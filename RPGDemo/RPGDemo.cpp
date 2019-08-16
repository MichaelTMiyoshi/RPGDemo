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
			13:09 figured out I need to commit the changes.
					Home button of Team Explorer, create commit message, press <Commit All> button.
					link below straightened me out.
			https://blogs.msdn.microsoft.com/benjaminperkins/2016/04/01/setting-up-and-using-github-in-visual-studio-2015/
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