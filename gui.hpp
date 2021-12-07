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

enum
{
    ID_CHECK_DB = 101,
    ID_CREATE_DB = 102,
    ID_DROP_DB = 103,
    ID_MODE_TEST = 104,
    ID_ADD_GUEST = 105,
    ID_ADD_GUEST_ADD = 106,
    ID_ADD_GUEST_CANCEL = 107,
    ID_VIEW_GUESTS = 108,
    ID_VIEW_GUESTS_FIND = 109,
    ID_VIEW_GUESTS_PRINT_ALL = 110,
    ID_VIEW_GUESTS_CLOSE = 111,
    ID_DELETE_GUEST = 112,
    ID_DELETE_GUEST_RADIO_ID = 113,
    ID_DELETE_GUEST_RADIO_NAME = 114,
    ID_DELETE_GUEST_DELETE = 115,
    ID_DELETE_GUEST_CANCEL = 116
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
    void OnCancel(wxCommandEvent &event);
};

class DialogViewGuests : public wxDialog
{
public:
    DialogViewGuests(wxWindow *parent, std::string dbName);

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
    void OnCancel(wxCommandEvent &event);
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
    void OnCancel(wxCommandEvent &event);
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
    wxButton *buttonAddGuest;
    wxButton *btnViewGuest;
    wxButton *buttonDeleteGuest;
    wxButton *btnAddRoom;
    wxButton *btnViewRoom;
    wxButton *btnDelRoom;
    wxButton *buttonAbout;
    wxButton *buttonExit;

    wxStaticBoxSizer *vSizerControlDB;
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
    void OnAddGuest(wxCommandEvent &event);
    void OnFindGuests(wxCommandEvent &event);
    void OnViewGuests(wxCommandEvent &event);
    void OnDeleteGuest(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
};

class AppClient : public wxApp
{
public:
    virtual bool OnInit();
};

#endif//GUI_HPP
