#include "gui.hpp"

DialogAddBook::DialogAddBook(wxWindow *parent, std::string dbName) : wxDialog(parent, wxID_ANY, "Add booking"), dbName(dbName)
{
    txtFldArrival = new wxTextCtrl(this, wxID_ANY, "<arrival>");
    txtFldDeparture = new wxTextCtrl(this, wxID_ANY, "<departure>");
    txtFldDate = new wxTextCtrl(this, wxID_ANY, "<date>");
    txtFldRoom = new wxTextCtrl(this, wxID_ANY, "<room>");
    txtFldTotalCost = new wxTextCtrl(this, wxID_ANY, "<total cost>");
    txtFldBankCard = new wxTextCtrl(this, wxID_ANY, "<bank card>");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnAdd = new wxButton(this, ID_ADD_BOOKING_ADD, "Add");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_ADD_BOOKING_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogAddBook::OnAdd));
    hSzrRowFstLeft = new wxBoxSizer(wxHORIZONTAL);
    hSzrRowFstRight = new wxBoxSizer(wxHORIZONTAL);
    hSzrRowSndLeft = new wxBoxSizer(wxHORIZONTAL);
    hSzrRowSndRight = new wxBoxSizer(wxHORIZONTAL);
    hSzrRowTrdLeft = new wxBoxSizer(wxHORIZONTAL);
    hSzrRowTrdRight = new wxBoxSizer(wxHORIZONTAL);
    hSzrRowFthRight = new wxBoxSizer(wxHORIZONTAL);
    gSzrMain = new wxGridSizer(2);
    hSzrRowFstLeft->Add(txtFldArrival, 1, wxTOP | wxLEFT, 5);
    hSzrRowFstRight->Add(txtFldDeparture, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSzrRowSndLeft->Add(txtFldDate, 1, wxTOP | wxLEFT, 5);
    hSzrRowSndRight->Add(txtFldRoom, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSzrRowTrdLeft->Add(txtFldTotalCost, 1, wxTOP | wxLEFT, 5);
    hSzrRowTrdRight->Add(txtFldBankCard, 1, wxTOP | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    hSzrRowFthRight->Add(btnAdd, 1, wxTOP | wxLEFT | wxBOTTOM, 5);
    hSzrRowFthRight->Add(btnCancel, 1, wxTOP | wxLEFT | wxBOTTOM | wxRIGHT, 5);
    gSzrMain->Add(hSzrRowFstLeft, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrRowFstRight, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrRowSndLeft, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrRowSndRight, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrRowTrdLeft, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrRowTrdRight, 0, wxEXPAND, 0);
    gSzrMain->Add(sTxtEmpty, 0);
    gSzrMain->Add(hSzrRowFthRight, 0, wxEXPAND, 0);
    SetSizer(gSzrMain);
    txtFldArrival->SetFocus();
    SetSize(wxSize(400, 188));
}

void DialogAddBook::OnAdd(wxCommandEvent &event)
{
    /*
    try {
        queryAddBook(DF_CNN, dbName,
                     txtFldBookID->GetValue().ToStdString(),
                     txtFldArrival->GetValue().ToStdString(),
                     txtFldDeparture->GetValue().ToStdString(),
                     txtFldDate->GetValue().ToStdString(),
                     txtFldRoom->GetValue().ToStdString(),
                     txtFldTotalCost->GetValue().ToStdString(),
                     txtFldBankCard->GetValue().ToStdString());
        wxMessageBox((std::string) "Added!", "Success!", wxOK | wxCENTRE);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
    EndModal(ID_ADD_GUEST_ADD);
    */
}

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
    buttonCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_ADD_GUEST_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogAddGuest::OnAdd));
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

DialogViewGuest::DialogViewGuest(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, (std::string) "Guests (" + dbName + ")", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), dbName(dbName)
{
    guestLst = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_READONLY);
    txtFldLstName = new wxTextCtrl(this, wxID_ANY, "<last name>");
    txtFldFstName = new wxTextCtrl(this, wxID_ANY, "<first name>");
    btnFind = new wxButton(this, ID_VIEW_GUEST_FIND, "Find");
    btnPrintAll = new wxButton(this, ID_VIEW_GUEST_PRINT_ALL, "Print all");
    btnCancel = new wxButton(this, ID_VIEW_GUEST_CLOSE, "Close");
    Connect(ID_VIEW_GUEST_FIND, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewGuest::OnFind));
    Connect(ID_VIEW_GUEST_PRINT_ALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewGuest::OnPrintAll));
    Connect(ID_VIEW_GUEST_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewGuest::OnClose));
    hSzrBtm = new wxBoxSizer(wxHORIZONTAL);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrBtm->Add(txtFldLstName, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->Add(txtFldFstName, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->AddSpacer(20);
    hSzrBtm->Add(btnFind, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->Add(btnPrintAll, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->AddSpacer(20);
    hSzrBtm->Add(btnCancel, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 5);
    vSzrMain->Add(guestLst, 1, wxEXPAND, 0);
    vSzrMain->Add(hSzrBtm, 0, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetMinSize(wxSize(520, 400));
    SetSize(wxSize(600, 400));
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "guest");
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

void DialogViewGuest::OnFind(wxCommandEvent &event)
{
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "guest");
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

void DialogViewGuest::OnPrintAll(wxCommandEvent &event)
{
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "guest");
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

DialogViewRoom::DialogViewRoom(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, (std::string) "Hotel Rooms (" + dbName + ")", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), dbName(dbName)
{
    roomLst = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_READONLY);
    btnPrintAll = new wxButton(this, ID_VIEW_ROOM_PRINT_ALL, "Print all");
    btnCancel = new wxButton(this, ID_VIEW_ROOM_CLOSE, "Close");
    Connect(ID_VIEW_ROOM_PRINT_ALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewRoom::OnPrintAll));
    Connect(ID_VIEW_ROOM_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewRoom::OnClose));
    hSzrBtm1 = new wxBoxSizer(wxHORIZONTAL);
    hSzrBtm2 = new wxBoxSizer(wxHORIZONTAL);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    
    hSzrBtm2->Add(btnPrintAll);
    hSzrBtm2->AddSpacer(5);
    hSzrBtm2->Add(btnCancel);
    vSzrMain->Add(roomLst, 1, wxEXPAND);
    vSzrMain->Add(hSzrBtm1, 1, wxEXPAND);
    vSzrMain->Add(hSzrBtm2, 0, wxALIGN_RIGHT | wxLEFT | wxRIGHT | wxBOTTOM | wxTOP, 5) ;
    SetSizer(vSzrMain);
    SetMinSize(wxSize(520, 400));
    SetSize(wxSize(600, 400));
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "hotel_room");
        std::string txt;
        for(std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin(); it != tbl.cend(); ++it) {
            for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
                txt += *jt + ' ';
            }
            txt += '\n';
        }
        roomLst->SetValue(txt);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewRoom::OnPrintAll(wxCommandEvent &event)
{
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "hotel_room");
        std::string txt;
        for(std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin(); it != tbl.cend(); ++it) {
            for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
                txt += *jt + ' ';
            }
            txt += '\n';
        }
        roomLst->SetValue(txt);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewRoom::OnClose(wxCommandEvent &event)
{
    Destroy();
}

void DialogViewGuest::OnClose(wxCommandEvent &event)
{
    Destroy();
}

DialogDeleteGuest::DialogDeleteGuest(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Delete guest"), dbName(dbName)
{
    radio = 0;
    rBtnID = new wxRadioButton(this, ID_DELETE_GUEST_RADIO_ID, "Delete certain guest by ID:");
    rBtnName = new wxRadioButton(this, ID_DELETE_GUEST_RADIO_NAME, "Delete all guests with specified initials:");
    txtFldID = new wxTextCtrl(this, wxID_ANY, "<guest ID>");
    txtFldLstName = new wxTextCtrl(this, wxID_ANY, "<last name>");
    txtFldFstName = new wxTextCtrl(this, wxID_ANY, "<first name>");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnDel = new wxButton(this, ID_DELETE_GUEST_DELETE, "Delete");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_DELETE_GUEST_RADIO_ID, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDeleteGuest::OnRadioID));
    Connect(ID_DELETE_GUEST_RADIO_NAME, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDeleteGuest::OnRadioName));
    Connect(ID_DELETE_GUEST_DELETE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogDeleteGuest::OnDelete));
    hSzrIDRowFstRight = new wxBoxSizer(wxHORIZONTAL);
    hSzrNameRowFstLeft = new wxBoxSizer(wxHORIZONTAL);
    hSzrNameRowFstRight = new wxBoxSizer(wxHORIZONTAL);
    hSzrNameRowSndRight = new wxBoxSizer(wxHORIZONTAL);
    gSzrTop = new wxGridSizer(2);
    gSzrBtm = new wxGridSizer(2);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrIDRowFstRight->Add(txtFldID, 1, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    gSzrTop->Add(rBtnID, 0, wxEXPAND, 0);
    gSzrTop->Add(hSzrIDRowFstRight, 0, wxEXPAND, 0);
    hSzrNameRowFstLeft->Add(txtFldLstName, 1, wxTOP | wxLEFT, 5);
    hSzrNameRowFstRight->Add(txtFldFstName, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSzrNameRowSndRight->Add(btnDel, 1, wxTOP | wxBOTTOM | wxLEFT, 5);
    hSzrNameRowSndRight->Add(btnCancel, 1, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    gSzrBtm->Add(hSzrNameRowFstLeft, 0, wxEXPAND, 0);
    gSzrBtm->Add(hSzrNameRowFstRight, 0, wxEXPAND, 0);
    gSzrBtm->Add(sTxtEmpty, 0);
    gSzrBtm->Add(hSzrNameRowSndRight, 0, wxEXPAND, 0);
    vSzrMain->Add(gSzrTop, 1, wxEXPAND, 0);
    vSzrMain->Add(rBtnName, 1, wxEXPAND, 0);
    vSzrMain->Add(gSzrBtm, 1, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetSize(wxSize(400, 160));
    txtFldLstName->Enable(false);
    txtFldFstName->Enable(false);
    txtFldID->SetFocus();
}

DialogDeleteRoom::DialogDeleteRoom(wxWindow *parent, std::string dbName):
    wxDialog(parent, wxID_ANY, "Delete Room"), dbName(dbName)
{
    sTxtID = new wxStaticText(this, ID_DELETE_GUEST_RADIO_ID, "Delete the room by ID:");
    txtFldID = new wxTextCtrl(this, wxID_ANY, "<room ID>");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnDel = new wxButton(this, ID_DELETE_ROOM_DELETE, "Delete");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_DELETE_ROOM_DELETE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogDeleteRoom::OnDelete));
    hSzrIDRowFstRight = new wxBoxSizer(wxHORIZONTAL);
    hSzrNameRowFstLeft = new wxBoxSizer(wxHORIZONTAL);
    hSzrNameRowFstRight = new wxBoxSizer(wxHORIZONTAL);
    hSzrNameRowSndRight = new wxBoxSizer(wxHORIZONTAL);
    gSzrTop = new wxGridSizer(2);
    gSzrBtm = new wxGridSizer(2);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrNameRowFstLeft->Add(sTxtID, 1, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    gSzrTop->Add(hSzrNameRowFstLeft, 0, wxEXPAND, 0);
    hSzrIDRowFstRight->Add(txtFldID, 1, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    gSzrTop->Add(hSzrIDRowFstRight, 0, wxEXPAND, 0);
    hSzrNameRowSndRight->Add(btnDel, 1, wxTOP | wxBOTTOM | wxLEFT, 5);
    hSzrNameRowSndRight->Add(btnCancel, 1, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    gSzrBtm->Add(sTxtEmpty, 0);
    gSzrBtm->Add(hSzrNameRowSndRight, 0, wxEXPAND, 0);
    vSzrMain->Add(gSzrTop, 1, wxEXPAND, 0);
    vSzrMain->Add(gSzrBtm, 0, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetSize(wxSize(400, 160));
    txtFldID->SetFocus();
}

void DialogDeleteRoom::OnDelete(wxCommandEvent &event)
{
	bool info = false;
    try {
        info = queryDeleteRow(DF_CNN, dbName, "hotel_room", "hotel_room_id", txtFldID->GetValue().ToStdString());
        if(info == true) {
            wxMessageBox((std::string) "The room was deleted!", "Success!", wxOK | wxCENTRE);
            EndModal(ID_DELETE_ROOM_DELETE);
        }
        else {
            wxMessageBox((std::string) "There is no room with such ID!\nThe room was not deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
}

void DialogDeleteGuest::OnRadioID(wxCommandEvent &event)
{
    radio = 0;
    txtFldID->Enable(true);
    txtFldLstName->Enable(false);
    txtFldFstName->Enable(false);
}

void DialogDeleteGuest::OnRadioName(wxCommandEvent &event)
{
    radio = 1;
    txtFldID->Enable(false);
    txtFldLstName->Enable(true);
    txtFldFstName->Enable(true);
}

void DialogDeleteGuest::OnDelete(wxCommandEvent &event)
{
    bool info = false;
    try {
        if(radio == 0) {
            info = queryDeleteRow(DF_CNN, dbName, "guest", "guest_id", txtFldID->GetValue().ToStdString());
            if(info == true) {
                wxMessageBox((std::string) "The guest was deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_GUEST_DELETE);
            }
            else {
                wxMessageBox((std::string) "There is not guest with such ID!\nThe guest was not deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
        else {
            info = queryDeleteGuestByName(DF_CNN, dbName,
                                          txtFldLstName->GetValue().ToStdString(),
                                          txtFldFstName->GetValue().ToStdString());
            if(info == true) {
                wxMessageBox((std::string) "All guests with such initials were deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_GUEST_DELETE);
            }
            else {
                wxMessageBox((std::string) "There are no any guests with such initials!\nNo one was deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
}

DialogAddRoom::DialogAddRoom(wxWindow *parent, std::string dbName) : wxDialog(parent, wxID_ANY, "Add hotel room"), dbName(dbName)
{
    textFieldRoomId = new wxTextCtrl(this, wxID_ANY, "<hotel room id>");
    textFieldPrice = new wxTextCtrl(this, wxID_ANY, "<price per day>");
    textFieldNumberOfRooms = new wxTextCtrl(this, wxID_ANY, "<number of rooms>");
    textFieldArea = new wxTextCtrl(this, wxID_ANY, "<area>");
    textFieldServiceClass = new wxTextCtrl(this, wxID_ANY, "<service class>");
    textFieldKitchen = new wxTextCtrl(this, wxID_ANY, "<kitchen>");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    buttonAdd = new wxButton(this, ID_ADD_ROOM_ADD, "Add");
    buttonCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_ADD_ROOM_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogAddRoom::OnAdd));
    hSizerRowFstLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFstRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSndLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSndRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowTrdLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowTrdRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFthLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFthRight = new wxBoxSizer(wxHORIZONTAL);
    gSizerMain = new wxGridSizer(2);
    hSizerRowFstLeft->Add(textFieldRoomId, 1, wxTOP | wxLEFT, 5);
    hSizerRowFstRight->Add(textFieldPrice, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowSndLeft->Add(textFieldNumberOfRooms, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowSndRight->Add(textFieldArea, 1, wxTOP | wxLEFT, 5);
    hSizerRowTrdLeft->Add(textFieldServiceClass, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowTrdRight->Add(textFieldKitchen, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowFthLeft->Add(sTxtEmpty, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowFthRight->Add(buttonAdd, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    hSizerRowFthRight->Add(buttonCancel, 1, wxTOP | wxLEFT | wxRIGHT, 5);
    gSizerMain->Add(hSizerRowFstLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFstRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSndLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSndRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowTrdLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowTrdRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFthLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFthRight, 0, wxEXPAND, 0);
    SetSizer(gSizerMain);
    SetSize(wxSize(400, 188));
}

void DialogAddRoom::OnAdd(wxCommandEvent &event)
{
    try {
        queryAddRoom(DF_CNN, dbName,
                      textFieldRoomId->GetValue().ToStdString(),
                      textFieldPrice->GetValue().ToStdString(),
                      textFieldNumberOfRooms->GetValue().ToStdString(),
                      textFieldArea->GetValue().ToStdString(),
                      textFieldServiceClass->GetValue().ToStdString(),
                      textFieldKitchen->GetValue().ToStdString());
        wxMessageBox((std::string) "Added!", "Success!", wxOK | wxCENTRE);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
    EndModal(ID_ADD_ROOM_ADD);
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
    btnAddBook = new wxButton(panelTopRight, ID_ADD_BOOKING, "Add");
    btnViewBook = new wxButton(panelTopRight, ID_VIEW_BOOKING, "View");
    btnDelBook = new wxButton(panelTopRight, ID_DELETE_BOOKING, "Delete");
    buttonAddGuest = new wxButton(panelTopRight, ID_ADD_GUEST, "Add");
    btnViewGuest = new wxButton(panelTopRight, ID_VIEW_GUEST, "View");
    buttonDeleteGuest = new wxButton(panelTopRight, ID_DELETE_GUEST, "Delete");
    btnAddRoom = new wxButton(panelTopRight, ID_ADD_ROOM, "Add");
    btnViewRoom = new wxButton(panelTopRight, ID_VIEW_ROOM, "View");
    btnDelRoom = new wxButton(panelTopRight, ID_DELETE_ROOM, "Delete");
    buttonAbout = new wxButton(panelBottomLeft, wxID_ABOUT, "About");
    buttonExit = new wxButton(panelBottomRight, wxID_EXIT, "Exit");
    Connect(ID_CREATE_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnCreateDB));
    Connect(ID_DROP_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDropDB));
    Connect(ID_CHECK_DB, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnCheckDB));
    Connect(ID_MODE_TEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnModeTest));
    Connect(ID_ADD_BOOKING, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAddBook));
    Connect(ID_VIEW_BOOKING, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnViewBook));
    Connect(ID_DELETE_BOOKING, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDeleteBook));
    Connect(ID_ADD_GUEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAddGuest));
    Connect(ID_ADD_ROOM, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAddRoom));
    Connect(ID_VIEW_GUEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnViewGuest));
    Connect(ID_VIEW_ROOM, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnViewRoom));
    Connect(ID_DELETE_GUEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDeleteGuest));
    Connect(ID_DELETE_ROOM, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDeleteRoom));
    Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAbout));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnExit));
    vSizerControlDB = new wxStaticBoxSizer(wxVERTICAL, panelTopLeft, "Database");
    vSzrControlBook = new wxStaticBoxSizer(wxVERTICAL, panelTopRight, "Booking");
    vSizerControlGuest = new wxStaticBoxSizer(wxVERTICAL, panelTopRight, "Guest");
    vSizerControlRoom = new wxStaticBoxSizer(wxVERTICAL, panelTopRight, "Hotel room");
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
    vSzrControlBook->Add(btnAddBook, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSzrControlBook->Add(btnViewBook, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSzrControlBook->Add(btnDelBook, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    vSizerTopRight->Add(vSzrControlBook, 0, wxALIGN_CENTER | wxTOP, 5);
    vSizerControlGuest->Add(buttonAddGuest, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlGuest->Add(btnViewGuest, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlGuest->Add(buttonDeleteGuest, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    vSizerControlRoom->Add(btnAddRoom, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlRoom->Add(btnViewRoom, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlRoom->Add(btnDelRoom, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    vSizerTopRight->Add(vSizerControlGuest, 0, wxALIGN_CENTER | wxTOP, 5);
    vSizerTopRight->Add(vSizerControlRoom, 0, wxALIGN_CENTER | wxTOP, 5);
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
}

void FrameMenu::AssumeDBCreated()
{
    buttonCreateDB->Enable(false);
    buttonDropDB->Enable(true);
    btnAddBook->Enable(true);
    btnViewBook->Enable(true);
    btnDelBook->Enable(true);
    buttonAddGuest->Enable(true);
    btnViewGuest->Enable(true);
    buttonDeleteGuest->Enable(true);
    btnAddRoom->Enable(true);
    btnViewRoom->Enable(true);
    btnDelRoom->Enable(true);
}

void FrameMenu::AssumeDBDropped()
{
    buttonCreateDB->Enable(true);
    buttonDropDB->Enable(false);
    btnAddBook->Enable(false);
    btnViewBook->Enable(false);
    btnDelBook->Enable(false);
    buttonAddGuest->Enable(false);
    btnViewGuest->Enable(false);
    buttonDeleteGuest->Enable(false);
    btnAddRoom->Enable(false);
    btnViewRoom->Enable(false);
    btnDelRoom->Enable(false);
}

void FrameMenu::AssumeDBError()
{
    buttonCreateDB->Enable(false);
    buttonDropDB->Enable(false);
    btnAddBook->Enable(false);
    btnViewBook->Enable(false);
    btnDelBook->Enable(false);
    buttonAddGuest->Enable(false);
    btnViewGuest->Enable(false);
    buttonDeleteGuest->Enable(false);
    btnAddRoom->Enable(false);
    btnViewRoom->Enable(false);
    btnDelRoom->Enable(false);
}

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

void FrameMenu::OnAddBook(wxCommandEvent &event)
{
    DialogAddBook *dialogAddBook = new DialogAddBook(this, textFieldDBName->GetValue().ToStdString());
    dialogAddBook->ShowModal();
    dialogAddBook->Destroy();
}

void FrameMenu::OnViewBook(wxCommandEvent &event)
{
    
}

void FrameMenu::OnDeleteBook(wxCommandEvent &event)
{
    
}

void FrameMenu::OnDeleteRoom(wxCommandEvent &event)
{
    DialogDeleteRoom *dialogDeleteRoom = new DialogDeleteRoom(this, textFieldDBName->GetValue().ToStdString());
    dialogDeleteRoom->ShowModal();
    dialogDeleteRoom->Destroy();
}

void FrameMenu::OnAddGuest(wxCommandEvent &event)
{
    DialogAddGuest *dialogAddGuest = new DialogAddGuest(this, textFieldDBName->GetValue().ToStdString());
    dialogAddGuest->ShowModal();
    dialogAddGuest->Destroy();
}

void FrameMenu::OnViewGuest(wxCommandEvent &event)
{
    DialogViewGuest *dialogViewGuest = new DialogViewGuest(this, textFieldDBName->GetValue().ToStdString());
    dialogViewGuest->Show(true);
}

void FrameMenu::OnDeleteGuest(wxCommandEvent &event)
{
    DialogDeleteGuest *dialogDeleteGuest = new DialogDeleteGuest(this, textFieldDBName->GetValue().ToStdString());
    dialogDeleteGuest->ShowModal();
    dialogDeleteGuest->Destroy();
}

void FrameMenu::OnAddRoom(wxCommandEvent &event)
{
    DialogAddRoom *dialogAddRoom = new DialogAddRoom(this, textFieldDBName->GetValue().ToStdString());
    dialogAddRoom->ShowModal();
    dialogAddRoom->Destroy();
}

void FrameMenu::OnViewRoom(wxCommandEvent &event)
{
    DialogViewRoom *dialogViewRoom = new DialogViewRoom(this, textFieldDBName->GetValue().ToStdString());
    dialogViewRoom->Show(true);
}

void FrameMenu::OnAbout(wxCommandEvent &event)
{
    wxMessageBox((std::string) "HSE Hotel Client, ver." + VERSION + "\n" + GITHUB, "About HSE Hotel Client", wxOK);
}

void FrameMenu::OnExit(wxCommandEvent &event)
{
    Close(true);
}
