#include "client.hpp"

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
    buttonConnect = new wxButton(panelTop, ID_CONNECT, wxT("Connect to the server"), wxDefaultPosition, wxDefaultSize);
    buttonSendSignal = new wxButton(panelTop, ID_SEND_SIGNAL, wxT("Send a signal to the server"), wxDefaultPosition, wxDefaultSize);
    wxButton *buttonAbout = new wxButton(panelBottomLeft, wxID_ABOUT, wxT("About"), wxDefaultPosition, wxDefaultSize);
    wxButton *buttonExit = new wxButton(panelBottomRight, wxID_EXIT, wxT("Exit"), wxDefaultPosition, wxDefaultSize);
    Connect(ID_CONNECT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameWelcome::OnConnect));
    Connect(ID_SEND_SIGNAL, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameWelcome::OnSendSignal));
    Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameWelcome::OnAbout));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameWelcome::OnExit));
    buttonSendSignal -> Enable(false);
    // sizers
    wxBoxSizer *vSizerTop = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vSizerBottomLeft = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vSizerBottomRight = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hSizerBottom = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vSizerMain = new wxBoxSizer(wxVERTICAL);
    vSizerTop -> Add(buttonConnect, 0, wxALIGN_CENTER | wxTOP, 10);
    vSizerTop -> Add(buttonSendSignal, 0, wxALIGN_CENTER | wxTOP, 10);
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
    // final touches
    buttonConnect -> SetFocus();
    SetMinSize(wxSize(220, 160));
    Centre();
};

void FrameWelcome::OnConnect(wxCommandEvent &event) {
    fdSockServer = socket(AF_INET, SOCK_STREAM, 0);
    if (fdSockServer == -1) {
        wxMessageBox("The connection has not been established:\nsocket() failed", "Error", wxOK | wxICON_ERROR);
        return;
    }
    struct sockaddr_in addrServer = { 0 };

    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(PORT);
    addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

    int check = connect(fdSockServer, (struct sockaddr *) &addrServer, sizeof(addrServer));
    if (check == -1) {
        wxMessageBox("The connection has not been established:\nconnect() failed", "Error", wxOK | wxICON_ERROR);
        return;
    }        
    wxMessageBox("The connection has been established", "Success", wxOK | wxICON_INFORMATION);

    buttonConnect -> Enable(false);
    buttonSendSignal -> Enable(true);
//    wxMessageBox("The connection was broken", "Warning", wxOK | wxICON_EXCLAMATION);
}

void FrameWelcome::OnSendSignal(wxCommandEvent &event) {
    std::string msg = "Hello, Server!";
    cstm::sendStr(fdSockServer, &msg);
    cstm::recvStr(fdSockServer, &msg);
    wxMessageBox(msg, "Message from the server", wxOK | wxICON_INFORMATION);
}

void FrameWelcome::OnAbout(wxCommandEvent &event) {
    wxMessageBox((std::string) "HSE Hostel Client, ver." + VERSION + "\n" + GITHUB, "About HSE Hostel Client", wxOK | wxICON_INFORMATION);
}

void FrameWelcome::OnExit(wxCommandEvent &event) {
    close(fdSockServer);
    Close(true);
}

wxIMPLEMENT_APP(AppClient);

bool AppClient::OnInit() {
    FrameWelcome *frameWelcome = new FrameWelcome("HSE Hostel Client", wxDefaultPosition, wxDefaultSize);
    frameWelcome -> Show(true);
    return true;
}
