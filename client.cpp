#include "client.hpp"

FrameWelcome::FrameWelcome(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    SetIcon(wxIcon(wxT(PATH_ICON)));
    
    wxPanel *panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel1 -> SetBackgroundColour(wxColor(200, 200, 50));

    wxPanel *panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel2 -> SetBackgroundColour(wxColor(50, 50, 50));

    wxButton *buttonCall = new wxButton(this, wxID_ANY, wxT("Better call Saul!"), wxDefaultPosition, wxDefaultSize);

    wxButton *buttonExit = new wxButton(this, wxID_EXIT, wxT("Exit"), wxDefaultPosition, wxDefaultSize);
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameWelcome::OnExit));
    
    wxButton *buttonAbout = new wxButton(this, wxID_ABOUT, wxT("About"), wxDefaultPosition, wxDefaultSize);
    Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameWelcome::OnAbout));

    wxBoxSizer *vSizer = new wxBoxSizer(wxHORIZONTAL);
    vSizer -> Add(buttonAbout, 0, wxEXPAND, 0);
    vSizer -> Add(panel2, 1, wxEXPAND, 0);
    vSizer -> Add(buttonExit, 0, wxEXPAND, 0);

    wxBoxSizer *hSizer = new wxBoxSizer(wxVERTICAL);
    hSizer -> Add(buttonCall, 0, wxALIGN_CENTER | wxTOP, 10);
    hSizer -> Add(panel1, 1, wxEXPAND, 0);
    hSizer -> Add(vSizer, 0, wxEXPAND, 0);

    buttonAbout -> SetFocus();
    this -> SetSizer(hSizer);

    Centre();
};

void FrameWelcome::OnExit(wxCommandEvent &event) {
    Close(true);
}

void FrameWelcome::OnAbout(wxCommandEvent &event) {
    wxMessageBox("Hse Hostel Client, build 2021.10.31.", "About HSE Hostel Client", wxOK | wxICON_INFORMATION);
}

wxIMPLEMENT_APP(ClientApp);

bool ClientApp::OnInit() {
    FrameWelcome *welcomeFrame = new FrameWelcome("HSE Hostel Client", wxDefaultPosition, wxDefaultSize);
    welcomeFrame -> Show(true);
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
