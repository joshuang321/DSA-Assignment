#include <iostream>
#ifdef __WINDOWS
#include <Windows.h>
#endif

#ifdef __WINDOWS
DWORD dwOldConsoleMode;
void __cdecl win32_atexit(void);
#endif

std::string clrsr = "\x1B[2J\x1B[H";
void printMenu();

int main(void)
{
	int choice = 0;

#ifdef __WINDOWS
	if (!GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),
		&dwOldConsoleMode))
	{
		std::cout << "Failed to set console mode!" << std::endl;
		return 0;
	}
	if (!SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), dwOldConsoleMode
		| ENABLE_VIRTUAL_TERMINAL_PROCESSING))
	{
		std::cout << "Failed to set console mode!" << std::endl;
		return 0;
	}
	atexit(win32_atexit);
#endif

	while (true)
	{
		printMenu();
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			break;
		
		case 2:
			break;

		case 3:
			std::cout << clrsr << "Goodbye!" << std::endl;
			return 0;
		}
	}
}

#ifdef __WINDOWS
void __cdecl win32_atexit()
{
	SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), dwOldConsoleMode);
}
#endif

void printMenu()
{
	std::cout << "==========Menu==========" << std::endl
		<< "[1] Login" << std::endl
		<< "[2] Register" << std::endl
		<< "[3] Exit" << std::endl
		<< "Your choice? ";
}