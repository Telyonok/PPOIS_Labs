#include "Menu.h"

void Menu::StartUpMenu()
{
	system("cls");
	PrintMenu();
	switch (GetPlayerChoice())
	{
	case 1:
		StartGame();
		break;
	case 2:
		return;
		break;
	default:
		StartUpMenu();
		break;
	}
}

void Menu::PrintMenu()
{
	cout << "WELCOME TO THE GAME OF TAGPUZZLE!!!!\n\n1-Start Game\n2-Quit\n";
}

void Menu::StartGame()
{
	puzzle = new Puzzle();
	Congratulate();
}

void Menu::Congratulate()
{
	cout << "\n\n\n\n\nCONGRATULATIONS!!!!! You did it!\n";
}

int Menu::GetPlayerChoice()
{
	int a;
	cin >> a;
	return a;
}
