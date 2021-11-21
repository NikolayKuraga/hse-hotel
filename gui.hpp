#ifndef GUI_HPP
#define GUI_HPP

#include <iostream>
#include <wx/wx.h>
#include "dbi.hpp"

#define VERSION   "2021.11.22"
#define GITHUB    "https://github.com/NikolayKuraga/hse-hotel"
#define PATH_ICON "icon.png"

class AppClient : public wxApp
{
public:
    virtual bool OnInit();
};

enum
{
    ID_CHECK_DB = 101,
    ID_CREATE_DB = 102,
    ID_DROP_DB = 103
};

class FrameMenu : public wxFrame
{
public:
    FrameMenu(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    wxPanel *panelTop;
    wxPanel *panelBottomLeft;
    wxPanel *panelBottomRight;
    wxButton *buttonCheckDB;
    wxButton *buttonCreateDB;
    wxButton *buttonDropDB;
    wxButton *buttonAbout;
    wxButton *buttonExit;
    wxBoxSizer *vSizerTop;
    wxBoxSizer *vSizerBottomLeft;
    wxBoxSizer *vSizerBottomRight;
    wxBoxSizer *hSizerBottom;
    wxBoxSizer *vSizerMain;

    void OnCheckDB(wxCommandEvent &event);
    void OnCreateDB(wxCommandEvent &event);
    void OnDropDB(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
};

#endif//GUI_HPP
