/*
Author:		Miyoshi
Project:	RPG Demo
Purpose:	Simple console RPG and GitHub Repo
Pseudocode:
	Output intro to the screen

Maintenance Log:
08/16/2019	Began program from scratch
			Started with introduction
			11:50 finished introduction
			13:02 cannot get VS to push changes (sync just pulls)
*/

#include <stdio.h>
#include <conio.h>

int main()
{
	printf("This is a Demo RPG created by Michael T. Miyoshi\n\n");
	printf("(It is also a demo for GitHub repos.)\n\n");
	printf("Your story starts when you began taking:\n");
	printf("Introduction to Computer Programming.\n\n");
	printf("Sounds scary already, doesn't it!");

	// keep these all together at the end of main()
	printf("\n\nPress the any key to exit...");
	_getch();
	return 0;
}