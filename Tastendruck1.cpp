#include <windows.h>
#include <iostream>

int main() {
    // Warte 5 Sekunden, damit du Zeit hast, das Fenster zu wechseln
    std::cout << "Warte 5 Sekunden..." << std::endl;
    Sleep(5000);

    // Simuliere einen Tastendruck (z.B. die 'a'-Taste) 
    INPUT ip;           

    // Drücke die 'a'-Taste
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0;
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    ip.ki.wVk = 0x41; // Virtual-Key-Code für 'a'
    ip.ki.dwFlags = 0; // 0 für Tastendruck
    SendInput(1, &ip, sizeof(INPUT));

    // Lasse die 'a'-Taste los
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen
    SendInput(1, &ip, sizeof(INPUT));

    return 0;
}
