#ifndef GUI_HPP
#define GUI_HPP

#include <iostream>
#include <vector>
#include <wx/wx.h>
#include "dbi.hpp"

#define VERSION   "2021.11.28"
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
    ID_ADD_GUEST_CANCEL = 107
};

class DialogAddGuest : public wxDialog
{
public:
    DialogAddGuest(wxWindow *parent);

private:
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
    wxButton *buttonCreateDB;
    wxButton *buttonDropDB;
    wxButton *buttonCheckDB;
    wxButton *buttonModeTest;
    wxButton *buttonAddGuest;
    wxButton *buttonAbout;
    wxButton *buttonExit;
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
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
};

class AppClient : public wxApp
{
public:
    virtual bool OnInit();
};

#endif//GUI_HPP
