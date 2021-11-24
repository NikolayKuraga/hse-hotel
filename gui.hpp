#ifndef GUI_HPP
#define GUI_HPP

#include <iostream>
#include <wx/wx.h>
#include "dbi.hpp"

#define VERSION   "2021.11.25"
#define GITHUB    "https://github.com/NikolayKuraga/hse-hotel"
#define PATH_ICON "icon.png"

enum
{
    ID_CHECK_DB = 101,
    ID_CREATE_DB = 102,
    ID_DROP_DB = 103,
    ID_ADD_GUEST = 104
};

class DialogAddGuest : public wxDialog
{
public:
    DialogAddGuest(wxWindow *parent);

private:/*
    wxTextCtrl *topLeft;
    wxTextCtrl *topRight;
    wxTextCtrl *bottomLeft;
    wxTextCtrl *bottomRight;
    wxGridSizer *vGridSizerMain;*/
//    wxPanel *panelMain;
//    wxSizer *sizerMain;
};

class FrameMenu : public wxFrame
{
public:
    FrameMenu();

private:
    wxPanel *panelTopLeft;
    wxPanel *panelTopRight;
    wxPanel *panelBottomLeft;
    wxPanel *panelBottomRight;
    wxButton *buttonCheckDB;
    wxButton *buttonCreateDB;
    wxButton *buttonDropDB;
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

    void OnCheckDB(wxCommandEvent &event);
    void OnCreateDB(wxCommandEvent &event);
    void OnDropDB(wxCommandEvent &event);
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
