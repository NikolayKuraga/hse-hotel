#include "client.hpp"

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int info = connect(sockfd, addr, addrlen);
    if (info == -1) {
        perror("connect() failed");
        exit(EXIT_FAILURE);
    }
    return info;
}

FrameWelcome::FrameWelcome(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    SetIcon(wxIcon(wxT(PATH_ICON)));
    // panels
    wxPanel *panelTop = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panelBottomLeft = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panelBottomRight = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panelTop -> SetBackgroundColour(wxColor(50, 150, 0));
    panelBottomLeft -> SetBackgroundColour(wxColor(130, 40, 200));
    panelBottomRight -> SetBackgroundColour(wxColor(40, 20, 140));
    // buttons
    buttonCallSaul = new wxButton(panelTop, ID_CALLSAUL, wxT("Better call Saul!"), wxDefaultPosition, wxDefaultSize);
    wxButton *buttonAbout = new wxButton(panelBottomLeft, wxID_ABOUT, wxT("About"), wxDefaultPosition, wxDefaultSize);
    wxButton *buttonExit = new wxButton(panelBottomRight, wxID_EXIT, wxT("Exit"), wxDefaultPosition, wxDefaultSize);
    Connect(ID_CALLSAUL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameWelcome::OnCallSaul));
    Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameWelcome::OnAbout));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameWelcome::OnExit));
    // sizers
    wxBoxSizer *vSizerTop = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vSizerBottomLeft = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vSizerBottomRight = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hSizerBottom = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vSizerMain = new wxBoxSizer(wxVERTICAL);
    vSizerTop -> Add(buttonCallSaul, 0, wxALIGN_CENTER | wxALL, 10);
    vSizerBottomLeft -> Add(buttonAbout, 0, wxALIGN_LEFT | wxALL, 10);
    vSizerBottomRight -> Add(buttonExit, 0, wxALIGN_RIGHT | wxALL, 10);
    hSizerBottom -> Add(panelBottomLeft, 1, wxEXPAND, 0);
    hSizerBottom -> Add(panelBottomRight, 1, wxEXPAND, 0);
    vSizerMain -> Add(panelTop, 1, wxEXPAND, 0);
    vSizerMain -> Add(hSizerBottom, 0, wxEXPAND, 0);
    panelBottomRight -> SetSizer(vSizerBottomRight);
    panelBottomLeft -> SetSizer(vSizerBottomLeft);
    panelTop -> SetSizer(vSizerTop);
    this -> SetSizer(vSizerMain);

    buttonCallSaul -> SetFocus();
    SetMinSize(wxSize(220, 150));
    Centre();
};

void FrameWelcome::OnExit(wxCommandEvent &event) {
    Close(true);
}

void FrameWelcome::OnAbout(wxCommandEvent &event) {
    wxMessageBox((std::string) "HSE Hostel Client, ver." + VERSION + "\n" + GITHUB, "About HSE Hostel Client", wxOK | wxICON_INFORMATION);
}

void FrameWelcome::OnCallSaul(wxCommandEvent &event) {
    buttonCallSaul -> Enable(false);
}

wxIMPLEMENT_APP(AppClient);

bool AppClient::OnInit() {
    FrameWelcome *frameWelcome = new FrameWelcome("HSE Hostel Client", wxDefaultPosition, wxDefaultSize);
    frameWelcome -> Show(true);
    return true;
}

/*
int main(int argc, char ** argv) {
    int sockServer = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addrServer = { 0 };

    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

    Connect(sockServer, (struct sockaddr *) &addrServer, sizeof(addrServer));

    std::cout << "Successfully connected to the server!" << std::endl;

    close(sockServer);
    return 0;
}
*/
