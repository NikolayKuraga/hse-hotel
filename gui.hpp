#ifndef GUI_HPP
#define GUI_HPP

#include <iostream>
#include <wx/wx.h>
#include "dbi.hpp"

#define VERSION   "2021.11.17"
#define GITHUB    "https://github.com/NikolayKuraga/hse-hotel"
#define PATH_ICON "icon.png"

class AppClient : public wxApp
{
public:
    virtual bool OnInit();
};

enum
{
    ID_QUERY = 101
};

class FrameMenu : public wxFrame
{
public:
    FrameMenu(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnQuery(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
};

#endif//GUI_HPP
