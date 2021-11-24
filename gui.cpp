#include "gui.hpp"

DialogAddGuest::DialogAddGuest(wxWindow *parent) : wxDialog(parent, wxID_ANY, "Add guest", wxDefaultPosition, wxDefaultSize)
{
//    panelMain = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    /*
    topLeft = new wxTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    topRight = new wxTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    bottomLeft = new wxTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    bottomRight = new wxTextCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    vGridSizerMain = new wxGridSizer(2, 0, 0);
    vGridSizerMain->Add(topLeft, );*/
//    vSizerMain->Add(panelMain, 1, wxEXPAND, 0);
//    SetSizer(vSizerMain);
}

void FrameMenu::AssumeDBCreated() {
    buttonCreateDB->Enable(false);
    buttonDropDB->Enable(true);
    buttonAddGuest->Enable(true);
}

void FrameMenu::AssumeDBDropped() {
    buttonCreateDB->Enable(true);
    buttonDropDB->Enable(false);
    buttonAddGuest->Enable(false);
}

void FrameMenu::AssumeDBError() {
    buttonCreateDB->Enable(false);
    buttonDropDB->Enable(false);
    buttonAddGuest->Enable(false);
}

FrameMenu::FrameMenu() : wxFrame(NULL, wxID_ANY, "HSE Hotel Client", wxDefaultPosition, wxDefaultSize)
{
    SetIcon(wxIcon(PATH_ICON));
    // panels
    panelTopRight = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panelTopLeft = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panelBottomLeft = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panelBottomRight = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
/*
    panelBottomLeft -> SetBackgroundColour(wxColor(130, 40, 200));
    panelTopLeft -> SetBackgroundColour(wxColor(50, 50, 50));
    panelTopRight -> SetBackgroundColour(wxColor(50, 150, 0));
    panelBottomRight -> SetBackgroundColour(wxColor(40, 20, 140));
*/
    // buttons
    buttonCheckDB = new wxButton(panelTopLeft, ID_CHECK_DB, "Check database", wxDefaultPosition, wxDefaultSize);
    buttonCreateDB = new wxButton(panelTopLeft, ID_CREATE_DB, "Create database", wxDefaultPosition, wxDefaultSize);
    buttonDropDB = new wxButton(panelTopLeft, ID_DROP_DB, "Delete database", wxDefaultPosition, wxDefaultSize);
    buttonAddGuest = new wxButton(panelTopRight, ID_ADD_GUEST, "Add guest", wxDefaultPosition, wxDefaultSize);
    buttonAbout = new wxButton(panelBottomLeft, wxID_ABOUT, "About", wxDefaultPosition, wxDefaultSize);
    buttonExit = new wxButton(panelBottomRight, wxID_EXIT, "Exit", wxDefaultPosition, wxDefaultSize);
    Connect(ID_CHECK_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnCheckDB));
    Connect(ID_CREATE_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnCreateDB));
    Connect(ID_DROP_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDropDB));
    Connect(ID_ADD_GUEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAddGuest));
    Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAbout));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnExit));
    // sizers
    vSizerTopLeft = new wxBoxSizer(wxVERTICAL);
    vSizerTopRight = new wxBoxSizer(wxVERTICAL);
    hSizerTop = new wxBoxSizer(wxHORIZONTAL);
    vSizerBottomLeft = new wxBoxSizer(wxVERTICAL);
    vSizerBottomRight = new wxBoxSizer(wxVERTICAL);
    hSizerBottom = new wxBoxSizer(wxHORIZONTAL);
    vSizerMain = new wxBoxSizer(wxVERTICAL);
    vSizerTopLeft->Add(buttonCreateDB, 0, wxALIGN_CENTER | wxTOP, 10);
    vSizerTopLeft->Add(buttonDropDB, 0, wxALIGN_CENTER | wxTOP, 10);
    vSizerTopLeft->Add(buttonCheckDB, 0, wxALIGN_CENTER | wxTOP, 30);
    vSizerTopRight->Add(buttonAddGuest, 0, wxALIGN_CENTER | wxTOP, 10);
    hSizerTop->Add(panelTopLeft, 0, wxEXPAND, 0);
    hSizerTop->Add(panelTopRight, 1, wxEXPAND, 0);
    vSizerBottomLeft->Add(buttonAbout, 0, wxALIGN_LEFT | wxALL, 10);
    vSizerBottomRight->Add(buttonExit, 0, wxALIGN_RIGHT | wxALL, 10);
    hSizerBottom->Add(panelBottomLeft, 1, wxEXPAND, 0);
    hSizerBottom->Add(panelBottomRight, 1, wxEXPAND, 0);
    vSizerMain->Add(hSizerTop, 1, wxEXPAND, 0);
    vSizerMain->Add(hSizerBottom, 0, wxEXPAND, 0);
    panelTopLeft->SetSizer(vSizerTopLeft);
    panelTopRight->SetSizer(vSizerTopRight);
    panelBottomLeft->SetSizer(vSizerBottomLeft);
    panelBottomRight->SetSizer(vSizerBottomRight);
    SetSizer(vSizerMain);
    // final touches
    SetMinSize(wxSize(440, 320));
    Centre();
    try {
        if(queryCheckDB() == true) {
            AssumeDBCreated();
        }
        else {
            AssumeDBDropped();
        }
    }
    catch(const std::exception &e) {
        AssumeDBError();
    }
};


void FrameMenu::OnCheckDB(wxCommandEvent &event)
{
    try {
        if(queryCheckDB() == true) {
            AssumeDBCreated();
            wxMessageBox("Database exists", "Information", wxOK | wxCENTRE | wxICON_INFORMATION);
        }
        else {
            AssumeDBDropped();
            wxMessageBox("Database does not exist", "Information", wxOK | wxCENTRE | wxICON_INFORMATION);
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        AssumeDBError();
    }
}


void FrameMenu::OnCreateDB(wxCommandEvent &event)
{
    try {
        if(queryCheckDB() == false) {
            queryCreateDB();
            if(queryCheckDB() == true) {
                AssumeDBCreated();
            }
            wxMessageBox("Database has been created!", "Information", wxOK | wxCENTRE | wxICON_INFORMATION);
        }
        else {
            wxMessageBox("Database has already been created!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        AssumeDBError();
    }
}

void FrameMenu::OnDropDB(wxCommandEvent &event)
{
    try {
        if(queryCheckDB() == true) {
            queryDropDB();
            if(queryCheckDB() == false) {
                AssumeDBDropped();
            }
            wxMessageBox("Database has been deleted!", "Information", wxOK | wxCENTRE | wxICON_INFORMATION);
        }
        else {
            wxMessageBox("Database has already been deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        AssumeDBError();
    }
}

void FrameMenu::OnAddGuest(wxCommandEvent &event)
{
    DialogAddGuest *dialogAddGuest = new DialogAddGuest(this);
    dialogAddGuest->Show(true);
}

void FrameMenu::OnAbout(wxCommandEvent &event)
{
    wxMessageBox((std::string) "HSE Hotel Client, ver." + VERSION + "\n" + GITHUB, "About HSE Hotel Client", wxOK | wxICON_INFORMATION);
}

void FrameMenu::OnExit(wxCommandEvent &event)
{
    Close(true);
}
