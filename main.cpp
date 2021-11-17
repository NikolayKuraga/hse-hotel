#include "gui.hpp"

bool AppClient::OnInit()
{
    FrameMenu *frameMenu = new FrameMenu("HSE Hostel Client", wxDefaultPosition, wxDefaultSize);
    frameMenu->Show(true);

    return true;
}
