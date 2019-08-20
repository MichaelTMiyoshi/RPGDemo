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
08/19/2019	structs.
			user statistics modified to use a struct.
			send struct to functions instead of using single variable pass by ref and returning
				continue to return room from the rooms, pass struct by ref
			should add at least 2 NPCs (will be teachers)
				they are just talking heads not really NPCs
08/20/2019	Add a little color for a nicer UI or UE
			system("color bf");	// where b stands for background and f stands for foreground
				case does not matter for the hex digits in color call
				Hexadecimal digit	Color
								0	Black
								1	Blue
								2	Green
								3	Cyan
								4	Red
								5	Magenta
								6	Brown
								7	Light gray
								8	Dark gray
								9	Light blue
								A	Light green
								B	Light cyan
								C	Light red
								D	Light magenta
								E	Yellow
								F	White

08/20/2019	14:34	Created new branch called vector
					Will create NPCs.  Sorta.
					The struct of NPCs will just be dialogue.
					- Intro on its own.
					- Then some random stuff.
			15:18	Put in all the intro and dialogue strings for the NPCs.
					Decided to send the whole vector in the first room (room0).
					Sent only the appropriate element in the vector to the other two rooms.
*/

#include <stdio.h>
#include <conio.h>
//#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// GS7-6 enum and struct
enum Equip {none, pencil, laptop, matches};

struct Player
{
	string name;
	int health, hitPoints;
	Equip equipment;
	string equipmentName;
};

struct NPC
{
	string intro;
	vector<string> dialogue;
};

// GS6-6 functions
void ShowStats(Player P)
{
	printf("%s.\nYour stats are:\n\tHealth:\t\t%d\n\tHit Points:\t%d\n", P.name.c_str(), P.health, P.hitPoints);
	printf("Your equipment:\n\t%s\n", P.equipmentName.c_str());
}

string SetEquipmentName(Equip equipment)
{
	switch (equipment)
	{
	case pencil:
		return "pencil";
		break;
	case laptop:
		return "laptop computer";
		break;
	case matches:
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

void ResetColor()
{
	system("color 0A");
}

int Room0(int room, Player &P, vector<NPC> NPCs)
{
	char choice;
	printf("This is the first room.  %s\n", NPCs[room].intro.c_str());
	printf("%s\n", NPCs[room].dialogue[0].c_str());
	//printf("\n");
	printf("Would you like to go to the second room?  (Y/N)  >>>  ");
	scanf_s("%c", &choice, 1);
	fseek(stdin, 0, SEEK_END);
	choice = toupper(choice);
	if (choice == 'Y' || 10 <= P.health)
	{
		room = 1;
		if (P.health == 10)
		{
			printf("%s\n", NPCs[room].dialogue[1].c_str());
			printf("Press a key to continue...\n");
			_getch();
			fseek(stdin, 0, SEEK_END);
		}
	}
	else if (P.health < 10)
	{
		P.health++;
		printf("%s\n", NPCs[room].dialogue[2].c_str());
		printf("Press a key to continue...\n");
		_getch();
		fseek(stdin, 0, SEEK_END);
	}

	return room;
}

int Room1(int room, Player &P, int &timesThrough, NPC npc)	// pass one NPC instead of the whole vector
{
	char choice;
	printf("This is the second room\n");
	printf("%s\n", npc.intro.c_str());
	printf("%s\n", npc.dialogue[0].c_str());
	//printf("\n");
	if (P.equipment != pencil)	// not a pencil
	{
		//printf("You found a pencil.\n");
		printf("Would you like to trade your %s for a pencil?  (Y/N)  >>>  ", P.equipmentName.c_str());
		scanf_s("%c", &choice, 1);
		fseek(stdin, 0, SEEK_END);
		choice = toupper(choice);
		if (choice == 'Y')
		{
			P.equipment = pencil;
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

int Room2(Player P, NPC npc)
{
	printf("Welcome to the competency test room.\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x8A);
	printf("%s\n", npc.intro.c_str());
	//printf("\n");
	printf("%s\n", npc.dialogue[0].c_str());
	printf("I see that you brought a %s to take your final competency test.\n", P.equipmentName.c_str());
	if (P.equipment == 1)
	{
		printf("%s\n\n", npc.dialogue[1].c_str());
	}
	else
	{
		printf("%s\n\n", npc.dialogue[2].c_str());
		P.health -= 3;
	}
	ResetColor();
	return P.health;
}

vector<NPC> InitializeNPCs(vector<NPC> NPCs)
{
	NPC temp;
	temp.intro = "I am Mr. Taskmaster, your taskmaster.";
	temp.dialogue.push_back("You may study for competency tests here if you like or proceed\nto the next room to exchange equipment or sharpen pencils.");
	temp.dialogue.push_back("You have practiced enough.  You must go to the next room.");
	temp.dialogue.push_back("You increased your health by practicing a competency test.");
	NPCs.push_back(temp);
	temp.dialogue.clear();
	temp.intro = "I am Ms. Battle Axe, your armorer.";
	temp.dialogue.push_back("You may choose other items to equip yourself for the tests ahead.\nOr you may just go as you are.");
	NPCs.push_back(temp);	// example of ragged or jagged matrix because the NPC is a vector and the dialogue is a vector inside the vector
	temp.dialogue.clear();
	temp.intro = "I am Mr. Proctor, your test proctor.\nI am your doom!  Mwa ha ha!  Oops.  Sorry 'bout that.";
	temp.dialogue.push_back("You must complete the competency tests to win the game.");
	temp.dialogue.push_back("Very good.  You will need it to complete your task.");
	temp.dialogue.push_back("Too bad.  You will need a pencil to complete your task.");
	temp.dialogue.push_back("You  must go back to the first room to study harder.");
	NPCs.push_back(temp);

	return NPCs;
}

int main()
{
	srand((unsigned)time(NULL));
	system("color 0A");		// light green text on black background
// GS1-4 introduction
	printf("This is a Demo RPG created by Michael T. Miyoshi\n\n");
	printf("(It is also a demo for GitHub repos.)\n\n");
	printf("Your story starts when you began taking:\n");
	printf("Introduction to Computer Programming.\n\n");
	printf("Sounds scary already, doesn't it!\n\n");

// GS3-1 variables
	printf("Let us start by you telling me your name >>>  ");
	Player P;
	//string name;
	getline(cin, P.name, '\n');	// let the user have spaces in name
	fseek(stdin, 0, SEEK_END);
	int min = 5, max = 10;
	//int health;
	//int hitPoints;

	P.health = min + rand() % (max - min + 1);
	P.hitPoints = min + rand() % (max - min + 1);
	P.equipment = none;

	printf("Well hello %s.\nYour stats are:\n\tHealth:\t\t%d\n\tHit Points:\t%d\n", P.name.c_str(), P.health, P.hitPoints);

// GS8-6 vector of NPCs
	vector<NPC> NPCs;
	NPCs = InitializeNPCs(NPCs);

// GS4-6 main menu and game loop
	bool ready = false;
	//int equipment = 0;
	//string equipmentName = "";
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
			P.equipment = pencil;
			//equipmentName = "pencil";
			break;
		case 'B': case 'b':
			P.equipment = laptop;
			//equipmentName = "laptop computer";
			break;
		case 'C': case 'c':
			P.equipment = matches;
			//equipmentName = "book of matches";
			break;
		default:
			printf("You must choose to arm yourself with something.");
			P.equipment = none;
			ready = false;
			break;
		}

		if (P.equipment != none)
		{
			P.equipmentName = SetEquipmentName(P.equipment);
			printf("A %s is a great choice.", P.equipmentName.c_str());
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
	int timesThrough = 0;	// keeps track of room1() times through.  Asks if player is sure does not want to exchange.
	// game loop
	do
	{
		system("cls");
		ResetColor();
		ShowStats(P);
		printf("\n");
		char choice;
		if (room == 0)
		{
			room = Room0(room, P, NPCs);
		}
		else if (room == 1)
		{
			room = Room1(room, P, timesThrough, NPCs[room]);
			P.equipmentName = SetEquipmentName(P.equipment);	// in case the equipment changed
		}
		else if (room == 2)
		{
			printf("This is the third room\n");
			P.health = Room2(P, NPCs[room]);
			if (TestHealth(P.health) && P.equipment != 1)
			{
				printf("\n\n%s\n", NPCs[room].dialogue[3].c_str());
				room = 0;
				printf("Press a key to go to the first room.\n\n");
				_getch();
				fseek(stdin, 0, SEEK_END);
			}
			else //if(!TestHealth(health)  || equipment == 1)
			{
				exit = true;
				printf("Nice job, %s.\n", P.name.c_str());
				printf("Press a key to see your final stats.\n\n");
				_getch();
				fseek(stdin, 0, SEEK_END);
			}
		}
	} while (!exit);	// game loop end

	system("cls");
	printf("Final Stats:\n\n");
	ShowStats(P);

	// did you win or lose?
	if (TestHealth(P.health))
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