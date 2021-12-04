#include "gui.hpp"

DialogAddGuest::DialogAddGuest(wxWindow *parent, std::string dbName) : wxDialog(parent, wxID_ANY, "Add guest"), dbName(dbName)
{
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

DialogViewGuests::DialogViewGuests(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, (std::string) "Guests (" + dbName + ")", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), dbName(dbName)
{
    guestLst = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_READONLY);
    txtFldLstName = new wxTextCtrl(this, wxID_ANY, "<last name>");
    txtFldFstName = new wxTextCtrl(this, wxID_ANY, "<first name>");
    btnFind = new wxButton(this, ID_VIEW_GUESTS_FIND, "Find");
    btnPrintAll = new wxButton(this, ID_VIEW_GUESTS_PRINT_ALL, "Print all");
    btnCancel = new wxButton(this, ID_VIEW_GUESTS_CLOSE, "Close");
    Connect(ID_VIEW_GUESTS_FIND, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewGuests::OnFind));
    Connect(ID_VIEW_GUESTS_PRINT_ALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewGuests::OnPrintAll));
    Connect(ID_VIEW_GUESTS_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewGuests::OnCancel));
    hSzrBtm = new wxBoxSizer(wxHORIZONTAL);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrBtm->Add(txtFldLstName, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->Add(txtFldFstName, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->Add(btnFind, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->Add(btnPrintAll, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->AddSpacer(20);
    hSzrBtm->Add(btnCancel, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 5);
    vSzrMain->Add(guestLst, 1, wxEXPAND, 0);
    vSzrMain->Add(hSzrBtm, 0, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetMinSize(wxSize(500, 400));
    SetSize(wxSize(600, 400));
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintGuests(DF_CNN, dbName);
        std::string txt;
        for(std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin(); it != tbl.cend(); ++it) {
            for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
                txt += *jt + ' ';
            }
            txt += '\n';
        }
        guestLst->SetValue(txt);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewGuests::OnFind(wxCommandEvent &event)
{
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintGuests(DF_CNN, dbName);
        std::string txt;
        for(std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin(); it != tbl.cend(); ++it) {
            if(it->at(1) == txtFldLstName->GetValue() && it->at(2) == txtFldFstName->GetValue()) {
                for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
                    txt += *jt + ' ';
                }
                txt += '\n';
            }
        }
        guestLst->SetValue(txt);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewGuests::OnPrintAll(wxCommandEvent &event)
{
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintGuests(DF_CNN, dbName);
        std::string txt;
        for(std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin(); it != tbl.cend(); ++it) {
            for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
                txt += *jt + ' ';
            }
            txt += '\n';
        }
        guestLst->SetValue(txt);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewGuests::OnCancel(wxCommandEvent &event)
{
    Destroy();
}

DialogDeleteGuest::DialogDeleteGuest(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Delete all guests with certain initials"), dbName(dbName)
{
    textFieldLastName = new wxTextCtrl(this, wxID_ANY, "<last name>");
    textFieldFirstName = new wxTextCtrl(this, wxID_ANY, "<first name>");
    staticTextRowSndLeft = new wxStaticText(this, wxID_ANY, wxEmptyString);
    buttonDelete = new wxButton(this, ID_DELETE_GUEST_DELETE, "Delete");
    buttonCancel = new wxButton(this, ID_DELETE_GUEST_CANCEL, "Cancel");
    Connect(ID_DELETE_GUEST_DELETE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogDeleteGuest::OnDelete));
    Connect(ID_DELETE_GUEST_CANCEL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogDeleteGuest::OnCancel));
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
    buttonViewGuests->Enable(true);
    buttonDeleteGuest->Enable(true);
}

void FrameMenu::AssumeDBDropped()
{
    buttonCreateDB->Enable(true);
    buttonDropDB->Enable(false);
    buttonAddGuest->Enable(false);
    buttonViewGuests->Enable(false);
    buttonDeleteGuest->Enable(false);
}

void FrameMenu::AssumeDBError()
{
    buttonCreateDB->Enable(false);
    buttonDropDB->Enable(false);
    buttonAddGuest->Enable(false);
    buttonViewGuests->Enable(false);
    buttonDeleteGuest->Enable(false);
}

FrameMenu::FrameMenu() : wxFrame(NULL, wxID_ANY, "HSE Hotel Client")
{
    modeTest = false;
    SetIcon(wxIcon(PATH_ICON));
    panelTopLeft = new wxPanel(this, wxID_ANY);
    panelTopRight = new wxPanel(this, wxID_ANY);
    panelBottomLeft = new wxPanel(this, wxID_ANY);
    panelBottomRight = new wxPanel(this, wxID_ANY);
    textFieldDBName = new wxTextCtrl(panelTopLeft, wxID_ANY, "clientdb");
    buttonCreateDB = new wxButton(panelTopLeft, ID_CREATE_DB, "Create");
    buttonDropDB = new wxButton(panelTopLeft, ID_DROP_DB, "Delete");
    buttonCheckDB = new wxButton(panelTopLeft, ID_CHECK_DB, "Check");
    buttonModeTest = new wxButton(panelTopLeft, ID_MODE_TEST, "Test mode");
    buttonAddGuest = new wxButton(panelTopRight, ID_ADD_GUEST, "Add guest");
    buttonViewGuests = new wxButton(panelTopRight, ID_VIEW_GUESTS, "View guests");
    buttonDeleteGuest = new wxButton(panelTopRight, ID_DELETE_GUEST, "Delete all guests with certain initials");
    buttonAbout = new wxButton(panelBottomLeft, wxID_ABOUT, "About");
    buttonExit = new wxButton(panelBottomRight, wxID_EXIT, "Exit");
    Connect(ID_CREATE_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnCreateDB));
    Connect(ID_DROP_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDropDB));
    Connect(ID_CHECK_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnCheckDB));
    Connect(ID_MODE_TEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnModeTest));
    Connect(ID_ADD_GUEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAddGuest));
    Connect(ID_VIEW_GUESTS, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnViewGuests));
    Connect(ID_DELETE_GUEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDeleteGuest));
    Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAbout));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnExit));
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
    vSizerTopRight->Add(buttonViewGuests, 0, wxALIGN_CENTER | wxTOP, 5);
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
}

void FrameMenu::OnViewGuests(wxCommandEvent &event)
{
    DialogViewGuests *dialogViewGuests = new DialogViewGuests(this, textFieldDBName->GetValue().ToStdString());
    dialogViewGuests->Show(true);
}

void FrameMenu::OnDeleteGuest(wxCommandEvent &event)
{
    DialogDeleteGuest *dialogDeleteGuest = new DialogDeleteGuest(this, textFieldDBName->GetValue().ToStdString());
    dialogDeleteGuest->ShowModal();
    dialogDeleteGuest->Destroy();
}

void FrameMenu::OnAbout(wxCommandEvent &event)
{
    wxMessageBox((std::string) "HSE Hotel Client, ver." + VERSION + "\n" + GITHUB, "About HSE Hotel Client", wxOK);
}

void FrameMenu::OnExit(wxCommandEvent &event)
{
    Close(true);
}
