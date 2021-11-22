#include "gui.hpp"

FrameMenu::FrameMenu(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    SetIcon(wxIcon(PATH_ICON));
    // panels
    panelTop = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panelBottomLeft = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panelBottomRight = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    // buttons
    buttonCheckDB = new wxButton(panelTop, ID_CHECK_DB, "Check database", wxDefaultPosition, wxDefaultSize);
    buttonCreateDB = new wxButton(panelTop, ID_CREATE_DB, "Create database", wxDefaultPosition, wxDefaultSize);
    buttonDropDB = new wxButton(panelTop, ID_DROP_DB, "Delete database", wxDefaultPosition, wxDefaultSize);
    buttonAbout = new wxButton(panelBottomLeft, wxID_ABOUT, "About", wxDefaultPosition, wxDefaultSize);
    buttonExit = new wxButton(panelBottomRight, wxID_EXIT, "Exit", wxDefaultPosition, wxDefaultSize);
    Connect(ID_CHECK_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnCheckDB));
    Connect(ID_CREATE_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnCreateDB));
    Connect(ID_DROP_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDropDB));
    Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAbout));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnExit));
    // sizers
    vSizerTop = new wxBoxSizer(wxVERTICAL);
    vSizerBottomLeft = new wxBoxSizer(wxVERTICAL);
    vSizerBottomRight = new wxBoxSizer(wxVERTICAL);
    hSizerBottom = new wxBoxSizer(wxHORIZONTAL);
    vSizerMain = new wxBoxSizer(wxVERTICAL);
    vSizerTop->Add(buttonCheckDB, 0, wxALIGN_CENTER | wxTOP, 10);
    vSizerTop->Add(buttonCreateDB, 0, wxALIGN_CENTER | wxTOP, 10);
    vSizerTop->Add(buttonDropDB, 0, wxALIGN_CENTER | wxTOP, 10);
    vSizerBottomLeft->Add(buttonAbout, 0, wxALIGN_LEFT | wxALL, 10);
    vSizerBottomRight->Add(buttonExit, 0, wxALIGN_RIGHT | wxALL, 10);
    hSizerBottom->Add(panelBottomLeft, 1, wxEXPAND, 0);
    hSizerBottom->Add(panelBottomRight, 1, wxEXPAND, 0);
    vSizerMain->Add(panelTop, 1, wxEXPAND, 0);
    vSizerMain->Add(hSizerBottom, 0, wxEXPAND, 0);
    panelBottomRight->SetSizer(vSizerBottomRight);
    panelBottomLeft->SetSizer(vSizerBottomLeft);
    panelTop->SetSizer(vSizerTop);
    SetSizer(vSizerMain);
    // final touches
    SetMinSize(wxSize(220, 160));
    Centre();
    try {
        if(queryCheckDB() == true) {
            buttonCreateDB->Enable(false);
        }
        else {
            buttonDropDB->Enable(false);
        }
    }
    catch(const std::exception &e) {
        buttonCreateDB->Enable(false);
        buttonDropDB->Enable(false);
    }
};

void FrameMenu::OnCheckDB(wxCommandEvent &event)
{
    try {
        if(queryCheckDB() == true) {
            buttonCreateDB->Enable(false);
            buttonDropDB->Enable(true);
            wxMessageBox("Database exists", "Information", wxOK | wxCENTRE | wxICON_INFORMATION);
        }
        else {
            buttonCreateDB->Enable(true);
            buttonDropDB->Enable(false);
            wxMessageBox("Database does not exist", "Information", wxOK | wxCENTRE | wxICON_INFORMATION);
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        buttonCreateDB->Enable(false);
        buttonDropDB->Enable(false);
    }
}

void FrameMenu::OnCreateDB(wxCommandEvent &event)
{
    try {
        if(queryCheckDB() == false) {
            queryCreateDB();
            if(queryCheckDB() == true) {
                buttonCreateDB->Enable(false);
                buttonDropDB->Enable(true);
            }
            wxMessageBox("Database has been created!", "Information", wxOK | wxCENTRE | wxICON_INFORMATION);
        }
        else {
            wxMessageBox("Database has already been created!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        buttonCreateDB->Enable(false);
        buttonDropDB->Enable(false);
    }

}

void FrameMenu::OnDropDB(wxCommandEvent &event)
{
    try {
        if(queryCheckDB() == true) {
            queryDropDB();
            if(queryCheckDB() == false) {
                buttonCreateDB->Enable(true);
                buttonDropDB->Enable(false);
            }
            wxMessageBox("Database has been deleted!", "Information", wxOK | wxCENTRE | wxICON_INFORMATION);
        }
        else {
            wxMessageBox("Database has already been deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        buttonCreateDB->Enable(false);
        buttonDropDB->Enable(false);
    }
}

void FrameMenu::OnAbout(wxCommandEvent &event)
{
    wxMessageBox((std::string) "HSE Hostel Client, ver." + VERSION + "\n" + GITHUB, "About HSE Hostel Client", wxOK | wxICON_INFORMATION);
}

void FrameMenu::OnExit(wxCommandEvent &event)
{
    Destroy();
}

wxIMPLEMENT_APP(AppClient);
