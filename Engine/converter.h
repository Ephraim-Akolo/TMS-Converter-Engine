/* This program takes the absolute path of the file 
e.g video, then encripts the file and overwrites
the original video */

#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#define MAX_MEGABYTE 4
#define MAX_BYTE (MAX_MEGABYTE*1024)

// Takes the source path of file to encript.
int convert(char* );
// Takes a file stream and verifies if encrypted.
int encrypted(FILE*);
// Takes a file stream and encrypts it.
int encrypt(FILE*);
// Takes a file stream and file path to inprint on the file and change its extension.
int inprint(FILE*, char* );
