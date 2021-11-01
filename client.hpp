#include "shared.hpp"
#include <wx/wx.h>

#define PATH_ICON "icon.png"

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int info = connect(sockfd, addr, addrlen);
    if (info == -1) {
        perror("connect() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}

class ClientApp : public wxApp {
public:
    virtual bool OnInit();
};

class FrameWelcome : public wxFrame {
public:
    FrameWelcome(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);

    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(FrameWelcome, wxFrame)
EVT_MENU(wxID_EXIT, FrameWelcome::OnExit)
EVT_MENU(wxID_ABOUT, FrameWelcome::OnAbout)
wxEND_EVENT_TABLE()
