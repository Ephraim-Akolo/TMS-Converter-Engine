#include"converter.h"

#define ENCRYPTION_KEY 0x01
#define PRINT "TMSCOMPANY"

int convert(char pathname[])
{
    // open file in read write binary mode.
    FILE* file;
    file = fopen(pathname, "rb+");
    if(file == NULL)
    {
       fprintf(stderr, "File Error: %s", strerror(errno));
        exit(-1);
    }

   // if(encrypted(file))
     //   printf("Encrypted!\n\n");

   // encrypt(file);

    inprint(file, pathname);
    fclose(file);
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


int inprint(FILE* file, const char* pathname)
{
   fseek(file, 0, SEEK_END);
   char _print[] = PRINT;
   strrchr()
}


int encrypted(FILE* file)
{
    
}
