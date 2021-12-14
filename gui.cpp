#include "gui.hpp"

DialogAddBook::DialogAddBook(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Add booking"), dbName(dbName)
{
    txtFldArrival = new wxTextCtrl(this, wxID_ANY, "<arrival>");
    txtFldDeparture = new wxTextCtrl(this, wxID_ANY, "<departure>");
    txtFldDate = new wxTextCtrl(this, wxID_ANY, "<date>");
    txtFldRoom = new wxTextCtrl(this, wxID_ANY, "<room>");
    txtFldCard = new wxTextCtrl(this, wxID_ANY, "<bank card>");
    btnAdd = new wxButton(this, ID_ADD_BOOKING_ADD, "Add");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_ADD_BOOKING_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogAddBook::OnAdd));
    hSzrFldArrival = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldDeparture = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldDate = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldRoom = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldCard = new wxBoxSizer(wxHORIZONTAL);
    hSzrBtns = new wxBoxSizer(wxHORIZONTAL);
    gSzrMain = new wxGridSizer(2);
    hSzrFldArrival->Add(txtFldArrival, 1, wxLEFT, 5);
    hSzrFldDeparture->Add(txtFldDeparture, 1, wxLEFT | wxRIGHT, 5);
    hSzrFldDate->Add(txtFldDate, 1, wxLEFT, 5);
    hSzrFldRoom->Add(txtFldRoom, 1, wxLEFT | wxRIGHT, 5);
    hSzrFldCard->Add(txtFldCard, 1, wxLEFT, 5);
    hSzrBtns->Add(btnAdd, 1, wxLEFT, 5);
    hSzrBtns->Add(btnCancel, 1, wxLEFT | wxRIGHT, 5);
    gSzrMain->Add(hSzrFldArrival, 0, wxEXPAND | wxTOP, 5);
    gSzrMain->Add(hSzrFldDeparture, 0, wxEXPAND | wxTOP, 5);
    gSzrMain->Add(hSzrFldDate, 0, wxEXPAND | wxTOP, 5);
    gSzrMain->Add(hSzrFldRoom, 0, wxEXPAND | wxTOP, 5);
    gSzrMain->Add(hSzrFldCard, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    gSzrMain->Add(hSzrBtns, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    SetSizerAndFit(gSzrMain);
    txtFldArrival->SetFocus();
}

void DialogAddBook::OnAdd(wxCommandEvent &event)
{
    try {
        queryAddBook(DF_CNN, dbName,
                     txtFldArrival->GetValue().ToStdString(),
                     txtFldDeparture->GetValue().ToStdString(),
                     txtFldDate->GetValue().ToStdString(),
                     txtFldRoom->GetValue().ToStdString(),
                     txtFldCard->GetValue().ToStdString());
        wxMessageBox((std::string) "Added!", "Success!", wxOK | wxCENTRE);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
    EndModal(ID_ADD_GUEST_ADD);
}

DialogViewBook::DialogViewBook(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, (std::string) "Bookings (" + dbName + ")", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), dbName(dbName)
{
    bookLst = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_READONLY);
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnPrintAll = new wxButton(this, ID_VIEW_BOOKING_PRINT_ALL, "Print All");
    btnClose = new wxButton(this, ID_VIEW_BOOKING_CLOSE, "Close");
    Connect(ID_VIEW_BOOKING_PRINT_ALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewBook::OnPrintAll));
    Connect(ID_VIEW_BOOKING_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewBook::OnClose));
    hSzrBtm = new wxBoxSizer(wxHORIZONTAL);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrBtm->Add(sTxtEmpty, 1);
    hSzrBtm->Add(btnPrintAll, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->AddSpacer(20);
    hSzrBtm->Add(btnClose, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 5);
    vSzrMain->Add(bookLst, 1, wxEXPAND, 0);
    vSzrMain->Add(hSzrBtm, 0, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetMinSize(wxSize(520, 400));
    SetSize(wxSize(600, 400));
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "booking");
        std::string txt;
        for(std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin(); it != tbl.cend(); ++it) {
            for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
                txt += *jt + ' ';
            }
            txt += '\n';
        }
        bookLst->SetValue(txt);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewBook::OnPrintAll(wxCommandEvent &event)
{
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "booking");
        std::string txt;
        for(std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin(); it != tbl.cend(); ++it) {
            for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
                txt += *jt + ' ';
            }
            txt += '\n';
        }
        bookLst->SetValue(txt);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewBook::OnClose(wxCommandEvent &event)
{
    Destroy();
}

DialogDeleteBook::DialogDeleteBook(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Delete booking"), dbName(dbName)
{
    radio = ID_DELETE_BOOKING_RADIO_ID;
    rBtnID = new wxRadioButton(this, ID_DELETE_BOOKING_RADIO_ID, "Delete certain booking by ID:");
    rBtnDelAll = new wxRadioButton(this, ID_DELETE_BOOKING_RADIO_DELETE_ALL, "Delete all bookings (clear the table)");
    txtFldID = new wxTextCtrl(this, wxID_ANY, "<booking ID>");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnDel = new wxButton(this, ID_DELETE_BOOKING_DELETE, "Delete");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_DELETE_BOOKING_RADIO_ID, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDeleteBook::OnRadioID));
    Connect(ID_DELETE_BOOKING_RADIO_DELETE_ALL, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDeleteBook::OnRadioDelAll));
    Connect(ID_DELETE_BOOKING_DELETE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogDeleteBook::OnDelete));
    hSzrTxtFldID = new wxBoxSizer(wxHORIZONTAL);
    hSzrBtns = new wxBoxSizer(wxHORIZONTAL);
    gSzrID = new wxGridSizer(2);
    gSzrBtm = new wxGridSizer(2);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrTxtFldID->Add(txtFldID, 1, wxLEFT | wxRIGHT, 5);
    gSzrID->Add(rBtnID, 0, wxEXPAND | wxTOP, 5);
    gSzrID->Add(hSzrTxtFldID, 0, wxEXPAND | wxTOP, 5);
    hSzrBtns->Add(btnDel, 1, wxLEFT, 5);
    hSzrBtns->Add(btnCancel, 1, wxLEFT | wxRIGHT, 5);
    gSzrBtm->Add(sTxtEmpty, 0, wxTOP | wxBOTTOM, 5);
    gSzrBtm->Add(hSzrBtns, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    vSzrMain->Add(gSzrID, 0, wxEXPAND, 0);
    vSzrMain->Add(rBtnDelAll, 0, wxEXPAND | wxTOP, 5);
    vSzrMain->Add(gSzrBtm, 0, wxEXPAND, 0);
    SetSizerAndFit(vSzrMain);
    txtFldID->SetFocus();
}

void DialogDeleteBook::OnRadioID(wxCommandEvent &event)
{
    radio = ID_DELETE_BOOKING_RADIO_ID;
    txtFldID->Enable(true);
}

void DialogDeleteBook::OnRadioDelAll(wxCommandEvent &event)
{
    radio = ID_DELETE_BOOKING_RADIO_DELETE_ALL;
    txtFldID->Enable(false);
}

void DialogDeleteBook::OnDelete(wxCommandEvent &event)
{
    bool info = false;
    try {
        if(radio == ID_DELETE_BOOKING_RADIO_ID) {
            info = queryDeleteRow(DF_CNN, dbName, "booking", "booking_id", txtFldID->GetValue().ToStdString());
            if(info == true) {
                wxMessageBox("The booking was deleted!", "Succes!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_BOOKING_DELETE);
            }
            else {
                wxMessageBox("There is not booking with such ID!\nNo one was deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
        else if(radio == ID_DELETE_BOOKING_RADIO_DELETE_ALL) {
            info = queryClearTable(DF_CNN, dbName, "booking");
            if(info == true) {
                wxMessageBox("Add bookings have been deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_BOOKING_DELETE);
            }
            else {
                wxMessageBox("There are already no bookings in this table!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
        else {
            throw std::invalid_argument("What a shame, dude...");
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Errow:\n" + e.what(), "Error", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
}

DialogAddGuest::DialogAddGuest(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Add guest"), dbName(dbName)
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
    SetSizerAndFit(gSizerMain);
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
    btnClose = new wxButton(this, ID_VIEW_GUEST_CLOSE, "Close");
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
    hSzrBtm->Add(btnClose, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 5);
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
    txtFldArrival = new wxTextCtrl(this, wxID_ANY, "<arrival>");
    txtFldDeparture = new wxTextCtrl(this, wxID_ANY, "<departure>");
    btnFind = new wxButton(this, ID_VIEW_ROOM_FIND, "Find free room");
    btnPrintAll = new wxButton(this, ID_VIEW_ROOM_PRINT_ALL, "Print all");
    btnCancel = new wxButton(this, ID_VIEW_ROOM_CLOSE, "Close");
    Connect(ID_VIEW_ROOM_FIND, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewRoom::OnFind));
    Connect(ID_VIEW_ROOM_PRINT_ALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewRoom::OnPrintAll));
    Connect(ID_VIEW_ROOM_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewRoom::OnClose));
    hSzrBtm = new wxBoxSizer(wxHORIZONTAL);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrBtm->Add(txtFldArrival, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->Add(txtFldDeparture, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->AddSpacer(20);
    hSzrBtm->Add(btnFind, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->Add(btnPrintAll, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->AddSpacer(20);
    hSzrBtm->Add(btnCancel, 0, wxALL, 5);
    vSzrMain->Add(roomLst, 1, wxEXPAND, 0);
    vSzrMain->Add(hSzrBtm, 0, wxEXPAND, 0);
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

void DialogViewRoom::OnFind(wxCommandEvent &event)
{
	try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryFindRooms(DF_CNN, dbName, txtFldArrival->GetValue().ToStdString(), txtFldDeparture->GetValue().ToStdString());
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
    radio = ID_DELETE_GUEST_RADIO_ID;
    rBtnID = new wxRadioButton(this, ID_DELETE_GUEST_RADIO_ID, "Delete certain guest by ID:");
    rBtnPassport = new wxRadioButton(this, ID_DELETE_GUEST_RADIO_PASSPORT, "Delete guest by passport serial and number:");
    rBtnName = new wxRadioButton(this, ID_DELETE_GUEST_RADIO_NAME, "Delete all guests with specified initials:");
    rBtnDelAll = new wxRadioButton(this, ID_DELETE_GUEST_RADIO_DELETE_ALL, "Delete all guests (clear the table)");
    txtFldID = new wxTextCtrl(this, wxID_ANY, "<guest ID>");
    txtFldPassportSer = new wxTextCtrl(this, wxID_ANY, "<passport serial>");
    txtFldPassportNum = new wxTextCtrl(this, wxID_ANY, "<passport number>");
    txtFldLstName = new wxTextCtrl(this, wxID_ANY, "<last name>");
    txtFldFstName = new wxTextCtrl(this, wxID_ANY, "<first name>");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnDel = new wxButton(this, ID_DELETE_GUEST_DELETE, "Delete");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_DELETE_GUEST_RADIO_ID, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDeleteGuest::OnRadioID));
    Connect(ID_DELETE_GUEST_RADIO_PASSPORT, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDeleteGuest::OnRadioPassport));
    Connect(ID_DELETE_GUEST_RADIO_NAME, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDeleteGuest::OnRadioName));
    Connect(ID_DELETE_GUEST_RADIO_DELETE_ALL, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDeleteGuest::OnRadioDelAll));
    Connect(ID_DELETE_GUEST_DELETE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogDeleteGuest::OnDelete));
    hSzrTxtFldID = new wxBoxSizer(wxHORIZONTAL);
    hSzrTxtFldPassportSer = new wxBoxSizer(wxHORIZONTAL);
    hSzrTxtFldPassportNum = new wxBoxSizer(wxHORIZONTAL);
    hSzrTxtFldLstName = new wxBoxSizer(wxHORIZONTAL);
    hSzrTxtFldFstName = new wxBoxSizer(wxHORIZONTAL);
    hSzrBtns = new wxBoxSizer(wxHORIZONTAL);
    gSzrID = new wxGridSizer(2);
    gSzrPassport = new wxGridSizer(2);
    gSzrName = new wxGridSizer(2);
    gSzrBtm = new wxGridSizer(2);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrTxtFldID->Add(txtFldID, 1, wxLEFT | wxRIGHT, 5);
    gSzrID->Add(rBtnID, 0, wxEXPAND | wxTOP, 5);
    gSzrID->Add(hSzrTxtFldID, 0, wxEXPAND | wxTOP, 5);
    hSzrTxtFldPassportSer->Add(txtFldPassportSer, 1, wxLEFT, 5);
    hSzrTxtFldPassportNum->Add(txtFldPassportNum, 1, wxLEFT | wxRIGHT, 5);
    gSzrPassport->Add(hSzrTxtFldPassportSer, 0, wxEXPAND | wxTOP, 5);
    gSzrPassport->Add(hSzrTxtFldPassportNum, 0, wxEXPAND | wxTOP, 5);
    hSzrTxtFldFstName->Add(txtFldLstName, 1, wxLEFT, 5);
    hSzrTxtFldLstName->Add(txtFldFstName, 1, wxLEFT | wxRIGHT, 5);
    gSzrName->Add(hSzrTxtFldFstName, 0, wxEXPAND | wxTOP, 5);
    gSzrName->Add(hSzrTxtFldLstName, 0, wxEXPAND | wxTOP, 5);
    hSzrBtns->Add(btnDel, 1, wxLEFT, 5);
    hSzrBtns->Add(btnCancel, 1, wxLEFT | wxRIGHT, 5);
    gSzrBtm->Add(sTxtEmpty, 0, wxTOP | wxBOTTOM, 5);
    gSzrBtm->Add(hSzrBtns, 1, wxEXPAND | wxTOP | wxBOTTOM, 5);
    vSzrMain->Add(gSzrID, 0, wxEXPAND, 0);
    vSzrMain->Add(rBtnPassport, 0, wxEXPAND | wxTOP, 5);
    vSzrMain->Add(gSzrPassport, 0, wxEXPAND, 0);
    vSzrMain->Add(rBtnName, 0, wxEXPAND | wxTOP, 5);
    vSzrMain->Add(gSzrName, 0, wxEXPAND, 0);
    vSzrMain->Add(rBtnDelAll, 0, wxEXPAND | wxTOP, 5);
    vSzrMain->Add(gSzrBtm, 0, wxEXPAND, 0);
    SetSizerAndFit(vSzrMain);
    txtFldPassportSer->Enable(false);
    txtFldPassportNum->Enable(false);
    txtFldLstName->Enable(false);
    txtFldFstName->Enable(false);
    txtFldID->SetFocus();
}

void DialogDeleteGuest::OnRadioID(wxCommandEvent &event)
{
    radio = ID_DELETE_GUEST_RADIO_ID;
    txtFldID->Enable(true);
    txtFldPassportSer->Enable(false);
    txtFldPassportNum->Enable(false);
    txtFldLstName->Enable(false);
    txtFldFstName->Enable(false);
}

void DialogDeleteGuest::OnRadioPassport(wxCommandEvent &event)
{
    radio = ID_DELETE_GUEST_RADIO_PASSPORT;
    txtFldID->Enable(false);
    txtFldPassportSer->Enable(true);
    txtFldPassportNum->Enable(true);
    txtFldLstName->Enable(false);
    txtFldFstName->Enable(false);
}

void DialogDeleteGuest::OnRadioName(wxCommandEvent &event)
{
    radio = ID_DELETE_GUEST_RADIO_NAME;
    txtFldID->Enable(false);
    txtFldPassportSer->Enable(false);
    txtFldPassportNum->Enable(false);
    txtFldLstName->Enable(true);
    txtFldFstName->Enable(true);
}

void DialogDeleteGuest::OnRadioDelAll(wxCommandEvent &event)
{
    radio = ID_DELETE_GUEST_RADIO_DELETE_ALL;
    txtFldID->Enable(false);
    txtFldPassportSer->Enable(false);
    txtFldPassportNum->Enable(false);
    txtFldLstName->Enable(false);
    txtFldFstName->Enable(false);
}

void DialogDeleteGuest::OnDelete(wxCommandEvent &event)
{
    bool info = false;
    try {
        if(radio == ID_DELETE_GUEST_RADIO_ID) {
            info = queryDeleteRow(DF_CNN, dbName, "guest", "guest_id", txtFldID->GetValue().ToStdString());
            if(info == true) {
                wxMessageBox("The guest was deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_GUEST_DELETE);
            }
            else {
                wxMessageBox("There is not guest with such ID!\nNo one was deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
        else if(radio == ID_DELETE_GUEST_RADIO_PASSPORT) {
            info = queryDeleteGuestByPassport(DF_CNN, dbName,
                                              txtFldPassportSer->GetValue().ToStdString(),
                                              txtFldPassportNum->GetValue().ToStdString());
            if(info == true) {
                wxMessageBox("The guest was deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_GUEST_DELETE);
            }
            else {
                wxMessageBox("There is not guest with such passport!\nNo one was deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
        else if(radio == ID_DELETE_GUEST_RADIO_NAME) {
            info = queryDeleteGuestByName(DF_CNN, dbName,
                                          txtFldLstName->GetValue().ToStdString(),
                                          txtFldFstName->GetValue().ToStdString());
            if(info == true) {
                wxMessageBox("All guests with such initials were deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_GUEST_DELETE);
            }
            else {
                wxMessageBox("There are no any guests with such initials!\nNo one was deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
        else if(radio == ID_DELETE_GUEST_RADIO_DELETE_ALL) {
            info = queryClearTable(DF_CNN, dbName, "guest");
            if(info == true) {
                wxMessageBox("All guests have been deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_GUEST_DELETE);
            }
            else {
                wxMessageBox("There are already no guests in this table!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
        else {
            throw std::invalid_argument("What a shame, dude...");
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
}

DialogAddLink::DialogAddLink(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Link guest with booking"), dbName(dbName)
{
    txtFldBookID = new wxTextCtrl(this, wxID_ANY, "<book ID>");
    txtFldGuestID = new wxTextCtrl(this, wxID_ANY, "<guest ID>");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnAdd = new wxButton(this, ID_ADD_LINK_ADD, "Link!");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_ADD_LINK_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogAddLink::OnAdd));
    hSzrFldBookID = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldGuestID = new wxBoxSizer(wxHORIZONTAL);
    hSzrBtns = new wxBoxSizer(wxHORIZONTAL);
    gSzrMain = new wxGridSizer(2);
    hSzrFldBookID->Add(txtFldBookID, 1, wxLEFT | wxRIGHT, 5);
    hSzrFldGuestID->Add(txtFldGuestID, 1, wxLEFT, 5);
    hSzrBtns->Add(btnAdd, 1, wxLEFT, 5);
    hSzrBtns->Add(btnCancel, 1, wxLEFT | wxRIGHT, 5);
    gSzrMain->Add(hSzrFldBookID, 0, wxEXPAND | wxTOP, 5);
    gSzrMain->Add(hSzrFldGuestID, 0, wxEXPAND | wxTOP, 5);
    gSzrMain->Add(sTxtEmpty, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    gSzrMain->Add(hSzrBtns, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    SetSizerAndFit(gSzrMain);
    txtFldBookID->SetFocus();
}

void DialogAddLink::OnAdd(wxCommandEvent &event)
{
    try {
        queryAddLink(DF_CNN, dbName,
                     txtFldBookID->GetValue().ToStdString(),
                     txtFldGuestID->GetValue().ToStdString());
        wxMessageBox("Linked!", "Success!", wxOK | wxCENTRE);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
    EndModal(ID_ADD_LINK_ADD);
}

DialogViewLink::DialogViewLink(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, (std::string) "Links (" + dbName + ")", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), dbName(dbName)
{
    linkLst = new wxRichTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxRE_READONLY);
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnPrintAll = new wxButton(this, ID_VIEW_LINK_PRINT_ALL, "Print All");
    btnClose = new wxButton(this, ID_VIEW_LINK_CLOSE, "Close");
    Connect(ID_VIEW_LINK_PRINT_ALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewLink::OnPrintAll));
    Connect(ID_VIEW_LINK_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewLink::OnClose));
    hSzrBtm = new wxBoxSizer(wxHORIZONTAL);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrBtm->Add(sTxtEmpty, 1);
    hSzrBtm->Add(btnPrintAll, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->AddSpacer(20);
    hSzrBtm->Add(btnClose, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 5);
    vSzrMain->Add(linkLst, 1, wxEXPAND, 0);
    vSzrMain->Add(hSzrBtm, 0, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetMinSize(wxSize(520, 400));
    SetSize(wxSize(600, 400));
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "booking_guest");
        std::string txt;
        for(std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin(); it != tbl.cend(); ++it) {
            for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
                txt += *jt + ' ';
            }
            txt += '\n';
        }
        linkLst->SetValue(txt);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewLink::OnPrintAll(wxCommandEvent &event)
{
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "booking_guest");
        std::string txt;
        for(std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin(); it != tbl.cend(); ++it) {
            for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
                txt += *jt + ' ';
            }
            txt += '\n';
        }
        linkLst->SetValue(txt);
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewLink::OnClose(wxCommandEvent &event)
{
    Destroy();
}

DialogDelLink::DialogDelLink(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Unlink guest with booking"), dbName(dbName)
{
	radio = ID_DELETE_LINK_RADIO_ID;
    rBtnID = new wxRadioButton(this, ID_DELETE_LINK_RADIO_ID, "Delete the link by the booking ID and the guest ID:");
    rBtnDelAll = new wxRadioButton(this, ID_DELETE_LINK_RADIO_DELETE_ALL, "Delete all links (clear the table)");
    txtFldBookingID = new wxTextCtrl(this, wxID_ANY, "<booking ID>");
    txtFldGuestID = new wxTextCtrl(this, wxID_ANY, "<guest ID>");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnDel = new wxButton(this, ID_DELETE_LINK_DELETE, "Delete");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_DELETE_LINK_RADIO_ID, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDelLink::OnRadioID));
    Connect(ID_DELETE_LINK_RADIO_DELETE_ALL, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDelLink::OnRadioDelAll));
    Connect(ID_DELETE_LINK_DELETE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogDelLink::OnDelete));
    hSzrTxtFldID = new wxBoxSizer(wxHORIZONTAL);
    hSzrBtns = new wxBoxSizer(wxHORIZONTAL);
    gSzrID = new wxGridSizer(2);
    gSzrBtm = new wxGridSizer(2);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrTxtFldID->Add(txtFldBookingID, 1, wxLEFT | wxRIGHT, 5);
    hSzrTxtFldID->Add(txtFldGuestID, 1, wxLEFT | wxRIGHT, 5);
    gSzrID->Add(rBtnID, 0, wxEXPAND | wxTOP, 5);
    gSzrID->Add(hSzrTxtFldID, 0, wxEXPAND | wxTOP, 5);
    hSzrBtns->Add(btnDel, 1, wxLEFT, 5);
    hSzrBtns->Add(btnCancel, 1, wxLEFT | wxRIGHT, 5);
    gSzrBtm->Add(sTxtEmpty, 0, wxTOP | wxBOTTOM, 5);
    gSzrBtm->Add(hSzrBtns, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    vSzrMain->Add(gSzrID, 0, wxEXPAND, 0);
    vSzrMain->Add(rBtnDelAll, 0, wxEXPAND | wxTOP, 5);
    vSzrMain->Add(gSzrBtm, 0, wxEXPAND, 0);
    SetSizerAndFit(vSzrMain);
}

void DialogDelLink::OnDelete(wxCommandEvent &event)
{
	std::cout << "deleting links\n";
	bool info = false;
    try {
        if(radio == ID_DELETE_LINK_RADIO_ID) {
			std::cout << "deleting by id\n";
            info = queryDeleteLink(DF_CNN, dbName, txtFldBookingID->GetValue().ToStdString(), txtFldGuestID->GetValue().ToStdString());
            if(info == true) {
                wxMessageBox("The link was deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_LINK_DELETE);
            }
            else {
                wxMessageBox("There is no such a link!\nNothing was deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
        else if(radio == ID_DELETE_LINK_RADIO_DELETE_ALL) {
			std::cout << "deleting all\n";
            info = queryClearTable(DF_CNN, dbName, "booking_guest");
            if(info == true) {
                wxMessageBox("All links have been deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_LINK_DELETE);
            }
            else {
                wxMessageBox("There are already no links in this table!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
}

void DialogDelLink::OnRadioID(wxCommandEvent &event)
{
    radio = ID_DELETE_LINK_RADIO_ID;
    txtFldBookingID->Enable(true);
    txtFldGuestID->Enable(true);
}

void DialogDelLink::OnRadioDelAll(wxCommandEvent &event)
{
    radio = ID_DELETE_LINK_RADIO_DELETE_ALL;
    txtFldBookingID->Enable(false);
    txtFldGuestID->Enable(false);
}

DialogDeleteRoom::DialogDeleteRoom(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Delete Room"), dbName(dbName)
{
    radio = ID_DELETE_ROOM_RADIO_ID;
    rBtnID = new wxRadioButton(this, ID_DELETE_ROOM_RADIO_ID, "Delete the room by ID:");
    rBtnDelAll = new wxRadioButton(this, ID_DELETE_ROOM_RADIO_DELETE_ALL, "Delete all rooms (clear the table)");
    txtFldID = new wxTextCtrl(this, wxID_ANY, "<room ID>");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnDel = new wxButton(this, ID_DELETE_ROOM_DELETE, "Delete");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_DELETE_ROOM_RADIO_ID, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDeleteRoom::OnRadioID));
    Connect(ID_DELETE_ROOM_RADIO_DELETE_ALL, wxEVT_RADIOBUTTON, wxCommandEventHandler(DialogDeleteRoom::OnRadioDelAll));
    Connect(ID_DELETE_ROOM_DELETE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogDeleteRoom::OnDelete));
    hSzrTxtFldID = new wxBoxSizer(wxHORIZONTAL);
    hSzrBtns = new wxBoxSizer(wxHORIZONTAL);
    gSzrID = new wxGridSizer(2);
    gSzrBtm = new wxGridSizer(2);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrTxtFldID->Add(txtFldID, 1, wxLEFT | wxRIGHT, 5);
    gSzrID->Add(rBtnID, 0, wxEXPAND | wxTOP, 5);
    gSzrID->Add(hSzrTxtFldID, 0, wxEXPAND | wxTOP, 5);
    hSzrBtns->Add(btnDel, 1, wxLEFT, 5);
    hSzrBtns->Add(btnCancel, 1, wxLEFT | wxRIGHT, 5);
    gSzrBtm->Add(sTxtEmpty, 0, wxTOP | wxBOTTOM, 5);
    gSzrBtm->Add(hSzrBtns, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    vSzrMain->Add(gSzrID, 0, wxEXPAND, 0);
    vSzrMain->Add(rBtnDelAll, 0, wxEXPAND | wxTOP, 5);
    vSzrMain->Add(gSzrBtm, 0, wxEXPAND, 0);
    SetSizerAndFit(vSzrMain);
    txtFldID->SetFocus();
}

void DialogDeleteRoom::OnRadioID(wxCommandEvent &event)
{
    radio = ID_DELETE_ROOM_RADIO_ID;
    txtFldID->Enable(true);
}

void DialogDeleteRoom::OnRadioDelAll(wxCommandEvent &event)
{
    radio = ID_DELETE_ROOM_RADIO_DELETE_ALL;
    txtFldID->Enable(false);
}

void DialogDeleteRoom::OnDelete(wxCommandEvent &event)
{
	bool info = false;
    try {
        if(radio == ID_DELETE_ROOM_RADIO_ID) {
            info = queryDeleteRow(DF_CNN, dbName, "hotel_room", "hotel_room_id", txtFldID->GetValue().ToStdString());
            if(info == true) {
                wxMessageBox("The room was deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_ROOM_DELETE);
            }
            else {
                wxMessageBox("There is no room with such ID!\nNothing was deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
        else if(radio == ID_DELETE_ROOM_RADIO_DELETE_ALL) {
            info = queryClearTable(DF_CNN, dbName, "hotel_room");
            if(info == true) {
                wxMessageBox("All rooms have been deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_ROOM_DELETE);
            }
            else {
                wxMessageBox("There are already no rooms in this table!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
}

DialogAddRoom::DialogAddRoom(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Add hotel room"), dbName(dbName)
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

FrameMenu::FrameMenu() :
    wxFrame(NULL, wxID_ANY, "HSE Hotel Client")
{
    modeTest = false;
    SetIcon(wxIcon(PATH_ICON));
    panelTopLeft = new wxPanel(this, wxID_ANY);
    panelTopRight = new wxPanel(this, wxID_ANY);
    panelBottomLeft = new wxPanel(this, wxID_ANY);
    panelBottomRight = new wxPanel(this, wxID_ANY);
    textFieldDBName = new wxTextCtrl(panelTopLeft, wxID_ANY, "clientdb");
    buttonCheckDB = new wxButton(panelTopLeft, ID_CHECK_DB, "Check");
    buttonCreateDB = new wxButton(panelTopLeft, ID_CREATE_DB, "Create");
    buttonDropDB = new wxButton(panelTopLeft, ID_DROP_DB, "Delete");
    buttonModeTest = new wxButton(panelTopLeft, ID_MODE_TEST, "Test mode");
    btnAddBook = new wxButton(panelTopRight, ID_ADD_BOOKING, "Add");
    btnViewBook = new wxButton(panelTopRight, ID_VIEW_BOOKING, "View");
    btnDelBook = new wxButton(panelTopRight, ID_DELETE_BOOKING, "Delete");
    buttonAddGuest = new wxButton(panelTopRight, ID_ADD_GUEST, "Add");
    btnViewGuest = new wxButton(panelTopRight, ID_VIEW_GUEST, "View");
    buttonDeleteGuest = new wxButton(panelTopRight, ID_DELETE_GUEST, "Delete");
    btnAddLink = new wxButton(panelTopRight, ID_ADD_LINK, "Add");
    btnViewLink = new wxButton(panelTopRight, ID_VIEW_LINK, "View");
    btnDelLink = new wxButton(panelTopRight, ID_DELETE_LINK, "Delete");
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
    Connect(ID_VIEW_GUEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnViewGuest));
    Connect(ID_DELETE_GUEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDeleteGuest));
    Connect(ID_ADD_LINK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAddLink));
    Connect(ID_VIEW_LINK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnViewLink));
    Connect(ID_DELETE_LINK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDelLink));
    Connect(ID_ADD_ROOM, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAddRoom));
    Connect(ID_VIEW_ROOM, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnViewRoom));
    Connect(ID_DELETE_ROOM, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnDeleteRoom));
    Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAbout));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnExit));
    vSizerControlDB = new wxStaticBoxSizer(wxVERTICAL, panelTopLeft, "Database");
    vSzrControlBook = new wxStaticBoxSizer(wxVERTICAL, panelTopRight, "Booking");
    vSizerControlGuest = new wxStaticBoxSizer(wxVERTICAL, panelTopRight, "Guest");
    vSzrControlLink = new wxStaticBoxSizer(wxVERTICAL, panelTopRight, "Link");
    vSizerControlRoom = new wxStaticBoxSizer(wxVERTICAL, panelTopRight, "Hotel room");
    vSizerTopLeft = new wxBoxSizer(wxVERTICAL);
    gSizerTopRight = new wxGridSizer(2);
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
    gSizerTopRight->Add(vSzrControlBook, 0, wxALIGN_CENTER | wxTOP, 5);
    vSizerControlGuest->Add(buttonAddGuest, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlGuest->Add(btnViewGuest, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlGuest->Add(buttonDeleteGuest, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    gSizerTopRight->Add(vSizerControlGuest, 0, wxALIGN_CENTER | wxTOP, 5);
    vSzrControlLink->Add(btnAddLink, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSzrControlLink->Add(btnViewLink, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSzrControlLink->Add(btnDelLink, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    gSizerTopRight->Add(vSzrControlLink, 0, wxALIGN_CENTER | wxTOP, 5);
    vSizerControlRoom->Add(btnAddRoom, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlRoom->Add(btnViewRoom, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlRoom->Add(btnDelRoom, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    gSizerTopRight->Add(vSizerControlRoom, 0, wxALIGN_CENTER | wxTOP, 5);
    hSizerTop->Add(panelTopLeft, 0, wxEXPAND, 0);
    hSizerTop->Add(panelTopRight, 1, wxEXPAND, 0);
    vSizerBottomLeft->Add(buttonAbout, 0, wxALIGN_LEFT | wxALL, 10);
    vSizerBottomRight->Add(buttonExit, 0, wxALIGN_RIGHT | wxALL, 10);
    hSizerBottom->Add(panelBottomLeft, 1, wxEXPAND, 0);
    hSizerBottom->Add(panelBottomRight, 1, wxEXPAND, 0);
    vSizerMain->Add(hSizerTop, 1, wxEXPAND, 0);
    vSizerMain->Add(hSizerBottom, 0, wxEXPAND, 0);
    panelTopLeft->SetSizer(vSizerTopLeft);
    panelTopRight->SetSizer(gSizerTopRight);
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
    btnAddLink->Enable(true);
    btnViewLink->Enable(true);
    btnDelLink->Enable(true);
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
    btnAddLink->Enable(false);
    btnViewLink->Enable(false);
    btnDelLink->Enable(false);
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
    btnAddLink->Enable(false);
    btnViewLink->Enable(false);
    btnDelLink->Enable(false);
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
    DialogViewBook *dialogViewBook = new DialogViewBook(this, textFieldDBName->GetValue().ToStdString());
    dialogViewBook->Show(true);
}

void FrameMenu::OnDeleteBook(wxCommandEvent &event)
{
    DialogDeleteBook *dialogDeleteBook = new DialogDeleteBook(this, textFieldDBName->GetValue().ToStdString());
    dialogDeleteBook->ShowModal();
    dialogDeleteBook->Destroy();
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

void FrameMenu::OnAddLink(wxCommandEvent &event)
{
    DialogAddLink *dialogAddLink = new DialogAddLink(this, textFieldDBName->GetValue().ToStdString());
    dialogAddLink->ShowModal();
    dialogAddLink->Destroy();
}

void FrameMenu::OnViewLink(wxCommandEvent &event)
{
    DialogViewLink *dialogViewLink = new DialogViewLink(this, textFieldDBName->GetValue().ToStdString());
    dialogViewLink->Show(true);
}

void FrameMenu::OnDelLink(wxCommandEvent &event)
{
    DialogDelLink *dialogDelLink = new DialogDelLink(this, textFieldDBName->GetValue().ToStdString());
    dialogDelLink->ShowModal();
    dialogDelLink->Destroy();
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

void FrameMenu::OnDeleteRoom(wxCommandEvent &event)
{
    DialogDeleteRoom *dialogDeleteRoom = new DialogDeleteRoom(this, textFieldDBName->GetValue().ToStdString());
    dialogDeleteRoom->ShowModal();
    dialogDeleteRoom->Destroy();
}

void FrameMenu::OnAbout(wxCommandEvent &event)
{
    wxMessageBox((std::string) "HSE Hotel Client, ver." + VERSION + "\n" + GITHUB, "About HSE Hotel Client", wxOK);
}

void FrameMenu::OnExit(wxCommandEvent &event)
{
    Close(true);
}
