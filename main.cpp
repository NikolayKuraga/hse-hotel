#include "gui.hpp"

bool AppClient::OnInit()
{
    FrameMenu *frameMenu = new FrameMenu();
    frameMenu->Show(true);

    return true;
}

wxIMPLEMENT_APP(AppClient);
