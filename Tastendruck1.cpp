#include <iostream>
#include <map>
#include <string>
#include<windows.h>


// Funktion, die eine Tastenkombination simuliert


void simulateShiftPlusOne(char n) {

	// Struktur für die Eingabe in ip werden die Variablen von unten eingesetzt
	INPUT ip[2] = { 0 };

	// Allg. für eingabe sagt soviel wie: Eingabe ist Tastendruck 
	ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.wVk = VK_SHIFT; // Virtueller Tastencode !Byte wird als wert erwartet
	ip[0].ki.dwFlags = 0; // 0 für Tastendruck

	std::cout << n << std::endl;
	// Allg. für eingabe sagt soviel wie: Eingabe ist Tastendruck 
	ip[1].type = INPUT_KEYBOARD;
	ip[1].ki.wVk = VkKeyScan(n); // Virtueller Tastencode !Byte wird als wert erwartet
	ip[1].ki.dwFlags = 0; // 0 für Tastendruck


	SendInput(2, ip, sizeof(INPUT)); //Tastendruck wird gesendet


	// Taste loslassen
	ip[0].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen
	ip[1].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen
	SendInput(2, ip, sizeof(INPUT));


	// Anzeigen, welcher Tastendruck simuliert wurde


	std::cout << "Simulierter Tastendruck: " << ip << std::endl;

}
void simulateALtGr(char n) {

	// Struktur für die Eingabe in ip werden die Variablen von unten eingesetzt
	INPUT ip[3] = { 0 };

	// Allg. für eingabe sagt soviel wie: Eingabe ist Tastendruck 
	ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.wVk = VK_CONTROL; // Virtueller Tastencode !Byte wird als wert erwartet
	ip[0].ki.dwFlags = 0; // 0 für Tastendruck

	std::cout << n << std::endl;
	// Allg. für eingabe sagt soviel wie: Eingabe ist Tastendruck 
	ip[1].type = INPUT_KEYBOARD;
	ip[1].ki.wVk = VK_MENU; // Virtueller Tastencode !Byte wird als wert erwartet
	ip[1].ki.dwFlags = 0; // 0 für Tastendruck

	ip[2].type = INPUT_KEYBOARD;
	ip[2].ki.wVk = VkKeyScan(n); // Virtueller Tastencode !Byte wird als wert erwartet
	ip[2].ki.dwFlags = 0; // 0 für Tastendruck


	SendInput(3, ip, sizeof(INPUT)); //Tastendruck wird gesendet


	// Taste loslassen
	ip[0].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen
	ip[1].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen
	ip[2].ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(3, ip, sizeof(INPUT));


	// Anzeigen, welcher Tastendruck simuliert wurde


	std::cout << "Simulierter Tastendruck: " << ip << std::endl;
}
void simulateST(char n) {
	INPUT ip[1] = { 0 };

	// Allg. für eingabe sagt soviel wie: Eingabe ist Tastendruck 
	ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.wVk = n; // Virtueller Tastencode !Byte wird als wert erwartet
	ip[0].ki.dwFlags = 0; // 0 für Tastendruck

	std::cout << n << std::endl;


	SendInput(1, ip, sizeof(INPUT));

	ip[0].ki.dwFlags = KEYEVENTF_KEYUP;


	SendInput(1, ip, sizeof(INPUT));

	std::cout << "simulierter Tastendruck: " << ip << std::endl;
}

void simulateKeyPressG(BYTE keyCodeByte, char zeichen) {
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

	BYTE scanCode = MapVirtualKey(keyCodeByte, MAPVK_VK_TO_VSC);
	std::cout << "Simulierter Tastendruck: " << char(zeichen) << std::endl;

}
void simulateKeyPressk(BYTE keyCodeByte) {




	// Struktur für die Eingabe in ip werden die Variablen von unten eingesetzt
	INPUT ip[1] = { 0 };


	ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.wVk = keyCodeByte;
	ip[0].ki.dwFlags = 0; // 0 für Tastendruck



	SendInput(1, ip, sizeof(INPUT)); //Tastendruck wird gesendet


	// Taste loslassen
	ip[0].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP für Tastenloslassen

	SendInput(1, ip, sizeof(INPUT));


	// Anzeigen, welcher Tastendruck simuliert wurde


	std::cout << "Simulierter Tastendruck: " << keyCodeByte << std::endl;
}



int main() {
	// Maps mit den Sonderzeichen
	// SHIFT SZ
	std::map<char, char> MapSZ = {

		// Sonderzeichen von Nummern 
		{ '!', '1' },
		{ '"', '2' },
		{ '§', '3' },
		{ '$', '4' },
		{ '%', '5' },
		{ '&', '6' },
		{ '/', '7' },
		{ '(', '8' },
		{ ')', '9' },
		{ '=', '0' },

		//Nicht nummer Sonderzeichen

		{ '`', '´' },
		{ '*', '+' },
		{ ';', ',' },
		{ ':', '.' },
		{ '_', '-' },
		{ '>', '<' },
		{ '°', '^' },

		//Hier EscapeCharacter: \ z.B. verwendung \' 

//funktioniert noch nicht!!!!!!!

		{'\'','#'},
		


	};

	//AltGr SZ
	std::map<char, char> MapAlTGr = {
		
		//AltGr Zahl
		{'²','2'},
		{'³','q'},
		{'{','7'},
		{'[','8'},
		{']','q'},
		{'}','0'},

		//AtGr Nicht Zahl
		{'@','q'},
		{'€','e'},
		{'~','+'},
		{'|','<'}

	};

	//ST
	std::map<std::string, int> MapST = {

		//Systemtasten Block 1
			{"ESC", VK_ESCAPE},
			{"CLEAR", VK_CLEAR},
			{"TAB", VK_TAB},
			{"RETURN", VK_RETURN},
			{"CAPS", VK_CAPITAL},
			{"LSHIFT", VK_LSHIFT},
			{"RSHIFT", VK_RSHIFT},
			{"LCONTROL", VK_LCONTROL},
			{"LWIN",VK_LWIN},
			{"ALT", VK_MENU},
			{"SPACE", VK_SPACE},

			//AltGr, Fn, kpwas das ist Tasten nicht

			{"RCONTROL", VK_RCONTROL},

			//systemtasten Block 2
				{"EINF", VK_INSERT},
				{"POS1", VK_HOME},
				{"BILDUP",VK_PRIOR},
				{"ENTF", VK_DELETE},
				{"ENDE", VK_END},
				{"BILDDOWN",VK_NEXT},

				{"UP", VK_UP},
				{"LEFT", VK_LEFT},
				{"DOWN", VK_DOWN},
				{"RIGHT", VK_RIGHT},

				//systemtasten Ftasten

					{"F1", VK_F1},
					{"F2", VK_F2},
					{"F3", VK_F3},
					{"F4", VK_F4},
					{"F5", VK_F5},
					{"F6", VK_F6},
					{"F7", VK_F7},
					{"F8", VK_F8},
					{"F9", VK_F9},
					{"F10", VK_F10},
					{"F11", VK_F11},
					{"F12", VK_F12},




	};


	// Ein Zeichen eingeben
	std::string str;
	std::cout << "Geben Sie ein Zeichen ein: ";
	std::cin >> str;
	Sleep(2000);

	//0 If unterscheidung Eingabe = 1 oder >1

	// 1.0 Eingabe = 1

	if (str.length() == 1) {
		char zeichen = str[0];

		// 1.1 If Map: Sonderzeichen, die mit Shift gerzeugt werden

		if (MapSZ.find(zeichen) != MapSZ.end()) {
			simulateShiftPlusOne(MapSZ[zeichen]);
			std::cout << "Mapping Zeichen SZ: " << MapSZ[zeichen] << std::endl;
		}
		// 1.2 If Map: Sonderzeichen, die mit AltGr erzeugt werden
		else if (MapAlTGr.find(zeichen) != MapAlTGr.end()) {
			simulateALtGr(MapAlTGr[zeichen]);
			std::cout << "Mappig Zeichen AltGr: " << MapAlTGr[zeichen] << std::endl;


		}
		// 1.3. Rest
		else {
			char keyCodeByte = zeichen;

			//1.3.1 If Uppercase letter?

			if (isupper(keyCodeByte)) {
				simulateKeyPressG(keyCodeByte, zeichen);
			}

			//1.3.2 Rest: Annahme übriger Character muss klein sein


			else if (islower(keyCodeByte)) {

				simulateKeyPressk(toupper(keyCodeByte));

				std::cout << "Dieses Zeichen hat keine spezielle Bedeutung." << std::endl;
			}
			else { simulateKeyPressk(keyCodeByte); }
		}
	}

	// 2.0 Eingabe > 1
	//2.1 Map Sondertaste also String eingabe 

	else if (MapST.find(str) != MapST.end()) {
		simulateST(MapST[str]);
		std::cout << "Mapping Zeichen ST: " << MapST[str] << std::endl;
	}
	//2.1 rest
	else {
		std::cout << "Dieses Zeichen hat keine spezielle Bedeutung." << std::endl;
	}











	return 0;
}
