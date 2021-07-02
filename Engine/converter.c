#include"converter.h"

#define ENCRYPTION_KEY 0x85
#define PRINT "TMSCOMPANY"
#define EXTENSION ".tms"

int convert(char pathname[])
{
    /*returns 1 if encrypted and 2 if already encrypted.*/

    // open file in read write binary mode.
    FILE* file;
    file = fopen(pathname, "rb+");
    if(file == NULL)
    {
       fprintf(stderr, "File Error: %s", strerror(errno));
        exit(-1);
    }
    // Return if already encrypted.
    if(encrypted(file))
        return 2;
    // otherwise encrypt the file.
    encrypt(file);
    // then create an inprint on the file.
    inprint(file, pathname);
    return 1;
}

int encrypt(FILE* file)
{
    int read = 0;
    int charSize = sizeof(unsigned char);
    fseek(file, 0, SEEK_SET); // go the the begining of the file

    // Allocating memory to buffer of size MAX_BYTE
    unsigned char* buffer = (unsigned char*) calloc(charSize, MAX_BYTE);
    if(buffer == NULL)
    {
        fprintf(stderr,"Memory error: %s", strerror(errno));
        exit(-2);
    }
    // Reading bytes(charsize = 1) from file to buffer. maximum readable byte is of MAX_BYTE.
    read = fread(buffer, charSize,MAX_BYTE, file);
    //Reallocating memory to fit exactly the size of the read bytes from file.
    buffer = realloc(buffer,read * charSize);
    // Encrypting the read bytes with the Encryption key by subtracting from the value of Each byte
    for(int i = 0; i < read; i++)
    {
        buffer[i] -= ENCRYPTION_KEY;
    }
    // Resetting the file cursor and replacing the read bytes with encrypted bytes
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, charSize, read, file);
}


int inprint(FILE* file, char* pathname)
{
    
    char* printdata = strdup(PRINT);
    // duplicate pathname
    char* _path = strdup(pathname);
    // Get file extension
    char* ext = strrchr(pathname, '.');
    if(!ext)
    {
        fprintf(stderr,"This should not happen!: ", strerror(errno)); ///******** check later
    }
    // Concatenate the extension in the print data
    strcat(printdata, ext);
    //concatenate the print data length int the printdata
    char len[2];
    len[0] = strlen(printdata) + 1;    // +1 for the len itself to be appended
    len[1] = '\0';                     // len in string format because of strcat.
    strcat(printdata, len);
    // go to the end of the file and inprint the print data
    fseek(file, 0, SEEK_END);
    fwrite(printdata, sizeof(char), len[0], file);
    // exclude original extension from allocated memory and append EXTENSION
    strrev(_path); 
    _path = strchr(_path, '.');
    char* basename = _path + 1; // passing the path without the '.'
    strrev(basename);
    strcat(basename, EXTENSION);
    // close file stream
    fclose(file);
    //rename to .tms extension
    rename(pathname, basename);
    //realease memory back to the OS.
    free(_path);
    free(printdata);
    
}


int encrypted(FILE* file)
{
    // Go the end of the file and get the last byte
    fseek(file, -1, SEEK_END);
    unsigned char printsize;
    fread(&printsize, sizeof(printsize), 1, file);
    // Use the last byte to get PRINT also using the length of PRINT
    char* print = (char*)calloc(sizeof(char), strlen(PRINT)+1);
    if(print == NULL)
    {
        fprintf(stderr,"Memory error: %s", strerror(errno));
        exit(-3);
    }
    fseek(file, -1*printsize,SEEK_END);
    fread(print, sizeof(char), strlen(PRINT), file);
    // Compare both PRINTS 
    char* initprint = strdup(PRINT);
    if(strcmp(print, initprint) == 0)
    {
        free(print);
        free(initprint);
        return 1;
    }
    else
    {
        free(print);
        free(initprint);
        return 0;
    }
}
