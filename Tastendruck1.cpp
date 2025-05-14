#include <windows.h>
#include <iostream>
#include <cctype>
using namespace std;


void simulateKeyPress(BYTE keyCodeByte, char keyCodeChar) {
    // Struktur für die Eingabe
    INPUT ip;

    // Eingabetyp auf Tastatur setzen
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // Kein Scan-Code
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    // Taste drücken
    ip.ki.wVk = keyCodeByte; // Virtueller Tastencode
    ip.ki.dwFlags = 0; // 0 für Tastendruck
    SendInput(1, &ip, sizeof(INPUT));

    // Taste loslassen
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen
    SendInput(1, &ip, sizeof(INPUT));

    // Anzeigen, welcher Tastendruck simuliert wurde
    std::cout << "Simulierter Tastendruck: " << char(tolower(keyCodeChar)) << std::endl;

}

int main() {
    
    char n;
    
    

    cin >> n;
    Sleep(2000);

   

    
        BYTE keyCodeByte = toupper(n); // Wandelt den Buchstaben in Großbuchstaben um


        char keyCodeChar = toupper(n);

    
 
   
   


    // Überprüfen des virtuellen Tastencodes
    UINT scanCode = MapVirtualKey(keyCodeByte, MAPVK_VK_TO_VSC);
    std::cout << "Virtueller Tastencode: " << (int)keyCodeByte << ", Scan-Code: " << scanCode << std::endl;
    

    simulateKeyPress(keyCodeByte, keyCodeChar);

    return 0;
}

