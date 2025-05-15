//Tastendruck großbuchstaben


#include <windows.h>
#include <iostream>
#include <cctype>
using namespace std;





void simulateKeyPress(BYTE keyCodeByte, char keyCodeChar) {
    // Struktur für die Eingabe in ip werden die Variablen von unten eingesetzt
    INPUT ip[2] = { 0 };

    // Allg. für eingabe sagt soviel wie: Eingabe ist Tastendruck 
    ip[0].type = INPUT_KEYBOARD;
    ip[0].ki.wVk = VK_SHIFT; // Virtueller Tastencode !Byte wird als wert erwartet
    ip[0].ki.dwFlags = 0; // 0 für Tastendruck


        // Allg. für eingabe sagt soviel wie: Eingabe ist Tastendruck 
    ip[1].type = INPUT_KEYBOARD;
    ip[1].ki.wVk = keyCodeByte; // Virtueller Tastencode !Byte wird als wert erwartet
    ip[1].ki.dwFlags = 0; // 0 für Tastendruck
    
    
    SendInput(2, ip, sizeof(INPUT)); //Tastendruck wird gesendet


    // Taste loslassen
    ip[0].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen
    ip[1].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen
    SendInput(2, ip, sizeof(INPUT));
    

    // Anzeigen, welcher Tastendruck simuliert wurde

    BYTE scanCode = MapVirtualKey(keyCodeChar, MAPVK_VK_TO_VSC);
    std::cout << "Simulierter Tastendruck: " << char(toupper(keyCodeChar)) << std::endl;

}

int main() {



    // EingabeVariable definieren

    char n;



    cin >> n;
    Sleep(2000);


    //n wird in zwei unterschiedliche datentypen/ variablen gespeichert und an Simulatekeypress übergeben. 

    BYTE keyCodeByte = toupper(n);


    char keyCodeChar = toupper(n);







    // Überprüfen des virtuellen Tastencodes
    
    


    simulateKeyPress(keyCodeByte, keyCodeChar);

    return 0;
}


