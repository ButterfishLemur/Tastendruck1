//Tastendruck kleinbuchstaben und zahlen 0 bis 9

#include <windows.h>
#include <iostream>
#include <cctype>
#include <string>
#include <map>



using namespace std;





void simulateKeyPress(BYTE keyCodeByte, char keyCodeChar) {
    // Struktur für die Eingabe in ip werden die Variablen von unten eingesetzt
    INPUT ip = { 0 };


    // Allg. für eingabe sagt soviel wie: Eingabe ist Tastendruck 
    ip.type = INPUT_KEYBOARD;
    ip.ki.wVk = keyCodeByte;
    



    // Taste drücken / daten zu Tastendruck
     // Virtueller Tastencode !Byte wird als wert erwartet
    ip.ki.dwFlags = 0; // 0 für Tastendruck
    
    
    
    SendInput(2, &ip, sizeof(INPUT)); //Tastendruck wird gesendet


    // Taste loslassen
    ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen
    char(SendInput(2, &ip, sizeof(INPUT)));
    

    // Anzeigen, welcher Tastendruck simuliert wurde

    
    std::cout << "Simulierter Tastendruck: " << char(tolower(keyCodeChar)) << "ptr" << &ip << std::endl;

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


