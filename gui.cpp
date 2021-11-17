#include "gui.hpp"

FrameMenu::FrameMenu(const wxString &title, const wxPoint &pos, const wxSize &size) : wxFrame(nullptr, wxID_ANY, title, pos, size)
{
    SetIcon(wxIcon(PATH_ICON));
    // panels
    wxPanel *panelTop = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panelBottomLeft = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panelBottomRight = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    // buttons
    wxButton *buttonQuery = new wxButton(panelTop, ID_QUERY, "Query about things", wxDefaultPosition, wxDefaultSize);
    wxButton *buttonAbout = new wxButton(panelBottomLeft, wxID_ABOUT, "About", wxDefaultPosition, wxDefaultSize);
    wxButton *buttonExit = new wxButton(panelBottomRight, wxID_EXIT, "Exit", wxDefaultPosition, wxDefaultSize);
    Connect(ID_QUERY, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnQuery));
    Connect(wxID_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnAbout));
    Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameMenu::OnExit));
    // sizers
    wxBoxSizer *vSizerTop = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vSizerBottomLeft = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *vSizerBottomRight = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *hSizerBottom = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *vSizerMain = new wxBoxSizer(wxVERTICAL);
    vSizerTop->Add(buttonQuery, 0, wxALIGN_CENTER | wxTOP, 10);
    vSizerBottomLeft->Add(buttonAbout, 0, wxALIGN_LEFT | wxALL, 10);
    vSizerBottomRight->Add(buttonExit, 0, wxALIGN_RIGHT | wxALL, 10);
    hSizerBottom->Add(panelBottomLeft, 1, wxEXPAND, 0);
    hSizerBottom->Add(panelBottomRight, 1, wxEXPAND, 0);
    vSizerMain->Add(panelTop, 1, wxEXPAND, 0);
    vSizerMain->Add(hSizerBottom, 0, wxEXPAND, 0);
    panelBottomRight->SetSizer(vSizerBottomRight);
    panelBottomLeft->SetSizer(vSizerBottomLeft);
    panelTop->SetSizer(vSizerTop);
    SetSizer(vSizerMain);
    // final touches
    SetMinSize(wxSize(220, 160));
    buttonQuery->SetFocus();
    Centre();
};

void FrameMenu::OnQuery(wxCommandEvent &event)
{
    try {
        pqxx::result r = query(CONNECTION_STRING);
        for(pqxx::result::const_iterator i = r.begin(); i != r.end(); ++i) {
            std::cout << i[0].as<int>() << ") "
                      << i[1].as<std::string>() << " -- "
                      << i[2].as<std::string>() << std::endl;
        }
        std::cout << std::endl;
    }
    catch(const std::exception &e) {
        wxMessageBox((std::string) "Connection error:\n" + e.what(), "Error", wxOK | wxCENTRE | wxICON_ERROR);
    }
}

void FrameMenu::OnAbout(wxCommandEvent &event)
{
    wxMessageBox((std::string) "HSE Hostel Client, ver." + VERSION + "\n" + GITHUB, "About HSE Hostel Client", wxOK | wxICON_INFORMATION);
}

void FrameMenu::OnExit(wxCommandEvent &event)
{
    Close(true);
}

wxIMPLEMENT_APP(AppClient);
