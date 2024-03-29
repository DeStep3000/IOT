#include "file_manager.h"
#include <wx/wx.h>

std::string FileManager::OpenFile() {
    wxString wildcard = "Text files (*.txt)|*.txt"; // Устанавливаем фильтр для текстовых файлов
    wxFileDialog dialog(nullptr, "Open File", "", "", wildcard, wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dialog.ShowModal() == wxID_OK) {
        wxString filePath = dialog.GetPath();
        return std::string(filePath.mb_str()); // Возвращаем путь выбранного файла
    } else {
        return ""; // В случае отмены выбора файла возвращаем пустую строку
    }
}
