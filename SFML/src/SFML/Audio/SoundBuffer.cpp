////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2024 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio/ALCheck.hpp>
#include <SFML/Audio/AudioDevice.hpp>
#include <SFML/Audio/InputSoundFile.hpp>
#include <SFML/Audio/OutputSoundFile.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include <SFML/System/Err.hpp>
#include <SFML/System/Time.hpp>

#include <exception>
#include <ostream>
#include <utility>

#if defined(__APPLE__)
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

namespace sf
{
////////////////////////////////////////////////////////////
SoundBuffer::SoundBuffer()
{
    // Create the buffer
    alCheck(alGenBuffers(1, &m_buffer));
}


////////////////////////////////////////////////////////////
SoundBuffer::SoundBuffer(const SoundBuffer& copy) : m_samples(copy.m_samples), m_duration(copy.m_duration)
// don't copy the attached sounds
{
    // Create the buffer
    alCheck(alGenBuffers(1, &m_buffer));

    // Update the internal buffer with the new samples
    if (!update(copy.getChannelCount(), copy.getSampleRate()))
        err() << "Failed to update copy-constructed sound buffer" << std::endl;
}


////////////////////////////////////////////////////////////
SoundBuffer::~SoundBuffer()
{
    // Make sure no sound is attached to this buffer
    if (!m_sounds.empty())
    {
        err() << "Failed to destruct sound buffer because it is used by " << m_sounds.size() << " sound(s)" << std::endl;
        std::terminate();
    }

    // Destroy the buffer
    if (m_buffer)
        alCheck(alDeleteBuffers(1, &m_buffer));
}


////////////////////////////////////////////////////////////
bool SoundBuffer::loadFromFile(const std::filesystem::path& filename)
{
    InputSoundFile file;
    if (file.openFromFile(filename))
        return initialize(file);
    else
        return false;
}


////////////////////////////////////////////////////////////
bool SoundBuffer::loadFromMemory(const void* data, std::size_t sizeInBytes)
{
    InputSoundFile file;
    if (file.openFromMemory(data, sizeInBytes))
        return initialize(file);
    else
        return false;
}


////////////////////////////////////////////////////////////
bool SoundBuffer::loadFromStream(InputStream& stream)
{
    InputSoundFile file;
    if (file.openFromStream(stream))
        return initialize(file);
    else
        return false;
}


////////////////////////////////////////////////////////////
bool SoundBuffer::loadFromSamples(const std::int16_t* samples,
                                  std::uint64_t       sampleCount,
                                  unsigned int        channelCount,
                                  unsigned int        sampleRate)
{
    if (samples && sampleCount && channelCount && sampleRate)
    {
        // Copy the new audio samples
        m_samples.assign(samples, samples + sampleCount);

        // Update the internal buffer with the new samples
        return update(channelCount, sampleRate);
    }
    else
    {
        // Error...
        err() << "Failed to load sound buffer from samples ("
              << "array: " << samples << ", "
              << "count: " << sampleCount << ", "
              << "channels: " << channelCount << ", "
              << "samplerate: " << sampleRate << ")" << std::endl;

        return false;
    }
}


////////////////////////////////////////////////////////////
bool SoundBuffer::saveToFile(const std::filesystem::path& filename) const
{
    // Create the sound file in write mode
    OutputSoundFile file;
    if (file.openFromFile(filename, getSampleRate(), getChannelCount()))
    {
        // Write the samples to the opened file
        file.write(m_samples.data(), m_samples.size());

        return true;
    }
    else
    {
        return false;
    }
}


////////////////////////////////////////////////////////////
const std::int16_t* SoundBuffer::getSamples() const
{
    return m_samples.empty() ? nullptr : m_samples.data();
}


////////////////////////////////////////////////////////////
std::uint64_t SoundBuffer::getSampleCount() const
{
    return m_samples.size();
}


////////////////////////////////////////////////////////////
unsigned int SoundBuffer::getSampleRate() const
{
    ALint sampleRate;
    alCheck(alGetBufferi(m_buffer, AL_FREQUENCY, &sampleRate));

    return static_cast<unsigned int>(sampleRate);
}


////////////////////////////////////////////////////////////
unsigned int SoundBuffer::getChannelCount() const
{
    ALint channelCount;
    alCheck(alGetBufferi(m_buffer, AL_CHANNELS, &channelCount));

    return static_cast<unsigned int>(channelCount);
}


////////////////////////////////////////////////////////////
Time SoundBuffer::getDuration() const
{
    return m_duration;
}


////////////////////////////////////////////////////////////
SoundBuffer& SoundBuffer::operator=(const SoundBuffer& right)
{
    SoundBuffer temp(right);

    std::swap(m_samples, temp.m_samples);
    std::swap(m_buffer, temp.m_buffer);
    std::swap(m_duration, temp.m_duration);

    // Reattach sounds that use this buffer so they get bound to the new OpenAL buffer
    for (Sound* soundPtr : m_sounds)
    {
        soundPtr->stop();
        soundPtr->reattachBuffer();
    }

    return *this;
}


////////////////////////////////////////////////////////////
bool SoundBuffer::initialize(InputSoundFile& file)
{
    // Retrieve the sound parameters
    const std::uint64_t sampleCount  = file.getSampleCount();
    const unsigned int  channelCount = file.getChannelCount();
    const unsigned int  sampleRate   = file.getSampleRate();

    // Read the samples from the provided file
    m_samples.resize(static_cast<std::size_t>(sampleCount));
    if (file.read(m_samples.data(), sampleCount) == sampleCount)
    {
        // Update the internal buffer with the new samples
        return update(channelCount, sampleRate);
    }
    else
    {
        return false;
    }
}


////////////////////////////////////////////////////////////
bool SoundBuffer::update(unsigned int channelCount, unsigned int sampleRate)
{
    // Check parameters
    if (!channelCount || !sampleRate || m_samples.empty())
        return false;

    // Find the good format according to the number of channels
    const ALenum format = priv::AudioDevice::getFormatFromChannelCount(channelCount);

    // Check if the format is valid
    if (format == 0)
    {
        err() << "Failed to load sound buffer (unsupported number of channels: " << channelCount << ")" << std::endl;
        return false;
    }

    // Detach the buffer from the sounds that use it (to avoid OpenAL errors)
    for (Sound* soundPtr : m_sounds)
        soundPtr->detachBuffer();

    // Fill the buffer
    const auto size = static_cast<ALsizei>(m_samples.size() * sizeof(std::int16_t));
    alCheck(alBufferData(m_buffer, format, m_samples.data(), size, static_cast<ALsizei>(sampleRate)));

    // Compute the duration
    m_duration = seconds(
        static_cast<float>(m_samples.size()) / static_cast<float>(sampleRate) / static_cast<float>(channelCount));

    // Now reattach the buffer to the sounds that use it
    for (Sound* soundPtr : m_sounds)
        soundPtr->reattachBuffer();

    return true;
}


////////////////////////////////////////////////////////////
void SoundBuffer::attachSound(Sound* sound) const
{
    m_sounds.insert(sound);
}


////////////////////////////////////////////////////////////
void SoundBuffer::detachSound(Sound* sound) const
{
    m_sounds.erase(sound);
}

} // namespace sf
