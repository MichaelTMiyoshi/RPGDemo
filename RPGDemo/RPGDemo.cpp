/*
Author:		Miyoshi
Project:	RPG Demo
Purpose:	Simple console RPG and GitHub Repo
Pseudocode:
	-----GS1-4
	Output intro to the screen
	-----GS3-1
	Create variables for health, hit points, and name
	Choose max and min for health and hit points and randomly give them to the user
	Address the user by name where appropriate
	-----GS4-6
	main menu in a loop
		equip user
			equip user with at least one item
			must have 3 choices for item
		enter game
	game loop

Note:
	GitHub:		When making changes, you need to do the following:
			*****	Commit, Sync, Publish     *****
				Every time.
Maintenance Log:
08/16/2019	Began program from scratch
			Started with introduction (GS1-4)
			11:50	finished introduction
			13:02	cannot get VS to push changes (sync just pulls)
			13:09	figured out I need to commit the changes.
					Home button of Team Explorer, create commit message, press <Commit All> button.
					link below straightened me out.
			https://blogs.msdn.microsoft.com/benjaminperkins/2016/04/01/setting-up-and-using-github-in-visual-studio-2015/
			13:14	create variables and give them values (GS3-1)
			13:30	coded and tested.  Update to repository as branch variables.
					Need to make sure to PUBLISH the branch after updating.
			13:38	game loop and branching (GS4-6)
					made a branch off of variables.
			15:25	created the equip loop.
					created the game loop.
						three rooms.  (numbered 0, 1, 2)
						in room 1 is a pencil.  If you do not have a pencil, you can trade.
							if you decide not to trade, you cannot win
							when you come back again, you get second chance to exchange for the pencil
						room 2 is the exit.  if you have the pencil.  if not, you go back to room 0
					added an equipment name
					added a way to say you really want to exchange for the pencil
08/17/2019	Created functions.
			- showing statistics
			- setting equipmentName based on equipment (instead of needing to change both manually
			- checking health to see if you lose (health <= 0)
			- function for each room (3, numbered 0-2)
*/

#include <stdio.h>
#include <conio.h>
//#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
using namespace std;

void ShowStats(string name, int health, int hitPoints, string equipmentName)
{
	printf("%s.\nYour stats are:\n\tHealth:\t\t%d\n\tHit Points:\t%d\n", name.c_str(), health, hitPoints);
	printf("Your equipment:\n\t%s\n", equipmentName.c_str());
}

string SetEquipmentName(int equipment)
{
	switch (equipment)
	{
	case 1:
		return "pencil";
		break;
	case 2:
		return "laptop computer";
		break;
	case 3:
		return "book of matches";
		break;
	}
	return "";
}

bool TestHealth(int &health)
{
	if (health <= 0) 
	{
		printf("You lose!\n\n");
		health = 0;
		return false;
	}
	else
	{
		return true;
	}
}

int Room0(int room, int &health)
{
	char choice;
	printf("This is the first room\n");
	printf("Would you like to go to the second room?  (Y/N)  >>>  ");
	scanf_s("%c", &choice, 1);
	fseek(stdin, 0, SEEK_END);
	choice = toupper(choice);
	if (choice == 'Y')
	{
		room = 1;
	}
	else if (health < 10)
	{
		health++;
		printf("You increased your health.\n");
	}

	return room;
}

int Room1(int room, int &equipment, string equipmentName, int &timesThrough)
{
	char choice;
	printf("This is the second room\n");
	if (equipment != 1)	// not a pencil
	{
		printf("You found a pencil.\n");
		printf("Would you like to trade your %s for a pencil?  (Y/N)  >>>  ", equipmentName.c_str());
		scanf_s("%c", &choice, 1);
		fseek(stdin, 0, SEEK_END);
		choice = toupper(choice);
		if (choice == 'Y')
		{
			equipment = 1;
		}
		else
		{
			if (1 <= timesThrough)
			{
				printf("Are you sure you do not want the pencil?  (Y/N)  >>>  ");
				scanf_s("%c", &choice, 1);
				fseek(stdin, 0, SEEK_END);
				choice = toupper(choice);
				if (choice == 'N')
				{
					//continue;	// go back to the top of the loop
					return room;
				}

			}
		}
	}

	printf("\nWould you like to go to the third room?  (Y/N)  >>>  ");
	scanf_s("%c", &choice, 1);
	fseek(stdin, 0, SEEK_END);
	choice = toupper(choice);
	if (choice == 'Y')
	{
		room = 2;
	}

	timesThrough++;

	return room;
}

int Room2(int health, int equipment, string equipmentName)
{
	printf("I see that you brought a %s to take your final competency test.\n", equipmentName.c_str());
	if (equipment == 1)
	{
		printf("Very good.  You will need it to complete your task.\n\n");
	}
	else
	{
		printf("Too bad.  You will need a pencil to complete your task.\n\n");
		health -= 3;
	}
	return health;
}

int main()
{
	srand((unsigned)time(NULL));
// GS1-4 introduction
	printf("This is a Demo RPG created by Michael T. Miyoshi\n\n");
	printf("(It is also a demo for GitHub repos.)\n\n");
	printf("Your story starts when you began taking:\n");
	printf("Introduction to Computer Programming.\n\n");
	printf("Sounds scary already, doesn't it!\n\n");

// GS3-1 variables
	printf("Let us start by you telling me your name >>>  ");
	string name;
	getline(cin, name, '\n');	// let the user have spaces in name
	fseek(stdin, 0, SEEK_END);
	int min = 5, max = 10;
	int health;
	int hitPoints;

	health = min + rand() % (max - min + 1);
	hitPoints = min + rand() % (max - min + 1);

	printf("Well hello %s.\nYour stats are:\n\tHealth:\t\t%d\n\tHit Points:\t%d\n", name.c_str(), health, hitPoints);

//GS4-6 main menu and game loop
	bool ready = false;
	int equipment = 0;
	string equipmentName = "";
	do 
	{
		char choice;
		printf("\n\nYou get to choose one item before you begin.\n");
		printf("Which would you like?\n");
		printf("\tA. Pencil\n");
		printf("\tB. Laptop computer\n");
		printf("\tC. Book of matches\n");
		printf(">>>  ");
		scanf_s("%c", &choice, 1);
		fseek(stdin, 0, SEEK_END);
		ready = true;
		switch (choice)
		{
		case 'A': case 'a':
			equipment = 1;
			//equipmentName = "pencil";
			break;
		case 'B': case 'b':
			equipment = 2;
			//equipmentName = "laptop computer";
			break;
		case 'C': case 'c':
			equipment = 3;
			//equipmentName = "book of matches";
			break;
		default:
			printf("You must choose to arm yourself with something.");
			ready = false;
			break;
		}

		if (equipment != 0)
		{
			equipmentName = SetEquipmentName(equipment);
			printf("A %s is a great choice.", equipmentName.c_str());
		}

		if (!ready)
		{
			continue;
		}

		printf("\n\n\nAre you ready to play the game?  >>>  ");
		scanf_s("%c", &choice, 1);
		fseek(stdin, 0, SEEK_END);
		if (toupper(choice) == 'N')
		{
			ready = false;
			printf("\nOkay.  Let us equip you again.\n");
		}
	} while (!ready);

	bool exit = false;
	int room = 0;
	int timesThrough = 0;

	do
	{
		ShowStats(name, health, hitPoints, equipmentName);
		char choice;
		if (room == 0)
		{
			room = Room0(room, health);
		}
		else if (room == 1)
		{
			room = Room1(room, equipment, equipmentName, timesThrough);
			equipmentName = SetEquipmentName(equipment);	// in case the equipment changed
		}
		else if (room == 2)
		{
			printf("This is the third room\n");
			health = Room2(health, equipment, equipmentName);
			if (TestHealth(health) && equipment != 1)
			{
				printf("\n\nYou  must go back to the first room to study harder.\n");
				room = 0;
				printf("Press a key to go to the first room.\n\n");
				_getch();
				fseek(stdin, 0, SEEK_END);
			}
			else //if(!TestHealth(health)  || equipment == 1)
			{
				exit = true;
			}
		}
	} while (!exit);

	printf("Final Stats:\n\n");
	ShowStats(name, health, hitPoints, equipmentName);

	if (TestHealth(health))
	{
		printf("\n\nWay to go!  You made it past all the competency tests!\n\n");
	}
	else
	{
		printf("\n\nBetter luck next time.\n\n");
	}

	// keep these all together at the end of main()
	printf("\n\nPress the any key to exit...");
	_getch();
	return 0;
}