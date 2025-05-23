// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <string>
#include <array>
#include <vector>
#include<map>
#include <iostream>
#include <codecvt>
#include <locale> // Include this header for std::codecvt_utf8
#include <cctype>

// Global variables
bool shiftActive = false;
// Ensure the ButtonInfo struct is declared before using it in the std::vector declaration.  
struct ButtonInfo {  
    std::wstring text; // Text of the button  
    int x; // x-position of the button  
    int y; // y-position of the button  
    int width; // Width of the button  
    int height; // Height of the button  
};  
std::vector<ButtonInfo> flatButtons;
// Correct the std::vector declaration by ensuring ButtonInfo is a valid type.  

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");
//variable behältihren wert zwischen den funktionsaufrufen: zähler funktion: jedes mal wenn aufgerufen wird zähler um eins erhöt. sonst immer zurückgesetzt
//sorgt für Erstellung von ANSI und Unicode kompatiblen programmen. Ohne: Muss code geändert werden je nach dem was benutzt wird.


// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Virtual Keyboard");


// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//Wert der ende ende der funktion angibt
// !!!CALLBACK!!!
//Funktion, die sich um alles kümmert, was mit dem Fenster zu tun hat.
//PArameter
//Identifikator ein bestimmtes fenster
//Gibt eine Nummer an, bspw 1 bed: fenster hat sich geöfnet usw
//letzten parameter geben an um was es sich bei msg handelt

void simulateShiftPlusOne(char n) {

	// Struktur für die Eingabe in ip werden die Variablen von unten eingesetzt
	INPUT ip[1] = { 0 };

	// Allg. für eingabe sagt soviel wie: Eingabe ist Tastendruck 
	ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.wVk = VK_SHIFT; // Virtueller Tastencode !Byte wird als wert erwartet
	ip[0].ki.dwFlags = 0; // 0 für Tastendruck

	


	 //Tastendruck wird gesendet
	SendInput(1, ip, sizeof(INPUT));
}

void simulateKeyPressPlus(char n) {
	INPUT ip[2] = { 0 };


	// Allg. für eingabe sagt soviel wie: Eingabe ist Tastendruck 
	ip[0].type = INPUT_KEYBOARD;
	ip[0].ki.wVk = VkKeyScan(n); // Virtueller Tastencode !Byte wird als wert erwartet
	ip[0].ki.dwFlags = 0; // 0 für Tastendruck


	SendInput(1, ip, sizeof(INPUT));

	ip[0].ki.dwFlags = KEYEVENTF_KEYUP;
	ip[1].ki.dwFlags = KEYEVENTF_KEYUP;




	//Tastendruck wird gesendet}


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


	
}
//x,y position des fensters	braucht man nicht, Offset:



// Benutzerdefinierte Einstellungen für bestimmte Tasten
struct CustomButton {
	std::wstring text;
	int x; // x-Position des Buttons
	int y;
	int width;
	int height;
	int spacing;

	// Optional: weitere Eigenschaften wie Farbe, Font etc.
};


int WINAPI WinMain(                         //Wie wird funktion aufgerufen 
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,       //Schlüssel für vorherige instanz
	_In_ LPSTR     lpCmdLine,               //Befehlsliste was gemacht werden soll. Programm bekommt input bspw 8908 und weiß links drehen
	_In_ int       nCmdShow                 // Wie soll das erzeugte fenster angezeigt werden //Ohne def standard
)
{
	WNDCLASSEX wcex = {};                                                //wcex Bauanleitung für Fensterklasse nur für lesbarkeit

	wcex.cbSize = sizeof(WNDCLASSEX);                               //größe in bytes                               
	wcex.style = CS_HREDRAW | CS_VREDRAW;                           //Stil Fensterklasse. hier: wenn fenster in der höhe oder breite verändert wird, wird es neu gezeichnet
	wcex.lpfnWndProc = WndProc;                                     //Zeiger auf die Fensterprozedur, wo werden tastendrücke verarbeitet
	wcex.cbClsExtra = 0;                                            //Zusätzliche Bytes für die Fensterklasse                
	wcex.cbWndExtra = 0;                                            //Zusätzliche Bytes für das Fenster                    
	wcex.hInstance = hInstance;                                     //Handle der Instanz, verwendet um auf resourcen zuzugreifen, die mit Anwendung verbunden sind       
	wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);         //Icon der Anwendung
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                     //Mauszeiger                
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);                //Hintergrundfarbe des Fensters hier  standard    
	wcex.lpszMenuName = NULL;                                       //Menü der Anwendung 
	wcex.lpszClassName = szWindowClass;                             //Name der Fensterklasse ist name des Automodells für verweise auf andere fenster die geleich aussehn sollen
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);       //Icon der Anwendung

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Windows Desktop Guided Tour"),
			NULL);

		return 1;
	}

	// Store instance handle in our global variable
	hInst = hInstance;



	HWND hWnd = CreateWindowEx(

		WS_EX_OVERLAPPEDWINDOW,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1000, 350,							//position letztes taste abgreifen lies: höhe und breite des fensters sind dynamisch mit den tasten
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd) {
		MessageBox(NULL, _T("Call to CreateWindowEx failed!"), _T("Fehler"), MB_ICONERROR);
		return 1;
	}

	//Standard Werte
	const int defaultWidth = 40;
	const int defaultHeight = 30;
	const int spacing = 5;
	const int startX = 10;
	const int startY = 40;

	// Tastatur-Layout: Zeilen, Tasten
	std::vector<std::vector<std::wstring>> keyboardRows = {
		{ L"ESC",L"F1", L"F2", L"F3", L"F4", L"F5", L"F6", L"F7", L"F8", L"F9", L"F10", L"F11", L"F12"},
		{ L"^", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"0", L"ß", L"´",L"BACK" ,L"INSERT", L"HOME", L"PAGE UP"},
		{ L"TAB", L"Q", L"W", L"E", L"R", L"T", L"Z", L"U", L"I", L"O", L"P", L"Ü", L"+" ,L"RETURN", L"DELETE", L"END", L"PAGE DOWN" },
		{ L"CAPS LOCK", L"A", L"S", L"D", L"F", L"G", L"H", L"J", L"K", L"L", L"Ö", L"Ä",L"#" },
		{ L"LSHIFT", L"<", L"Y", L"X", L"C", L"V", L"B", L"N", L"M", L",", L".", L"-",L"RSHIFT" ,L"ARROW UP"},
		{ L"LCTRL", L"LWIN", L"ALT", L"SPACE", L"ALT GR", L"RWIN", L"MENU", L"RCTRL", L"ARROW LEFT", L"ARROW DOWN", L"ARROW RIGHT"}
	};

	// Beispiel: Zwei benutzerdefinierte Tasten
	int abstBlock2 = 20;
	// Update the initialization of the `customButtons` vector to ensure proper construction of `CustomButton` objects.  
	std::vector<CustomButton> customButtons = {
		{L"ESC", startX, startY, 60, defaultHeight, spacing + 45},
		{L"F4", startX, startY, defaultWidth, defaultHeight, spacing + 45},
		{L"F8", startX, startY, defaultWidth,defaultHeight, spacing + 45 },
		{L"BACK", startX, startY, 150, defaultHeight, abstBlock2},
		{L"TAB", startX, startY, 60, defaultHeight, spacing},
		{L"+", startX, startY, 60, defaultHeight, spacing + 15},
		{L"RETURN", startX, startY, 95, 2 * defaultHeight + 5,abstBlock2},
		{L"CAPS LOCK", startX, startY, 90, defaultHeight, spacing},
		{L"LSHIFT", startX, startY, 55, defaultHeight, spacing},
		{L"RSHIFT", startX, startY, 180, defaultHeight, abstBlock2 + 45},
		{L"SPACE", startX, startY, 240, defaultHeight, spacing}  ,
		{ L"LCTRL", startX, startY, 65, defaultHeight, spacing },
		{ L"LWIN", startX, startY, 65, defaultHeight, spacing },
		{ L"ALT", startX, startY, 65, defaultHeight, spacing },
		{ L"ALT GR", startX, startY, 65, defaultHeight, spacing },
		{ L"RWIN", startX, startY, 65, defaultHeight, spacing },
		{ L"MENU", startX, startY, 65, defaultHeight, spacing },
		{ L"RCTRL", startX, startY, 70, defaultHeight, abstBlock2 }
	};

	// In WinMain, vor dem Befüllen:
	flatButtons.clear();

	int y = startY;
	for (const auto& row : keyboardRows) {
		int x = startX;
		for (const auto& key : row) {
			// Standardwerte
			int w = defaultWidth;
			int h = defaultHeight;
			int s = spacing;

			// Prüfen, ob Taste benutzerdefiniert ist
			for (const auto& custom : customButtons) {
				if (custom.text == key) {
					w = custom.width;
					h = custom.height;
					s = custom.spacing;
					break;
				}
			}

			
            // Update the push_back call to ensure the correct constructor is used for ButtonInfo.  
            flatButtons.push_back(ButtonInfo{ std::wstring(key), x, y, w, h });
			x += w + s;
		}
		y += defaultHeight + spacing;
	}

	// Button-Erstellung


	HFONT hFont = CreateFontW(
		18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI"
	);

	for (size_t i = 0; i < flatButtons.size(); ++i) {
		const ButtonInfo& info = flatButtons[i];
		HWND btnHwnd = CreateWindowW(
			L"BUTTON",
			info.text.c_str(),
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			info.x, info.y, info.width, info.height,
			hWnd,
			(HMENU)(INT_PTR)(100 + i),
			hInst,
			NULL
		);

		// Schriftart für den Button setzen
		SendMessage(btnHwnd, WM_SETFONT, (WPARAM)hFont, TRUE);



	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	// Main message loop:
	MSG msg;                                     //msg wird hier als Feedback von windows verwendet   

	while (GetMessage(&msg, NULL, 0, 0)) // Check for messages in the queue.  
	{
		TranslateMessage(&msg); // Translate keyboard input messages.  
		DispatchMessage(&msg);  // Dispatch the message to the appropriate window procedure.  
	}


	return (int)msg.wParam;

}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;                                        // Struktur wie sieht es aus?
	HDC hdc;                                            // Was ist es für ein endgerät?
	TCHAR greeting[] = _T("Press A Button");   // Text innerhalb der Anwendung

	switch (message)    //wenn message (feedback von windows ist:
	{
	case WM_PAINT:          //programm wird eöfnet 

		hdc = BeginPaint(hWnd, &ps);//kreiere das fenster in dem anderen fenster.

		// Here your application is laid out.
		// For this introduction, we just print out "Hello, Windows desktop!"
		// in the top left corner.
		TextOut(hdc,
			5, 5,
			greeting, int(_tcslen(greeting)));
		// End application-specific layout section.

		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
	{
		Sleep(3000);
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
		
		
		int buttonId = LOWORD(wParam);
		int index = buttonId - 100;
		if (index >= 0 && index < flatButtons.size()) {
			std::wstring buttonText = flatButtons[index].text;
			char zeichen = static_cast<char>(buttonText[0]);

			//1.Fall : kleinbuchstabe/Zahl Geht


			if (buttonText.size() == 1 && isalnum(zeichen)) {
				simulateKeyPressk(zeichen);

				return 0;

			}

			//2.Fall sonderzeichen mapping mit Mapaltgr

			

		else if (buttonText == L"LSHIFT" || buttonText == L"RSHIFT") {
				if (!shiftActive) {
					INPUT ip = { 0 };
					ip.type = INPUT_KEYBOARD;
					ip.ki.wVk = VK_SHIFT;
					ip.ki.dwFlags = 0; // Key down
					SendInput(1, &ip, sizeof(INPUT));


					return 0;
				}
				if(shiftActive == true && buttonText.size() == 1) {
					
					simulateKeyPressG(toupper(zeichen), zeichen); // Shift-Taste loslassen und Taste drücken
				
					

					shiftActive = false;
					return 0;
				
				}

				else if(buttonText == L"ALT") {}

				
				}
				
				else {
					shiftActive = false;
					simulateKeyPressk(zeichen); // Shift-Taste loslassen und Taste drücken
				
					return 0;

				 
				// keypress zweite taste
				// ausgabe von beiden tasten
				// tste hoch
				
				 }


			
			

					
				
			}
		}


		
			


	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}



/*std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
std::string str = converter.to_bytes(buttonText);

if (MapST.find(str) != MapST.end()) {
	simulateST(MapST[str]);
}*/