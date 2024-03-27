#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        wxFileDialog dialog(nullptr, "Open File", "", "", "", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
        if (dialog.ShowModal() == wxID_OK) {
            wxString filePath = dialog.GetPath();
            wxPrintf("Selected file: %s\n", filePath);
        }
        return false; // Возвращаем false, чтобы не запускать wxApp::MainLoop()
    }
};

wxIMPLEMENT_APP(MyApp);
