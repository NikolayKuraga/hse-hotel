#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "shared.hpp"
#include <wx/wx.h>

#define PATH_ICON "icon.png"

class AppClient : public wxApp {
public:
    virtual bool OnInit();
};

enum {
    ID_CONNECT = 101,
    ID_SEND_SIGNAL = 102
};

class FrameWelcome : public wxFrame {
public:
    FrameWelcome(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
    wxButton *buttonConnect;
    wxButton *buttonSendSignal;

    int fdSockServer;

    void OnConnect(wxCommandEvent &event);
    void OnSendSignal(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
};

#endif//CLIENT_HPP
