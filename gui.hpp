#ifndef GUI_HPP
#define GUI_HPP

#include <iostream>
#include <vector>
#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include "dbi.hpp"

#define VERSION   "2021.12.02"
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
    ID_PRINT_GUESTS = 108,
    ID_PRINT_GUESTS_OK = 109,
    ID_DELETE_GUEST = 110,
    ID_DELETE_GUEST_DELETE = 111,
    ID_DELETE_GUEST_CANCEL = 112
};

class DialogPrintGuests : public wxDialog
{
public:
    DialogPrintGuests(wxWindow *parent, std::string dbName);

private:
    wxPanel *panelBottom;
    wxRichTextCtrl *guestList;
    wxButton *buttonOK;

    wxBoxSizer *vSizerBottom;
    wxBoxSizer *vSizerMain;
    void OnOK(wxCommandEvent &event);
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

class DialogDeleteGuest : public wxDialog
{
public:
    DialogDeleteGuest(wxWindow *parent, std::string dbName);

private:
    std::string dbName;

    wxTextCtrl *textFieldFirstName;
    wxTextCtrl *textFieldLastName;
    wxStaticText *staticTextRowSndLeft;
    wxButton *buttonDelete;
    wxButton *buttonCancel;

    wxBoxSizer *hSizerRowFstLeft;
    wxBoxSizer *hSizerRowFstRight;
    wxBoxSizer *hSizerRowSndRight;
    wxGridSizer *gSizerMain;

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
    wxButton *buttonPrintGuests;
    wxButton *buttonDeleteGuest;
    wxButton *buttonAbout;
    wxButton *buttonExit;

    wxStaticBoxSizer *vSizerControlDB;
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
    void OnPrintGuests(wxCommandEvent &event);
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
