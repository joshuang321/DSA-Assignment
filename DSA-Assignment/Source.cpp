//==================================================================
// Student Number : S10205140B, S10223630K
// Student Name :Joshua Ng, Armirola Roseller Iii Tumolva
// Module Group : P03
//==================================================================

#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "Account.h"
#include "Application.h"

DWORD dwOldConsoleMode;
void __cdecl win32_atexit(void);

using namespace std;


int main(void)
{
	Application app;
		
	/* Sets up virtual terminal processing for the console output */
	if (!GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),
		&dwOldConsoleMode))
	{
		cout << "Failed to set console mode!" << endl;
		return 0;
	}
	if (!SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), dwOldConsoleMode
		| ENABLE_VIRTUAL_TERMINAL_PROCESSING))
	{
		cout << "Failed to set console mode!" << endl;
		return 0;
	}
	atexit(win32_atexit);

	return app.Run();
}

void __cdecl win32_atexit()
{
	/* Resets console output mode back to normal */
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), dwOldConsoleMode);
}