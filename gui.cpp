#include "gui.hpp"

DialogPrintGuests::DialogPrintGuests(wxWindow *parent, std::string dbName) : wxDialog(parent, wxID_ANY, "Print guests", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
    // controls
    panelBottom = new wxPanel(this, wxID_ANY);
    guestList = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_READONLY);
    buttonOK = new wxButton(panelBottom, ID_PRINT_GUESTS_OK, "OK");
    Connect(ID_PRINT_GUESTS_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogPrintGuests::OnOK));

    // sizers
    vSizerBottom = new wxBoxSizer(wxVERTICAL);
    vSizerMain = new wxBoxSizer(wxVERTICAL);
    vSizerBottom->Add(buttonOK, 0, wxALIGN_RIGHT | wxTOP | wxBOTTOM | wxRIGHT, 5);
    vSizerMain->Add(guestList, 1, wxEXPAND, 0);
    vSizerMain->Add(panelBottom, 0, wxEXPAND, 0);
    panelBottom->SetSizer(vSizerBottom);
    SetSizer(vSizerMain);
    // final touches
    SetSize(wxSize(600, 400));
    try {
        guestList->SetValue(queryPrintGuests(DF_CNN, dbName));
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogPrintGuests::OnOK(wxCommandEvent &event)
{
    Destroy();
}

DialogAddGuest::DialogAddGuest(wxWindow *parent, std::string dbName) : wxDialog(parent, wxID_ANY, "Add guest"), dbName(dbName)
{
    // text fields / texts / buttons
    textFieldLastName = new wxTextCtrl(this, wxID_ANY, "<last name>");
    textFieldFirstName = new wxTextCtrl(this, wxID_ANY, "<first name>");
    staticTextRowSndLeft = new wxStaticText(this, wxID_ANY, wxEmptyString);
    textFieldPatronymic = new wxTextCtrl(this, wxID_ANY, "<patronymic>");
    textFieldPassportSeries = new wxTextCtrl(this, wxID_ANY, "<passport series>");
    textFieldPassportNumber = new wxTextCtrl(this, wxID_ANY, "<passport number>");
    staticTextRowFthLeft = new wxStaticText(this, wxID_ANY, wxEmptyString);
    textFieldPhone = new wxTextCtrl(this, wxID_ANY, "<phone>");
    staticTextRowFfhLeft = new wxStaticText(this, wxID_ANY, wxEmptyString);
    buttonAdd = new wxButton(this, ID_ADD_GUEST_ADD, "Add");
    buttonCancel = new wxButton(this, ID_ADD_GUEST_CANCEL, "Cancel");
    Connect(ID_ADD_GUEST_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogAddGuest::OnAdd));
    Connect(ID_ADD_GUEST_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogAddGuest::OnCancel));
    // sizers
    hSizerRowFstLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFstRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSndRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowTrdLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowTrdRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFthRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFfhRight = new wxBoxSizer(wxHORIZONTAL);
    gSizerMain = new wxGridSizer(2);
    hSizerRowFstLeft->Add(textFieldLastName, 1, wxTOP | wxLEFT, 5);
    hSizerRowFstRight->Add(textFieldFirstName, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowSndRight->Add(textFieldPatronymic, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowTrdLeft->Add(textFieldPassportSeries, 1, wxTOP | wxLEFT, 5);
    hSizerRowTrdRight->Add(textFieldPassportNumber, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowFthRight->Add(textFieldPhone, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowFfhRight->Add(buttonAdd, 1, wxTOP | wxBOTTOM | wxLEFT, 5);
    hSizerRowFfhRight->Add(buttonCancel, 1, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    gSizerMain->Add(hSizerRowFstLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFstRight, 0, wxEXPAND, 0);
    gSizerMain->Add(staticTextRowSndLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSndRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowTrdLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowTrdRight, 0, wxEXPAND, 0);
    gSizerMain->Add(staticTextRowFthLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFthRight, 0, wxEXPAND, 0);
    gSizerMain->Add(staticTextRowFfhLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFfhRight, 0, wxEXPAND, 0);
    SetSizer(gSizerMain);
    // final touches
    SetSize(wxSize(400, 226));
}

void DialogAddGuest::OnAdd(wxCommandEvent &event)
{
    try {
        queryAddGuest(DF_CNN, dbName,
                      textFieldLastName->GetValue().ToStdString(),
                      textFieldFirstName->GetValue().ToStdString(),
                      textFieldPatronymic->GetValue().ToStdString(),
                      textFieldPassportSeries->GetValue().ToStdString(),
                      textFieldPassportNumber->GetValue().ToStdString(),
                      textFieldPhone->GetValue().ToStdString());
        wxMessageBox((std::string) "Added!", "Success!", wxOK | wxCENTRE);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
    EndModal(ID_ADD_GUEST_ADD);
}

void DialogAddGuest::OnCancel(wxCommandEvent &event)
{
    EndModal(ID_ADD_GUEST_CANCEL);
}

DialogDeleteGuest::DialogDeleteGuest(wxWindow *parent, std::string dbName) : wxDialog(parent, wxID_ANY, "Delete all guests with certain initials"), dbName(dbName)
{
    // text fields / texts / buttons
    textFieldLastName = new wxTextCtrl(this, wxID_ANY, "<last name>");
    textFieldFirstName = new wxTextCtrl(this, wxID_ANY, "<first name>");
    staticTextRowSndLeft = new wxStaticText(this, wxID_ANY, wxEmptyString);
    buttonDelete = new wxButton(this, ID_DELETE_GUEST_DELETE, "Delete");
    buttonCancel = new wxButton(this, ID_DELETE_GUEST_CANCEL, "Cancel");
    Connect(ID_DELETE_GUEST_DELETE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogDeleteGuest::OnDelete));
    Connect(ID_DELETE_GUEST_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogDeleteGuest::OnCancel));
    // sizers
    hSizerRowFstLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFstRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSndRight = new wxBoxSizer(wxHORIZONTAL);
    gSizerMain = new wxGridSizer(2);
    hSizerRowFstLeft->Add(textFieldLastName, 1, wxTOP | wxLEFT, 5);
    hSizerRowFstRight->Add(textFieldFirstName, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowSndRight->Add(buttonDelete, 1, wxTOP | wxBOTTOM | wxLEFT, 5);
    hSizerRowSndRight->Add(buttonCancel, 1, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    gSizerMain->Add(hSizerRowFstLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFstRight, 0, wxEXPAND, 0);
    gSizerMain->Add(staticTextRowSndLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSndRight, 0, wxEXPAND, 0);
    SetSizer(gSizerMain);
    // final touches
    SetSize(wxSize(400, 100));
}

void DialogDeleteGuest::OnDelete(wxCommandEvent &event)
{
    try {
        queryDeleteGuest(DF_CNN, dbName,
                         textFieldLastName->GetValue().ToStdString(),
                         textFieldFirstName->GetValue().ToStdString());
        wxMessageBox((std::string) "All guests with such initials were deleted!", "Success!", wxOK | wxCENTRE);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
    EndModal(ID_DELETE_GUEST_DELETE);
}

void DialogDeleteGuest::OnCancel(wxCommandEvent &event)
{
    EndModal(ID_DELETE_GUEST_CANCEL);
}

void FrameMenu::AssumeDBCreated()
{
    buttonCreateDB->Enable(false);
    buttonDropDB->Enable(true);
    buttonAddGuest->Enable(true);
    buttonPrintGuests->Enable(true);
    buttonDeleteGuest->Enable(true);
}

void FrameMenu::AssumeDBDropped()
{
    buttonCreateDB->Enable(true);
    buttonDropDB->Enable(false);
    buttonAddGuest->Enable(false);
    buttonPrintGuests->Enable(false);
    buttonDeleteGuest->Enable(false);
}

void FrameMenu::AssumeDBError()
{
    buttonCreateDB->Enable(false);
    buttonDropDB->Enable(false);
    buttonAddGuest->Enable(false);
    buttonPrintGuests->Enable(false);
    buttonDeleteGuest->Enable(false);
}

FrameMenu::FrameMenu() : wxFrame(NULL, wxID_ANY, "HSE Hotel Client")
{
    // little things
    modeTest = false;
    SetIcon(wxIcon(PATH_ICON));
    // panels
    panelTopLeft = new wxPanel(this, wxID_ANY);
    panelTopRight = new wxPanel(this, wxID_ANY);
    panelBottomLeft = new wxPanel(this, wxID_ANY);
    panelBottomRight = new wxPanel(this, wxID_ANY);
    // text fields / texts / buttons
    textFieldDBName = new wxTextCtrl(panelTopLeft, wxID_ANY, "clientdb");
    buttonCreateDB = new wxButton(panelTopLeft, ID_CREATE_DB, "Create");
    buttonDropDB = new wxButton(panelTopLeft, ID_DROP_DB, "Delete");
    buttonCheckDB = new wxButton(panelTopLeft, ID_CHECK_DB, "Check");
    buttonModeTest = new wxButton(panelTopLeft, ID_MODE_TEST, "Test mode");
    buttonAddGuest = new wxButton(panelTopRight, ID_ADD_GUEST, "Add guest");
    buttonPrintGuests = new wxButton(panelTopRight, ID_PRINT_GUESTS, "Print all guests");
    buttonDeleteGuest = new wxButton(panelTopRight, ID_DELETE_GUEST, "Delete all guests with certain initials");
    buttonAbout = new wxButton(panelBottomLeft, wxID_ABOUT, "About");
    buttonExit = new wxButton(panelBottomRight, wxID_EXIT, "Exit");
    Connect(ID_CREATE_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnCreateDB));
    Connect(ID_DROP_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDropDB));
    Connect(ID_CHECK_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnCheckDB));
    Connect(ID_MODE_TEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnModeTest));
    Connect(ID_ADD_GUEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAddGuest));
    Connect(ID_PRINT_GUESTS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnPrintGuests));
    Connect(ID_DELETE_GUEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDeleteGuest));
    Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAbout));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnExit));
    // sizers
    vSizerControlDB = new wxStaticBoxSizer(wxVERTICAL, panelTopLeft, "Database");
    vSizerTopLeft = new wxBoxSizer(wxVERTICAL);
    vSizerTopRight = new wxBoxSizer(wxVERTICAL);
    hSizerTop = new wxBoxSizer(wxHORIZONTAL);
    vSizerBottomLeft = new wxBoxSizer(wxVERTICAL);
    vSizerBottomRight = new wxBoxSizer(wxVERTICAL);
    hSizerBottom = new wxBoxSizer(wxHORIZONTAL);
    vSizerMain = new wxBoxSizer(wxVERTICAL);

    vSizerControlDB->Add(textFieldDBName, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlDB->Add(buttonCheckDB, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlDB->AddSpacer(20);
    vSizerControlDB->Add(buttonCreateDB, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlDB->Add(buttonDropDB, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    vSizerTopLeft->Add(vSizerControlDB, 0, wxALIGN_CENTER | wxTOP | wxLEFT, 5);
    vSizerTopLeft->AddSpacer(20);
    vSizerTopLeft->Add(buttonModeTest, 0, wxALIGN_CENTER | wxTOP | wxLEFT, 5);
    vSizerTopRight->Add(buttonAddGuest, 0, wxALIGN_CENTER | wxTOP, 5);
    vSizerTopRight->Add(buttonPrintGuests, 0, wxALIGN_CENTER | wxTOP, 5);
    vSizerTopRight->Add(buttonDeleteGuest, 0, wxALIGN_CENTER | wxTOP, 5);
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
    SetMinSize(wxSize(420, 400));
    Centre();
    AssumeDBError();
    buttonCheckDB->SetFocus();
};

void FrameMenu::OnCreateDB(wxCommandEvent &event)
{
    try {
        if(queryCheckDB(DF_CNN, DF_DB, textFieldDBName->GetValue().ToStdString()) == false) {
            queryCreateDB(DF_CNN, DF_DB, textFieldDBName->GetValue().ToStdString());
            if(queryCheckDB(DF_CNN, DF_DB, textFieldDBName->GetValue().ToStdString()) == true) {
                AssumeDBCreated();
            }
            wxMessageBox("Database has been created!", "Information", wxOK | wxCENTRE);
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
        if(queryCheckDB(DF_CNN, DF_DB, textFieldDBName->GetValue().ToStdString()) == true) {
            queryDropDB(DF_CNN, DF_DB, textFieldDBName->GetValue().ToStdString());
            if(queryCheckDB(DF_CNN, DF_DB, textFieldDBName->GetValue().ToStdString()) == false) {
                AssumeDBDropped();
            }
            wxMessageBox("Database has been deleted!", "Information", wxOK | wxCENTRE);
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

void FrameMenu::OnCheckDB(wxCommandEvent &event)
{
    try {
        if(queryCheckDB(DF_CNN, DF_DB, textFieldDBName->GetValue().ToStdString()) == true) {
            AssumeDBCreated();
            wxMessageBox("Database exists", "Information", wxOK | wxCENTRE);
        }
        else {
            AssumeDBDropped();
            wxMessageBox("Database does not exist", "Information", wxOK | wxCENTRE);
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        AssumeDBError();
    }
}

void FrameMenu::OnModeTest(wxCommandEvent &event)
{
    if(modeTest == false) {
        modeTest = true;
        panelBottomLeft->SetBackgroundColour(wxColor(130, 40, 200));
        panelTopLeft->SetBackgroundColour(wxColor(50, 50, 50));
        panelTopRight->SetBackgroundColour(wxColor(50, 150, 0));
        panelBottomRight->SetBackgroundColour(wxColor(40, 20, 140));
        return;
    }
    modeTest = false;
    panelBottomLeft->SetBackgroundColour(wxNullColour);
    panelTopLeft->SetBackgroundColour(wxNullColour);
    panelTopRight->SetBackgroundColour(wxNullColour);
    panelBottomRight->SetBackgroundColour(wxNullColour);
}

void FrameMenu::OnAddGuest(wxCommandEvent &event)
{
    DialogAddGuest *dialogAddGuest = new DialogAddGuest(this, textFieldDBName->GetValue().ToStdString());
    dialogAddGuest->ShowModal();
    dialogAddGuest->Destroy();
//    std::cout << event.GetId() << std::endl;
}

void FrameMenu::OnPrintGuests(wxCommandEvent &event)
{
    DialogPrintGuests *dialogPrintGuests = new DialogPrintGuests(this, textFieldDBName->GetValue().ToStdString());
    dialogPrintGuests->Show(true);
//    Std::cout << event.GetId() << std::endl;
}
void FrameMenu::OnDeleteGuest(wxCommandEvent &event)
{
    DialogDeleteGuest *dialogDeleteGuest = new DialogDeleteGuest(this, textFieldDBName->GetValue().ToStdString());
    dialogDeleteGuest->ShowModal();
    dialogDeleteGuest->Destroy();
//    std::cout << event.GetId() << std::endl;
}

void FrameMenu::OnAbout(wxCommandEvent &event)
{
    wxMessageBox((std::string) "HSE Hotel Client, ver." + VERSION + "\n" + GITHUB, "About HSE Hotel Client", wxOK);
}

void FrameMenu::OnExit(wxCommandEvent &event)
{
    Close(true);
}
