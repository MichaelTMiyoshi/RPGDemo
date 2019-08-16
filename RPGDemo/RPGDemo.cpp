/*
Author:		Miyoshi
Project:	RPG Demo
Purpose:	Simple console RPG and GitHub Repo
Pseudocode:
	Output intro to the screen
	Create variables for health, hit points, and name
	Choose max and min for health and hit points and randomly give them to the user
	Address the user by name where appropriate

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
*/

#include <stdio.h>
#include <conio.h>
//#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
using namespace std;

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
	int min = 5, max = 10;
	int health;
	int hitPoints;

	health = min + rand() % (max - min + 1);
	hitPoints = min + rand() % (max - min + 1);

	printf("Well hello %s.\nYour stats are:\n\tHealth:\t\t%d\n\tHit Points:\t%d\n", name.c_str(), health, hitPoints);

	// keep these all together at the end of main()
	printf("\n\nPress the any key to exit...");
	_getch();
	return 0;
}