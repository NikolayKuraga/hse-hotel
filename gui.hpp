#ifndef GUI_HPP
#define GUI_HPP

#include <iostream>
#include <vector>
#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include "dbi.hpp"

#define VERSION   "2021.12.09"
#define GITHUB    "https://github.com/NikolayKuraga/hse-hotel"
#define PATH_ICON "icon.png"

enum {
    ONE_HUNDRED = 100,
    ID_CHECK_DB,
    ID_CREATE_DB,
    ID_DROP_DB,
    ID_MODE_TEST,
    ID_ADD_BOOKING,
    ID_ADD_BOOKING_ADD,
    ID_VIEW_BOOKING,
    ID_DELETE_BOOKING,
    ID_ADD_GUEST,
    ID_ADD_GUEST_ADD,
    ID_VIEW_GUEST,
    ID_VIEW_GUEST_FIND,
    ID_VIEW_GUEST_PRINT_ALL,
    ID_VIEW_GUEST_CLOSE,
    ID_DELETE_GUEST,
    ID_DELETE_GUEST_RADIO_ID,
    ID_DELETE_GUEST_RADIO_NAME,
    ID_DELETE_GUEST_DELETE,
    ID_ADD_ROOM,
    ID_ADD_ROOM_ADD,
    ID_VIEW_ROOM,
    ID_DELETE_ROOM,
    ID_DELETE_ROOM_DELETE,
    ID_DELETE_ROOM_RADIO_ID,
    ID_DELETE_ROOM_RADIO_DELETE_ALL,
    ID_VIEW_ROOM_PRINT_ALL,
    ID_VIEW_ROOM_CLOSE
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
    wxTextCtrl *txtFldTotalCost;
    wxTextCtrl *txtFldBankCard;
    wxStaticText *sTxtEmpty;
    wxButton *btnAdd;
    wxButton *btnCancel;
    wxBoxSizer *hSzrRowFstLeft;
    wxBoxSizer *hSzrRowFstRight;
    wxBoxSizer *hSzrRowSndLeft;
    wxBoxSizer *hSzrRowSndRight;
    wxBoxSizer *hSzrRowTrdLeft;
    wxBoxSizer *hSzrRowTrdRight;
    wxBoxSizer *hSzrRowFthRight;
    wxGridSizer *gSzrMain;

    void OnAdd(wxCommandEvent &event);
};

class DialogAddGuest : public wxDialog
{
public:
    DialogAddGuest(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxTextCtrl *textFieldFirstName;
    wxTextCtrl *textFieldLastName;
    wxStaticText *staticTextRowSndLeft;
    wxTextCtrl *textFieldPatronymic;
    wxTextCtrl *textFieldPassportSeries;
    wxTextCtrl *textFieldPassportNumber;
    wxStaticText *staticTextRowFthLeft;
    wxTextCtrl *textFieldPhone;
    wxStaticText *staticTextRowFfhLeft;
    wxButton *buttonAdd;
    wxButton *buttonCancel;

    wxBoxSizer *hSizerRowFstLeft;
    wxBoxSizer *hSizerRowFstRight;
    wxBoxSizer *hSizerRowSndRight;
    wxBoxSizer *hSizerRowTrdLeft;
    wxBoxSizer *hSizerRowTrdRight;
    wxBoxSizer *hSizerRowFthRight;
    wxBoxSizer *hSizerRowFfhRight;
    wxGridSizer *gSizerMain;

    void OnAdd(wxCommandEvent &event);
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
    wxButton *btnCancel;

    wxBoxSizer *hSzrBtm;
    wxBoxSizer *vSzrMain;

    void OnFind(wxCommandEvent &event);
    void OnPrintAll(wxCommandEvent &event);
    void OnClose(wxCommandEvent &event);
};

class DialogViewRoom : public wxDialog
{
public:
    DialogViewRoom(wxWindow *parent, std::string dbName);

private:
    std::string dbName;
    
    wxRichTextCtrl *roomLst;
    wxButton *btnPrintAll;
    wxButton *btnCancel;
    wxPanel *panel;
    wxBoxSizer *hSzrBtm1;
    wxBoxSizer *hSzrBtm2;
    wxBoxSizer *vSzrMain;

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
    wxRadioButton *rBtnName;
    wxTextCtrl *txtFldID;
    wxTextCtrl *txtFldFstName;
    wxTextCtrl *txtFldLstName;
    wxStaticText *sTxtEmpty;
    wxButton *btnDel;
    wxButton *btnCancel;

    wxBoxSizer *hSzrIDRowFstRight;
    wxBoxSizer *hSzrNameRowFstLeft;
    wxBoxSizer *hSzrNameRowFstRight;
    wxBoxSizer *hSzrNameRowSndRight;
    wxGridSizer *gSzrTop;
    wxGridSizer *gSzrBtm;
    wxBoxSizer *vSzrMain;

    void OnRadioID(wxCommandEvent &event);
    void OnRadioName(wxCommandEvent &event);
    void OnDelete(wxCommandEvent &event);
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
    wxButton *buttonModeTest;
    wxButton *btnAddBook;
    wxButton *btnViewBook;
    wxButton *btnDelBook;
    wxButton *buttonAddGuest;
    wxButton *btnViewGuest;
    wxButton *buttonDeleteGuest;
    wxButton *btnAddRoom;
    wxButton *btnViewRoom;
    wxButton *btnDelRoom;
    wxButton *buttonAbout;
    wxButton *buttonExit;

    wxStaticBoxSizer *vSizerControlDB;
    wxStaticBoxSizer *vSzrControlBook;
    wxStaticBoxSizer *vSizerControlGuest;
    wxStaticBoxSizer *vSizerControlRoom;
    wxBoxSizer *vSizerTopLeft;
    wxBoxSizer *vSizerTopRight;
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
    void OnModeTest(wxCommandEvent &event);
    void OnAddBook(wxCommandEvent &event);
    void OnViewBook(wxCommandEvent &event);
    void OnDeleteBook(wxCommandEvent &event);
    void OnAddGuest(wxCommandEvent &event);
    void OnAddRoom(wxCommandEvent &event);
    void OnViewGuest(wxCommandEvent &event);
    void OnViewRoom(wxCommandEvent &event);
    void OnDeleteGuest(wxCommandEvent &event);
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
