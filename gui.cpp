#include "gui.hpp"

DialogViewOverall::DialogViewOverall(wxWindow *parent, std::string dbName):
    wxDialog(parent, wxID_ANY, (std::string) "Overall table (" + dbName + ")", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), dbName(dbName)
{
    overallTbl = new wxListView(this, wxID_ANY);
    txtFldLstName = new wxTextCtrl(this, wxID_ANY, "<last name>");
    txtFldFstName = new wxTextCtrl(this, wxID_ANY, "<first name>");
    btnFind = new wxButton(this, ID_VIEW_OVERALL_FIND, "Find");
    btnPrintAll = new wxButton(this, ID_VIEW_OVERALL_PRINT_ALL, "Print All");
    btnClose = new wxButton(this, ID_VIEW_OVERALL_CLOSE, "Close");
    Connect(ID_VIEW_OVERALL_FIND, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewOverall::OnFind));
    Connect(ID_VIEW_OVERALL_PRINT_ALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewOverall::OnPrintAll));
    Connect(ID_VIEW_OVERALL_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogViewOverall::OnClose));
    hSzrBtm = new wxBoxSizer(wxHORIZONTAL);
    vSzrMain = new wxBoxSizer(wxVERTICAL);
    hSzrBtm->Add(txtFldLstName, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->Add(txtFldFstName, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->AddSpacer(20);
    hSzrBtm->Add(btnFind, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->Add(btnPrintAll, 0, wxLEFT | wxTOP | wxBOTTOM, 5);
    hSzrBtm->AddSpacer(20);
    hSzrBtm->Add(btnClose, 0, wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 5);
    vSzrMain->Add(overallTbl, 1, wxEXPAND, 0);
    vSzrMain->Add(hSzrBtm, 0, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetMinSize(wxSize(520, 400));
    SetSize(wxSize(600, 400));
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintOverallTable(DF_CNN, dbName);
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            overallTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            overallTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                overallTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewOverall::OnFind(wxCommandEvent &event)
{
    overallTbl->ClearAll();
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryFindBookingByName(DF_CNN, dbName, txtFldLstName->GetValue().ToStdString(), txtFldFstName->GetValue().ToStdString());
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            overallTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            overallTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                overallTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewOverall::OnPrintAll(wxCommandEvent &event)
{
    overallTbl->ClearAll();
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintOverallTable(DF_CNN, dbName);
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            overallTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            overallTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                overallTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewOverall::OnClose(wxCommandEvent &event)
{
    Destroy();
}

DialogAddBook::DialogAddBook(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Add booking"), dbName(dbName)
{
    staticTextArrival = new wxStaticText(this, wxID_ANY, "Arrival:");
    staticTextDeparture = new wxStaticText(this, wxID_ANY, "Departure:");
    staticTextRoom = new wxStaticText(this, wxID_ANY, "Room:");
    staticTextCard = new wxStaticText(this, wxID_ANY, "Bank card:");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    txtFldArrival = new wxTextCtrl(this, wxID_ANY, "");
    txtFldDeparture = new wxTextCtrl(this, wxID_ANY, "");
    txtFldRoom = new wxTextCtrl(this, wxID_ANY, "");
    txtFldCard = new wxTextCtrl(this, wxID_ANY, "");
    btnAdd = new wxButton(this, ID_ADD_BOOKING_ADD, "Add");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_ADD_BOOKING_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogAddBook::OnAdd));
    hSzrStaticTextArrival = new wxBoxSizer(wxHORIZONTAL);
    hSzrStaticTextDeparture = new wxBoxSizer(wxHORIZONTAL);
    hSzrStaticTextRoom = new wxBoxSizer(wxHORIZONTAL);
    hSzrStaticTextCard = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldArrival = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldDeparture = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldDate = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldRoom = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldCard = new wxBoxSizer(wxHORIZONTAL);
    hSzrBtns = new wxBoxSizer(wxHORIZONTAL);
    gSzrMain = new wxGridSizer(2);
    hSzrStaticTextArrival->Add(staticTextArrival, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSzrStaticTextDeparture->Add(staticTextDeparture, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSzrStaticTextRoom->Add(staticTextRoom, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSzrStaticTextCard->Add(staticTextCard, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSzrFldArrival->Add(txtFldArrival, 1, wxLEFT | wxRIGHT, 5);
    hSzrFldDeparture->Add(txtFldDeparture, 1, wxLEFT | wxRIGHT, 5);
    hSzrFldRoom->Add(txtFldRoom, 1, wxLEFT | wxRIGHT, 5);
    hSzrFldCard->Add(txtFldCard, 1, wxLEFT | wxRIGHT, 5);
    hSzrBtns->Add(btnAdd, 1, wxTOP | wxBOTTOM | wxLEFT, 5);
    hSzrBtns->Add(btnCancel, 1, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    gSzrMain->Add(hSzrStaticTextArrival, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrStaticTextRoom, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrFldArrival, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrFldRoom, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrStaticTextDeparture, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrStaticTextCard, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrFldDeparture, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrFldCard, 0, wxEXPAND, 0);
    gSzrMain->Add(sTxtEmpty, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrBtns, 0, wxEXPAND, 0);
    SetSizerAndFit(gSzrMain);
    txtFldArrival->SetFocus();
}

void DialogAddBook::OnAdd(wxCommandEvent &event)
{
    try {
        queryAddBook(DF_CNN, dbName,
                     txtFldArrival->GetValue().ToStdString(),
                     txtFldDeparture->GetValue().ToStdString(),
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

DialogEditBook::DialogEditBook(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Edit book"), dbName(dbName)
{
    staticTextBookID = new wxStaticText(this, wxID_ANY, "Booking ID:");
    staticTextRoomID = new wxStaticText(this, wxID_ANY, "Room number:");
    txtFldBookID = new wxTextCtrl(this, wxID_ANY, "");
    txtFldRoomID = new wxTextCtrl(this, wxID_ANY, "");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnApply = new wxButton(this, ID_EDIT_BOOKING_APPLY, "Apply");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_EDIT_BOOKING_APPLY, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogEditBook::OnApply));
    hSzrStaticTextBookID = new wxBoxSizer(wxHORIZONTAL);
    hSzrStaticTextRoomID = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldBookID = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldRoomID = new wxBoxSizer(wxHORIZONTAL);
    hSzrBtns = new wxBoxSizer(wxHORIZONTAL);
    gSzrMain = new wxGridSizer(2);
    hSzrStaticTextBookID->Add(staticTextBookID, 1, wxCENTRE | wxLEFT, 5);
    hSzrStaticTextRoomID->Add(staticTextRoomID, 1, wxCENTRE | wxLEFT | wxRIGHT, 5);
    hSzrFldBookID->Add(txtFldBookID, 1, wxLEFT, 5);
    hSzrFldRoomID->Add(txtFldRoomID, 1, wxLEFT | wxRIGHT, 5);
    hSzrBtns->Add(btnApply, 1, wxLEFT, 5);
    hSzrBtns->Add(btnCancel, 1, wxLEFT | wxRIGHT, 5);
    gSzrMain->Add(hSzrStaticTextBookID, 0, wxEXPAND | wxTOP, 5);
    gSzrMain->Add(hSzrStaticTextRoomID, 0, wxEXPAND | wxTOP, 5);
    gSzrMain->Add(hSzrFldBookID, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrFldRoomID, 0, wxEXPAND, 0);
    gSzrMain->Add(sTxtEmpty, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    gSzrMain->Add(hSzrBtns, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);
    SetSizerAndFit(gSzrMain);
    txtFldBookID->SetFocus();
}

void DialogEditBook::OnApply(wxCommandEvent &event)
{
   bool info = false;
   try {
        info = queryEditBook(DF_CNN, dbName,
                      txtFldBookID->GetValue().ToStdString(),
                      txtFldRoomID->GetValue().ToStdString());
        if (info == true){
			wxMessageBox("Applied!", "Success!", wxOK | wxCENTRE);
			EndModal(ID_EDIT_BOOKING);
		}
		else {
			wxMessageBox("No update has happened!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
		}
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
        return;
    }
}

DialogViewBook::DialogViewBook(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, (std::string) "Bookings (" + dbName + ")", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), dbName(dbName)
{
    bookTbl = new wxListView(this, wxID_ANY);
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
    vSzrMain->Add(bookTbl, 1, wxEXPAND, 0);
    vSzrMain->Add(hSzrBtm, 0, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetMinSize(wxSize(520, 400));
    SetSize(wxSize(600, 400));
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "booking");
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            bookTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            bookTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                bookTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewBook::OnPrintAll(wxCommandEvent &event)
{
    bookTbl->ClearAll();
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "booking");
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            bookTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            bookTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                bookTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
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
	staticTextLastName = new wxStaticText(this, wxID_ANY, "Last name:");
    textFieldLastName = new wxTextCtrl(this, wxID_ANY, "");
    staticTextFirstName = new wxStaticText(this, wxID_ANY, "First name:");
    textFieldFirstName = new wxTextCtrl(this, wxID_ANY, "");
    staticTextPatronymic = new wxStaticText(this, wxID_ANY, "Patronymic:");
    textFieldPatronymic = new wxTextCtrl(this, wxID_ANY, "");
    staticTextPassportSeries = new wxStaticText(this, wxID_ANY, "Passport series:");
    textFieldPassportSeries = new wxTextCtrl(this, wxID_ANY, "");
    staticTextPassportNumber = new wxStaticText(this, wxID_ANY, "Passport number:");
    textFieldPassportNumber = new wxTextCtrl(this, wxID_ANY, "");
    staticTextPhone = new wxStaticText(this, wxID_ANY, "Phone:");
    textFieldPhone = new wxTextCtrl(this, wxID_ANY, "");
    buttonAdd = new wxButton(this, ID_ADD_GUEST_ADD, "Add");
    buttonCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_ADD_GUEST_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogAddGuest::OnAdd));
    hSizerRowFstLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFstRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSndLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSndRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowTrdLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowTrdRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFthLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFthRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFfhLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFfhRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSxthLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSxthRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSvthLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSvthRight = new wxBoxSizer(wxHORIZONTAL);
    gSizerMain = new wxGridSizer(2);
    hSizerRowFstLeft->Add(staticTextLastName, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowFstRight->Add(staticTextPassportSeries, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowSndLeft->Add(textFieldLastName, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowSndRight->Add(textFieldPassportSeries, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowTrdLeft->Add(staticTextFirstName, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowTrdRight->Add(staticTextPassportNumber, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowFthLeft->Add(textFieldFirstName, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowFthRight->Add(textFieldPassportNumber, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowFfhLeft->Add(staticTextPatronymic, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowFfhRight->Add(staticTextPhone, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowSxthLeft->Add(textFieldPatronymic, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowSxthRight->Add(textFieldPhone, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowSvthRight->Add(buttonAdd, 1, wxTOP | wxBOTTOM | wxLEFT, 5);
    hSizerRowSvthRight->Add(buttonCancel, 1, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    gSizerMain->Add(hSizerRowFstLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFstRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSndLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSndRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowTrdLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowTrdRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFthLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFthRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFfhLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFfhRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSxthLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSxthRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSvthLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSvthRight, 0, wxEXPAND, 0);
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
    guestTbl = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
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
    vSzrMain->Add(guestTbl, 1, wxEXPAND, 0);
    vSzrMain->Add(hSzrBtm, 0, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetMinSize(wxSize(520, 400));
    SetSize(wxSize(600, 400));
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "guest");
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            guestTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            guestTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                guestTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewGuest::OnFind(wxCommandEvent &event)
{
    guestTbl->ClearAll();
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "guest");
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            guestTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            if(it == tbl.cbegin() || (it->at(1) == txtFldLstName->GetValue() && it->at(2) == txtFldFstName->GetValue())) {
                guestTbl->InsertItem(i, *(it->cbegin()));
                int j = 1;
                for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                    guestTbl->SetItem(i, j++, *jt);
                }
                ++i;
            }
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
   }
}

void DialogViewGuest::OnPrintAll(wxCommandEvent &event)
{
    guestTbl->ClearAll();
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "guest");
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            guestTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            guestTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                guestTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewGuest::OnClose(wxCommandEvent &event)
{
    Destroy();
}

DialogDeleteGuest::DialogDeleteGuest(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Delete guest"), dbName(dbName)
{
    radio = ID_DELETE_GUEST_RADIO_ID;
    rBtnID = new wxRadioButton(this, ID_DELETE_GUEST_RADIO_ID, "Delete a guest by ID:");
    rBtnPassport = new wxRadioButton(this, ID_DELETE_GUEST_RADIO_PASSPORT, "Delete a guest by passport series and number:");
    rBtnName = new wxRadioButton(this, ID_DELETE_GUEST_RADIO_NAME, "Delete all guests with specified last name and first name:");
    rBtnDelAll = new wxRadioButton(this, ID_DELETE_GUEST_RADIO_DELETE_ALL, "Delete all guests (clear the table)");
    txtFldID = new wxTextCtrl(this, wxID_ANY, "<guest ID>");
    txtFldPassportSer = new wxTextCtrl(this, wxID_ANY, "<passport series>");
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
                wxMessageBox("There are no guesta with such passport data!\nNo one was deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
            }
        }
        else if(radio == ID_DELETE_GUEST_RADIO_NAME) {
            info = queryDeleteGuestByName(DF_CNN, dbName,
                                          txtFldLstName->GetValue().ToStdString(),
                                          txtFldFstName->GetValue().ToStdString());
            if(info == true) {
                wxMessageBox("All guests with such a name were deleted!", "Success!", wxOK | wxCENTRE);
                EndModal(ID_DELETE_GUEST_DELETE);
            }
            else {
                wxMessageBox("There are no guests with such a name!\nNo one was deleted!", "Warning!", wxOK | wxCENTRE | wxICON_EXCLAMATION);
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
    staticTextBookID = new wxStaticText(this, wxID_ANY, "Booking ID:");
    staticTextGuestID = new wxStaticText(this, wxID_ANY, "Guest ID:");
    txtFldBookID = new wxTextCtrl(this, wxID_ANY, "");
    txtFldGuestID = new wxTextCtrl(this, wxID_ANY, "");
    sTxtEmpty = new wxStaticText(this, wxID_ANY, wxEmptyString);
    btnAdd = new wxButton(this, ID_ADD_LINK_ADD, "Link");
    btnCancel = new wxButton(this, wxID_OK, "Cancel");
    Connect(ID_ADD_LINK_ADD, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DialogAddLink::OnAdd));
    hSzrStaticTextBookID = new wxBoxSizer(wxHORIZONTAL);
    hSzrStaticTextGuestID = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldBookID = new wxBoxSizer(wxHORIZONTAL);
    hSzrFldGuestID = new wxBoxSizer(wxHORIZONTAL);
    hSzrBtns = new wxBoxSizer(wxHORIZONTAL);
    gSzrMain = new wxGridSizer(2);
    hSzrStaticTextBookID->Add(staticTextBookID, 1, wxCENTRE | wxLEFT | wxRIGHT, 5);
    hSzrStaticTextGuestID->Add(staticTextGuestID, 1, wxCENTRE | wxLEFT | wxRIGHT, 5);
    hSzrFldBookID->Add(txtFldBookID, 1, wxLEFT | wxRIGHT, 5);
    hSzrFldGuestID->Add(txtFldGuestID, 1, wxLEFT | wxRIGHT, 5);
    hSzrBtns->Add(btnAdd, 1, wxLEFT, 5);
    hSzrBtns->Add(btnCancel, 1, wxLEFT | wxRIGHT, 5);
    gSzrMain->Add(hSzrStaticTextBookID, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrStaticTextGuestID, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrFldBookID, 0, wxEXPAND, 0);
    gSzrMain->Add(hSzrFldGuestID, 0, wxEXPAND, 0);
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
    linkTbl = new wxListView(this, wxID_ANY);
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
    vSzrMain->Add(linkTbl, 1, wxEXPAND, 0);
    vSzrMain->Add(hSzrBtm, 0, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetMinSize(wxSize(520, 400));
    SetSize(wxSize(600, 400));
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "booking_guest");
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            linkTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            linkTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                linkTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewLink::OnPrintAll(wxCommandEvent &event)
{
    linkTbl->ClearAll();
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "booking_guest");
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            linkTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            linkTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                linkTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
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
	bool info = false;
    try {
        if(radio == ID_DELETE_LINK_RADIO_ID) {
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

DialogAddRoom::DialogAddRoom(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, "Add hotel room"), dbName(dbName)
{
    staticTextRoomId = new wxStaticText(this, wxID_ANY, "Hotel room ID:");
    textFieldRoomId = new wxTextCtrl(this, wxID_ANY, "");
    staticTextPrice = new wxStaticText(this, wxID_ANY, "Price per day:");
    textFieldPrice = new wxTextCtrl(this, wxID_ANY, "");
    staticTextNumberOfRooms = new wxStaticText(this, wxID_ANY, "Number of rooms:");
    textFieldNumberOfRooms = new wxTextCtrl(this, wxID_ANY, "");
    staticTextArea = new wxStaticText(this, wxID_ANY, "Area:");
    textFieldArea = new wxTextCtrl(this, wxID_ANY, "");
    staticTextServiceClass = new wxStaticText(this, wxID_ANY, "Service class:");
    textFieldServiceClass = new wxTextCtrl(this, wxID_ANY, "");
    staticTextKitchen = new wxStaticText(this, wxID_ANY, "Kitchen:");
    textFieldKitchen = new wxTextCtrl(this, wxID_ANY, "");
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
    hSizerRowFfhLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowFfhRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSxthLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSxthRight = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSvthLeft = new wxBoxSizer(wxHORIZONTAL);
    hSizerRowSvthRight = new wxBoxSizer(wxHORIZONTAL);
    gSizerMain = new wxGridSizer(2);
    hSizerRowFstLeft->Add(staticTextRoomId, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowFstRight->Add(staticTextPrice, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowSndLeft->Add(textFieldRoomId, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowSndRight->Add(textFieldPrice, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowTrdLeft->Add(staticTextNumberOfRooms, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowTrdRight->Add(staticTextArea, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowFthLeft->Add(textFieldNumberOfRooms, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowFthRight->Add(textFieldArea, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowFfhLeft->Add(staticTextServiceClass, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowFfhRight->Add(staticTextKitchen, 1, wxALIGN_CENTRE | wxLEFT | wxRIGHT, 5);
    hSizerRowSxthLeft->Add(textFieldServiceClass, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowSxthRight->Add(textFieldKitchen, 1, wxLEFT | wxRIGHT, 5);
    hSizerRowSvthRight->Add(buttonAdd, 1, wxTOP | wxBOTTOM | wxLEFT, 5);
    hSizerRowSvthRight->Add(buttonCancel, 1, wxTOP | wxBOTTOM | wxLEFT | wxRIGHT, 5);
    gSizerMain->Add(hSizerRowFstLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFstRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSndLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSndRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowTrdLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowTrdRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFthLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFthRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFfhLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowFfhRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSxthLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSxthRight, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSvthLeft, 0, wxEXPAND, 0);
    gSizerMain->Add(hSizerRowSvthRight, 0, wxEXPAND, 0);
    SetSizerAndFit(gSizerMain);
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

DialogViewRoom::DialogViewRoom(wxWindow *parent, std::string dbName) :
    wxDialog(parent, wxID_ANY, (std::string) "Hotel Rooms (" + dbName + ")", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER), dbName(dbName)
{
    roomTbl = new wxListView(this, wxID_ANY);
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
    vSzrMain->Add(roomTbl, 1, wxEXPAND, 0);
    vSzrMain->Add(hSzrBtm, 0, wxEXPAND, 0);
    SetSizer(vSzrMain);
    SetMinSize(wxSize(520, 400));
    SetSize(wxSize(600, 400));
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "hotel_room");
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            roomTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            roomTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                roomTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewRoom::OnFind(wxCommandEvent &event)
{
    roomTbl->ClearAll();
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryFindRooms(DF_CNN, dbName, txtFldArrival->GetValue().ToStdString(), txtFldDeparture->GetValue().ToStdString());
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            roomTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            roomTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                roomTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewRoom::OnPrintAll(wxCommandEvent &event)
{
    roomTbl->ClearAll();
    try {
        std::vector<std::vector<std::string>> tbl;
        tbl = queryPrintTable(DF_CNN, dbName, "hotel_room");
        std::vector<std::vector<std::string>>::const_iterator it = tbl.cbegin();
        for(std::vector<std::string>::const_iterator jt = it->cbegin(); jt != it->cend(); ++jt) {
            roomTbl->AppendColumn(*jt);
        }
        ++it;
        int i = 0;
        for(; it != tbl.cend(); ++it) {
            roomTbl->InsertItem(i, *(it->cbegin()));
            int j = 1;
            for(std::vector<std::string>::const_iterator jt = it->cbegin() + 1; jt != it->cend(); ++jt) {
                roomTbl->SetItem(i, j++, *jt);
            }
            ++i;
        }
    }
    catch (const std::exception &e) {
        wxMessageBox((std::string) "Error:\n" + e.what(), "Error!", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void DialogViewRoom::OnClose(wxCommandEvent &event)
{
    Destroy();
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
    btnViewOverall = new wxButton(panelTopLeft, ID_VIEW_OVERALL, "Open\noverall\ntable");
    buttonModeTest = new wxButton(panelTopLeft, ID_MODE_TEST, "Test mode");
    btnAddBook = new wxButton(panelTopRight, ID_ADD_BOOKING, "Add");
    btnEditBook = new wxButton(panelTopRight, ID_EDIT_BOOKING, "Edit");
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
    Connect(ID_VIEW_OVERALL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnViewOverall));
    Connect(ID_MODE_TEST, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnModeTest));
    Connect(ID_ADD_BOOKING, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAddBook));
    Connect(ID_EDIT_BOOKING, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnEditBook));
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
    vSizerControlDB->Add(buttonDropDB, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSizerControlDB->Add(btnViewOverall, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    vSizerTopLeft->Add(vSizerControlDB, 0, wxALIGN_CENTER | wxTOP | wxLEFT, 5);
    vSizerTopLeft->AddSpacer(20);
    vSizerTopLeft->Add(buttonModeTest, 0, wxALIGN_CENTER | wxTOP | wxLEFT, 5);
    vSzrControlBook->Add(btnAddBook, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
    vSzrControlBook->Add(btnEditBook, 0, wxALIGN_CENTER | wxTOP | wxLEFT | wxRIGHT, 5);
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
    btnViewOverall->Enable(true);
    btnAddBook->Enable(true);
    btnEditBook->Enable(true);
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
    btnViewOverall->Enable(false);
    btnAddBook->Enable(false);
    btnEditBook->Enable(false);
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
    btnViewOverall->Enable(false);
    btnAddBook->Enable(false);
    btnEditBook->Enable(false);
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

void FrameMenu::OnViewOverall(wxCommandEvent &event)
{
    DialogViewOverall *dialogViewOverall = new DialogViewOverall(this, textFieldDBName->GetValue().ToStdString());
    dialogViewOverall->Show(true);
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

void FrameMenu::OnEditBook(wxCommandEvent &event)
{
    DialogEditBook * dialogEditBook = new DialogEditBook(this, textFieldDBName->GetValue().ToStdString());
    dialogEditBook->ShowModal();
    dialogEditBook->Destroy();
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
