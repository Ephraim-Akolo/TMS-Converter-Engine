/* This program takes the absolute path of the video(s)
with the number of path provided, then encripts the 
video and overwrites the original video */

#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#define MAX_MEGABYTE 4
#define MAX_BYTE (MAX_MEGABYTE*1024)

// Takes the source path of file to encript.
int convert(char* );

//Takes the source path and checks for TMS extension.
int encrypted(FILE*);

int encrypt(FILE*);

int inprint(FILE*, const char* );
