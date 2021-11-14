#include "client.hpp"

bool AppClient::OnInit() {
    FrameWelcome *frameWelcome = new FrameWelcome("HSE Hostel Client", wxDefaultPosition, wxDefaultSize);
    frameWelcome -> Show(true);
    return true;
}
