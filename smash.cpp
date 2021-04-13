/*	smash.c
main file. This file contains the main function of smash
*******************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "commands.h"
#include "signals.h"
#define MAX_LINE_SIZE 80
#define MAXARGS 20
#define MAXPATHLEN 2048
#include <iostream>
#include <string.h>

char* L_Fg_Cmd;
void* jobs = NULL; //This represents the list of jobs. Please change to a preferred type (e.g array of char*)
char lineSize[MAX_LINE_SIZE]; 
//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
    char cmdString[MAX_LINE_SIZE]; 	   

	
	//signal declaretions
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.c
	 /* add your code here */
	
	/************************************/
	//NOTE: the signal handlers and the function/s that sets the handler should be found in siganls.c
	//set your signal handlers here
	/* add your code here */

	/************************************/

	/************************************/
	// Init globals 
    char temp_path[MAXPATHLEN];
    Global char *last_cd_tmp = new char[MAXPATHLEN + 1];
    char *last_cd = new char[MAXPATHLEN + 1];
	
	L_Fg_Cmd =(char*)malloc(sizeof(char)*(MAX_LINE_SIZE+1));
	if (L_Fg_Cmd == NULL) 
			exit (-1); 
	L_Fg_Cmd[0] = '\0';
	
    	while (1)
    	{
	 	printf("smash > ");
		fgets(lineSize, MAX_LINE_SIZE, stdin);
		strcpy(cmdString, lineSize);    	
		cmdString[strlen(lineSize)-1]='\0';
					// perform a complicated Command
		if(!ExeComp(lineSize)) continue; 
					// background command	
	 	if(!BgCmd(lineSize, jobs)) continue; 
					// built in commands
		ExeCmd(jobs, lineSize, cmdString);
		
		/* initialize for next line read*/
		lineSize[0]='\0';
		cmdString[0]='\0';
	}
    /**
     * remmeber!
     */
    //clear_memory;
    return 0;
}

//		commands.c
//********************************************
#define MAXPATHLEN 2048
//********************************************
#include "commands.h"

//********************************************
// function name: ExeCmd
// Description: interperts and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
using namespace std;
int ExeCmd(void* jobs, char* lineSize, char* cmdString)
{
    char* cmd;
    char* args[MAX_ARG];
    char pwd[MAX_LINE_SIZE];
    char* delimiters = " \t\n";
    int i = 0, num_arg = 0;
    bool illegal_cmd = FALSE; // illegal command
    cmd = strtok(lineSize, delimiters);
    if (cmd == NULL)
        return 0;
    args[0] = cmd;
    for (i=1; i<MAX_ARG; i++)
    {
        args[i] = strtok(NULL, delimiters);
        if (args[i] != NULL)
            num_arg++;

    }
//******************************************* our additions
    bool last_cd_exist = false;
/*************************************************/
// Built in Commands PLEASE NOTE NOT ALL REQUIRED
// ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
// MORE IF STATEMENTS AS REQUIRED
/*************************************************/
    if (!strcmp(cmd, "cd") ) {

        if ((args[1] == "-") && (last_cd_exist));
        {
            int ret_val_cdir = chdir(last_cd);
            if (ret_val_cdir == -1) {
                cout << "\"" << cmdString << "\" " << "- No such file or directory" << endl;
            }


            strcpy(last_cd_tmp, temp_path);


            if (ret_val_cdir == -1) {
                cout << "\"" << cmdString << "\" " << "- No such file or directory" << endl;
            } else {

                strcpy(last_cd, temp_path);
                last_cd_exist = true;
            }
        }
    }

        /*************************************************/
    else if (!strcmp(cmd, "pwd"))
    {
        char temp[MAXPATHLEN];
        cout << ( getcwd(temp, sizeof(temp)) ? std::string( temp ) : std::string("") ) << endl;
    }

        /*************************************************/
    else if (!strcmp(cmd, "mkdir"))
    {

    }
        /*************************************************/

    else if (!strcmp(cmd, "jobs"))
    {

    }
        /*************************************************/
    else if (!strcmp(cmd, "showpid"))
    {

    }
        /*************************************************/
    else if (!strcmp(cmd, "fg"))
    {

    }
        /*************************************************/
    else if (!strcmp(cmd, "bg"))
    {

    }
        /*************************************************/
    else if (!strcmp(cmd, "quit"))
    {

    }
        /*************************************************/
    else // external command
    {
        clear_memory;
        ExeExternal(args, cmdString);
        return 0;
    }
    if (illegal_cmd == TRUE)
    {
        printf("smash error: > \"%s\"\n", cmdString);
        return 1;
    }
    return 0;
}
//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//**************************************************************************************
void ExeExternal(char *args[MAX_ARG], char* cmdString)
{
    int pID;
    switch(pID = fork())
    {
        case -1:
            // Add your code here (error)

            /*
            your code
            */
        case 0 :
            // Child Process
            setpgrp();

            // Add your code here (execute an external command)

            /*
            your code
            */

        default:
            // Add your code here

            cout << ("our default") << endl;
            /*
            your code
            */
    }
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char* lineSize)
{
    char ExtCmd[MAX_LINE_SIZE+2];
    char *args[MAX_ARG];
    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) || (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&")))
    {
        // Add your code here (execute a complicated command)

        /*
        your code
        */
    }
    return -1;
}
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize, void* jobs)
{

    char* Command;
    char* delimiters = " \t\n";
    char *args[MAX_ARG];
    if (lineSize[strlen(lineSize)-2] == '&')
    {
        lineSize[strlen(lineSize)-2] = '\0';
        // Add your code here (execute a in the background)

        /*
        your code
        */

    }
    return -1;
}

