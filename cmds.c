/******************************************************************
*
*   file:     cmds.c
*   author:   betty o'neil
*   date:     ?
*
*   semantic actions for commands called by tutor (cs341, hw2)
*
*   revisions:
*      9/90  eb   cleanup, convert function declarations to ansi
*      9/91  eb   changes so that this can be used for hw1
*      9/02  re   minor changes to quit command
*/
/* the Makefile arranges that #include <..> searches in the right
   places for these headers-- 200920*/

#include <stdio.h>
#include "slex.h"

/*===================================================================*
*
*   Command table for tutor program -- an array of structures of type
*   cmd -- for each command provide the token, the function to call when
*   that token is found, and the help message.
*
*   slex.h contains the typdef for struct cmd, and declares the
*   cmds array as extern to all the other parts of the program.
*   Code in slex.c parses user input command line and calls the
*   requested semantic action, passing a pointer to the cmd struct
*   and any arguments the user may have entered.
*
*===================================================================*/

PROTOTYPE int stop(Cmd *cp, char *arguments);
PROTOTYPE int mem_display(Cmd *cp, char *arguments);
PROTOTYPE int mem_set(Cmd *cp, char *arguments);
PROTOTYPE int help(Cmd *cp, char *arguments);
/* command table */

Cmd cmds[] = {{"md",  mem_display, "Memory display: MD <addr>"},
				{"ms", mem_set, "Memory set: MS <addr> <value>"},
				{"h", help, "Help: H <command>"},
              {"s",   stop,        "Stop" },
              {NULL,  NULL,        NULL}};  /* null cmd to flag end of table */

char xyz = 6;  /* test global variable  */
char *pxyz = &xyz;  /* test pointer to xyz */
/*===================================================================*
*		command			routines
*
*   Each command routine is called with 2 args, the remaining
*   part of the line to parse and a pointer to the struct cmd for this
*   command. Each returns 0 for continue or 1 for all-done.
*
*===================================================================*/

int stop(Cmd *cp, char *arguments)
{
  return 1;			/* all done flag */
}

/*===================================================================*
*
*   mem_display: display contents of 16 bytes in hex
*
*/

int mem_display(Cmd *cp, char *arguments)
{
  int numprint = 0;
  int address = 0;
  unsigned char *adrs_ptr;
  sscanf(arguments, "%x", &address);
  adrs_ptr =(char *)address;
  //printf("address I keep trying to print: %x\n", thing);
  printf("Hey here is a text: %x; %02x ", address, *adrs_ptr++);  
  //some for loop bs to print all values
  for(numprint=0;numprint <16; numprint++)
	printf("%02x ", *adrs_ptr++); 
  adrs_ptr = (unsigned char *)address;
  printf("\n");
  for(numprint=0;numprint<16;numprint++)
	if(*adrs_ptr > 0x20 && *adrs_ptr < 0x7F)
		printf("%c", *adrs_ptr++);
	else
	{	
		printf(".");
		adrs_ptr++;
	}
  printf("\n");
  printf("Reached mem_display, passed argument string: |%s|\n", arguments);
  printf("        help message: %s\n", cp->help);
  return 0;			/* not done */
}

/*===================================================================*
*
*    mem_set: sets the address with the value typed
*
*/

int mem_set(Cmd *cp, char *arguments)
 {
	int address = 0;
	int value = 0;
	char *adrs_ptr;
	sscanf(arguments,"%x %x", &address, &value);
	adrs_ptr = (char *)address;
	*adrs_ptr = value;
	//printf("this is the address I changed: |%s|\n", arguments);
	//printf("now it is this: %x; %02x \n", address, *adrs_ptr); 
	return 0;
 }


/*====================================================================*
*
*	help: something something help
*
*/

int help(Cmd *cp, char *arguments)
{
	char string[2];
	int num = 0;
	int length = sizeof(cmds)/sizeof(Cmd);
	sscanf(arguments, "%s", string);
	for(num=0; num < length-1;num++)
		if((strcmp(cmds[num].cmdtoken, string)) == 0)
			printf("%s\n", cmds[num].help);

	return 0;
}	
