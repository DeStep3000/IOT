#include "file_manager.h"
#include <wx/wx.h>

// Function to open a file dialog and return the selected file path
std::string FileManager::OpenFile() {
    // Set wildcard filter for text files
    wxString wildcard = "Text files (*.txt)|*.txt";

    // Create file dialog object with specified parameters
    wxFileDialog dialog(nullptr, "Open File", "", "", wildcard, wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    // Show the file dialog and wait for user input
    if (dialog.ShowModal() == wxID_OK) {
        // Get the selected file path
        wxString filePath = dialog.GetPath();
        // Convert wxString to std::string and return the file path
        return std::string(filePath.mb_str());
    } else {
        // Return an empty string if file selection is canceled
        return "";
    }
}

