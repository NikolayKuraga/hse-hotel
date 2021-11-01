#include "shared.hpp"
#include <wx/wx.h>

#define VERSION   "2021.11.02"
#define GITHUB    "https://github.com/NikolayKuraga/hse-hotel"
#define PATH_ICON "icon.png"

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

class AppClient : public wxApp {
public:
    virtual bool OnInit();
};

enum {
    ID_CALLSAUL = 101
};

class FrameWelcome : public wxFrame {
public:
    FrameWelcome(const wxString &title, const wxPoint &pos, const wxSize &size);
private:
    wxButton *buttonCallSaul;
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnCallSaul(wxCommandEvent &event);
};
