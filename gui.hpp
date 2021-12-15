#ifndef GUI_HPP
#define GUI_HPP

#include <iostream>
#include <vector>
#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include "dbi.hpp"

#define VERSION   "2021.12.14"
#define GITHUB    "https://github.com/NikolayKuraga/hse-hotel"
#define PATH_ICON "icon.png"

enum {
    ONE_HUNDRED = 100,
    ID_CHECK_DB,
    ID_CREATE_DB,
    ID_DROP_DB,
    ID_VIEW_OVERALL,
    ID_VIEW_OVERALL_FIND,
    ID_VIEW_OVERALL_PRINT_ALL,
    ID_VIEW_OVERALL_CLOSE,
    ID_MODE_TEST,
    ID_ADD_BOOKING,
    ID_ADD_BOOKING_ADD,
    ID_EDIT_BOOKING,
    ID_EDIT_BOOKING_APPLY,
    ID_VIEW_BOOKING,
    ID_VIEW_BOOKING_PRINT_ALL,
    ID_VIEW_BOOKING_CLOSE,
    ID_DELETE_BOOKING,
    ID_DELETE_BOOKING_RADIO_ID,
    ID_DELETE_BOOKING_RADIO_DELETE_ALL,
    ID_DELETE_BOOKING_DELETE,
    ID_ADD_GUEST,
    ID_ADD_GUEST_ADD,
    ID_VIEW_GUEST,
    ID_VIEW_GUEST_FIND,
    ID_VIEW_GUEST_PRINT_ALL,
    ID_VIEW_GUEST_CLOSE,
    ID_DELETE_GUEST,
    ID_DELETE_GUEST_RADIO_ID,
    ID_DELETE_GUEST_RADIO_PASSPORT,
    ID_DELETE_GUEST_RADIO_NAME,
    ID_DELETE_GUEST_RADIO_DELETE_ALL,
    ID_DELETE_GUEST_DELETE,
    ID_ADD_LINK,
    ID_ADD_LINK_ADD,
    ID_VIEW_LINK,
    ID_VIEW_LINK_PRINT_ALL,
    ID_VIEW_LINK_CLOSE,
    ID_DELETE_LINK,
    ID_DELETE_LINK_DELETE,
    ID_DELETE_LINK_RADIO_ID,
    ID_DELETE_LINK_RADIO_DELETE_ALL,
    ID_ADD_ROOM,
    ID_ADD_ROOM_ADD,
    ID_VIEW_ROOM,
    ID_VIEW_ROOM_FIND,
    ID_VIEW_ROOM_PRINT_ALL,
    ID_VIEW_ROOM_CLOSE,
    ID_DELETE_ROOM,
    ID_DELETE_ROOM_DELETE,
    ID_DELETE_ROOM_RADIO_ID,
    ID_DELETE_ROOM_RADIO_DELETE_ALL
};

class DialogViewOverall : public wxDialog
{
public:
    DialogViewOverall(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxRichTextCtrl *overallLst;
    wxTextCtrl *txtFldLstName;
    wxTextCtrl *txtFldFstName;
    wxButton *btnFind;
    wxButton *btnPrintAll;
    wxButton *btnClose;
    wxBoxSizer *hSzrBtm;
    wxBoxSizer *vSzrMain;
    
    void OnFind(wxCommandEvent &event);
    void OnPrintAll(wxCommandEvent &event);
    void OnClose(wxCommandEvent &event);
};

class DialogAddBook : public wxDialog
{
public:
    DialogAddBook(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxTextCtrl *txtFldArrival;
    wxTextCtrl *txtFldDeparture;
    wxTextCtrl *txtFldDate;
    wxTextCtrl *txtFldRoom;
    wxTextCtrl *txtFldCard;
    wxStaticText *sTxtEmpty;
    wxButton *btnAdd;
    wxButton *btnCancel;
    wxBoxSizer *hSzrFldArrival;
    wxBoxSizer *hSzrFldDeparture;
    wxBoxSizer *hSzrFldDate;
    wxBoxSizer *hSzrFldRoom;
    wxBoxSizer *hSzrFldCard;
    wxBoxSizer *hSzrBtns;
    wxGridSizer *gSzrMain;

    void OnAdd(wxCommandEvent &event);
};

class DialogEditBook : public wxDialog
{
public:
    DialogEditBook(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxTextCtrl *txtFldBookID;
    wxTextCtrl *txtFldRoomID;
    wxStaticText *sTxtEmpty;
    wxButton *btnApply;
    wxButton *btnCancel;
    wxBoxSizer *hSzrFldBookID;
    wxBoxSizer *hSzrFldRoomID;
    wxBoxSizer *hSzrBtns;
    wxGridSizer *gSzrMain;

    void OnApply(wxCommandEvent &event);
};

class DialogViewBook : public wxDialog
{
public:
    DialogViewBook(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxRichTextCtrl *bookLst;
    wxStaticText *sTxtEmpty;
    wxButton *btnPrintAll;
    wxButton *btnClose;

    wxBoxSizer *hSzrBtm;
    wxBoxSizer *vSzrMain;

    void OnPrintAll(wxCommandEvent &event);
    void OnClose(wxCommandEvent &event);
};

class DialogDeleteBook : public wxDialog
{
public:
    DialogDeleteBook(wxWindow *parent, std::string dbName);

private:
    std::string dbName;
    int radio;

    wxRadioButton *rBtnID;
    wxRadioButton *rBtnDelAll;
    wxTextCtrl *txtFldID;
    wxStaticText *sTxtEmpty;
    wxButton *btnDel;
    wxButton *btnCancel;

    wxBoxSizer *hSzrTxtFldID;
    wxBoxSizer *hSzrBtns;
    wxGridSizer *gSzrID;
    wxGridSizer *gSzrBtm;
    wxBoxSizer *vSzrMain;

    void OnRadioID(wxCommandEvent &event);
    void OnRadioDelAll(wxCommandEvent &event);
    void OnDelete(wxCommandEvent &event);
};

class DialogAddGuest : public wxDialog
{
public:
    DialogAddGuest(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxStaticText *staticTextFirstName;
    wxStaticText *staticTextLastName;
    wxStaticText *staticTextPatronymic;
    wxStaticText *staticTextPassportSeries;
    wxStaticText *staticTextPassportNumber;
    wxStaticText *staticTextPhone;
    
    wxTextCtrl *textFieldFirstName;
    wxTextCtrl *textFieldLastName;
    wxTextCtrl *textFieldPatronymic;
    wxTextCtrl *textFieldPassportSeries;
    wxTextCtrl *textFieldPassportNumber;
    wxTextCtrl *textFieldPhone;
    
    wxButton *buttonAdd;
    wxButton *buttonCancel;

    wxBoxSizer *hSizerRowFstLeft;
    wxBoxSizer *hSizerRowFstRight;
    wxBoxSizer *hSizerRowSndLeft;
    wxBoxSizer *hSizerRowSndRight;
    wxBoxSizer *hSizerRowTrdLeft;
    wxBoxSizer *hSizerRowTrdRight;
    wxBoxSizer *hSizerRowFthLeft;
    wxBoxSizer *hSizerRowFthRight;
    wxBoxSizer *hSizerRowFfhLeft;
    wxBoxSizer *hSizerRowFfhRight;
    wxBoxSizer *hSizerRowSxthLeft;
    wxBoxSizer *hSizerRowSxthRight;
    wxBoxSizer *hSizerRowSvthLeft;
    wxBoxSizer *hSizerRowSvthRight;
    wxGridSizer *gSizerMain;

    void OnAdd(wxCommandEvent &event);
};

class DialogViewGuest : public wxDialog
{
public:
    DialogViewGuest(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxRichTextCtrl *guestLst;
    wxTextCtrl *txtFldLstName;
    wxTextCtrl *txtFldFstName;
    wxButton *btnFind;
    wxButton *btnPrintAll;
    wxButton *btnClose;

    wxBoxSizer *hSzrBtm;
    wxBoxSizer *vSzrMain;

    void OnFind(wxCommandEvent &event);
    void OnPrintAll(wxCommandEvent &event);
    void OnClose(wxCommandEvent &event);
};

class DialogDeleteGuest : public wxDialog
{
public:
    DialogDeleteGuest(wxWindow *parent, std::string dbName);

private:
    std::string dbName;
    int radio;

    wxRadioButton *rBtnID;
    wxRadioButton *rBtnPassport;
    wxRadioButton *rBtnName;
    wxRadioButton *rBtnDelAll;
    wxTextCtrl *txtFldID;
    wxTextCtrl *txtFldPassportSer;
    wxTextCtrl *txtFldPassportNum;
    wxTextCtrl *txtFldFstName;
    wxTextCtrl *txtFldLstName;
    wxStaticText *sTxtEmpty;
    wxButton *btnDel;
    wxButton *btnCancel;

    wxBoxSizer *hSzrTxtFldID;
    wxBoxSizer *hSzrTxtFldPassportNum;
    wxBoxSizer *hSzrTxtFldPassportSer;
    wxBoxSizer *hSzrTxtFldLstName;
    wxBoxSizer *hSzrTxtFldFstName;
    wxBoxSizer *hSzrBtns;
    wxGridSizer *gSzrID;
    wxGridSizer *gSzrPassport;
    wxGridSizer *gSzrName;
    wxGridSizer *gSzrBtm;
    wxBoxSizer *vSzrMain;

    void OnRadioID(wxCommandEvent &event);
    void OnRadioPassport(wxCommandEvent &event);
    void OnRadioName(wxCommandEvent &event);
    void OnRadioDelAll(wxCommandEvent &event);
    void OnDelete(wxCommandEvent &event);
};

class DialogAddLink : public wxDialog
{
public:
    DialogAddLink(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxTextCtrl *txtFldBookID;
    wxTextCtrl *txtFldGuestID;
    wxStaticText *sTxtEmpty;
    wxButton *btnAdd;
    wxButton *btnCancel;
    wxBoxSizer *hSzrFldBookID;
    wxBoxSizer *hSzrFldGuestID;
    wxBoxSizer *hSzrBtns;
    wxGridSizer *gSzrMain;

    void OnAdd(wxCommandEvent &event);
};

class DialogViewLink : public wxDialog
{
public:
    DialogViewLink(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxRichTextCtrl *linkLst;
    wxStaticText *sTxtEmpty;
    wxButton *btnPrintAll;
    wxButton *btnClose;
    wxBoxSizer *hSzrBtm;
    wxBoxSizer *vSzrMain;

    void OnPrintAll(wxCommandEvent &event);
    void OnClose(wxCommandEvent &event);
};

class DialogDelLink : public wxDialog
{
public:
    DialogDelLink(wxWindow *parent, std::string dbName);

private:
    std::string dbName;
    int radio;
    
    wxRadioButton *rBtnID;
    wxRadioButton *rBtnDelAll;
    wxStaticText *sTxtEmpty;
    wxTextCtrl *txtFldBookingID;
    wxTextCtrl *txtFldGuestID;
    wxButton *btnDel;
    wxButton *btnCancel;

    wxBoxSizer *hSzrTxtFldID;
    wxBoxSizer *hSzrBtns;
    wxGridSizer *gSzrID;
    wxGridSizer *gSzrBtm;
    wxBoxSizer *vSzrMain;

    void OnRadioID(wxCommandEvent &event);
    void OnRadioDelAll(wxCommandEvent &event);
    void OnDelete(wxCommandEvent &event);
};

class DialogAddRoom : public wxDialog
{
public:
    DialogAddRoom(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxTextCtrl *textFieldRoomId;
    wxTextCtrl *textFieldPrice;
    wxTextCtrl *textFieldNumberOfRooms;
    wxTextCtrl *textFieldArea;
    wxTextCtrl *textFieldServiceClass;
    wxTextCtrl *textFieldKitchen;
    wxStaticText *sTxtEmpty;
    wxButton *buttonAdd;
    wxButton *buttonCancel;

    wxBoxSizer *hSizerRowFstLeft;
    wxBoxSizer *hSizerRowFstRight;
    wxBoxSizer *hSizerRowSndLeft;
    wxBoxSizer *hSizerRowSndRight;
    wxBoxSizer *hSizerRowTrdLeft;
    wxBoxSizer *hSizerRowTrdRight;
    wxBoxSizer *hSizerRowFthLeft;
    wxBoxSizer *hSizerRowFthRight;
    wxGridSizer *gSizerMain;

    void OnAdd(wxCommandEvent &event);
};

class DialogViewRoom : public wxDialog
{
public:
    DialogViewRoom(wxWindow *parent, std::string dbName);

private:
    std::string dbName;
    
    wxTextCtrl *txtFldArrival;
    wxTextCtrl *txtFldDeparture;
    wxRichTextCtrl *roomLst;
    wxButton *btnFind;
    wxButton *btnPrintAll;
    wxButton *btnCancel;
    wxPanel *panel;
    wxBoxSizer *hSzrBtm;
    wxBoxSizer *vSzrMain;
    
    void OnFind(wxCommandEvent &event);
    void OnPrintAll(wxCommandEvent &event);
    void OnClose(wxCommandEvent &event);
};

class DialogDeleteRoom : public wxDialog
{
public:
    DialogDeleteRoom(wxWindow *parent, std::string dbName);

private:
    std::string dbName;
    int radio;
    
    wxRadioButton *rBtnID;
    wxRadioButton *rBtnDelAll;
    wxStaticText *sTxtEmpty;
    wxTextCtrl *txtFldID;
    wxButton *btnDel;
    wxButton *btnCancel;

    wxBoxSizer *hSzrTxtFldID;
    wxBoxSizer *hSzrBtns;
    wxGridSizer *gSzrID;
    wxGridSizer *gSzrBtm;
    wxBoxSizer *vSzrMain;

    void OnRadioID(wxCommandEvent &event);
    void OnRadioDelAll(wxCommandEvent &event);
    void OnDelete(wxCommandEvent &event);

};

class FrameMenu : public wxFrame
{
public:
    FrameMenu();

private:
    bool modeTest;

    wxPanel *panelTopLeft;
    wxPanel *panelTopRight;
    wxPanel *panelBottomLeft;
    wxPanel *panelBottomRight;

    wxTextCtrl *textFieldDBName;
    wxButton *buttonCreateDB;
    wxButton *buttonDropDB;
    wxButton *buttonCheckDB;
    wxButton *btnViewOverall;
    wxButton *buttonModeTest;
    wxButton *btnAddBook;
    wxButton *btnEditBook;
    wxButton *btnViewBook;
    wxButton *btnDelBook;
    wxButton *buttonAddGuest;
    wxButton *btnViewGuest;
    wxButton *buttonDeleteGuest;
    wxButton *btnAddLink;
    wxButton *btnViewLink;
    wxButton *btnDelLink;
    wxButton *btnAddRoom;
    wxButton *btnViewRoom;
    wxButton *btnDelRoom;
    wxButton *buttonAbout;
    wxButton *buttonExit;

    wxStaticBoxSizer *vSizerControlDB;
    wxStaticBoxSizer *vSzrControlBook;
    wxStaticBoxSizer *vSizerControlGuest;
    wxStaticBoxSizer *vSzrControlLink;
    wxStaticBoxSizer *vSizerControlRoom;
    wxBoxSizer *vSizerTopLeft;
    wxGridSizer *gSizerTopRight;
    wxBoxSizer *hSizerTop;
    wxBoxSizer *vSizerBottomLeft;
    wxBoxSizer *vSizerBottomRight;
    wxBoxSizer *hSizerBottom;
    wxBoxSizer *vSizerMain;

    void AssumeDBCreated();
    void AssumeDBDropped();
    void AssumeDBError();

    void OnCreateDB(wxCommandEvent &event);
    void OnDropDB(wxCommandEvent &event);
    void OnCheckDB(wxCommandEvent &event);
    void OnViewOverall(wxCommandEvent &event);
    void OnModeTest(wxCommandEvent &event);
    void OnAddBook(wxCommandEvent &event);
    void OnEditBook(wxCommandEvent &event);
    void OnViewBook(wxCommandEvent &event);
    void OnDeleteBook(wxCommandEvent &event);
    void OnAddGuest(wxCommandEvent &event);
    void OnViewGuest(wxCommandEvent &event);
    void OnDeleteGuest(wxCommandEvent &event);
    void OnAddLink(wxCommandEvent &event);
    void OnViewLink(wxCommandEvent &event);
    void OnDelLink(wxCommandEvent &event);
    void OnAddRoom(wxCommandEvent &event);
    void OnViewRoom(wxCommandEvent &event);
    void OnDeleteRoom(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
};

class AppClient : public wxApp
{
public:
    virtual bool OnInit();
};

#endif//GUI_HPP
