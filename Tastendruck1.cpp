#include <windows.h>
#include <iostream>

using namespace std;


void simulateKeyPress(BYTE keyCode) {
    // Struktur für die Eingabe
    INPUT ip;

    // Eingabetyp auf Tastatur setzen
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // Kein Scan-Code
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Taste drücken
    ip.ki.wVk = keyCode; // Virtueller Tastencode
    ip.ki.dwFlags = 0; // 0 für Tastendruck
    SendInput(1, &ip, sizeof(INPUT));

    // Taste loslassen
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen
    SendInput(1, &ip, sizeof(INPUT));

    // Anzeigen, welcher Tastendruck simuliert wurde
    std::cout << "Simulierter Tastendruck: " << keyCode << std::endl;
}

int main() {
    // Beispiel: Simulation des Tastendrucks für die Taste 'A'
   
    char n;

    cin >> n;
    
    simulateKeyPress(n);

    return 0;
}

