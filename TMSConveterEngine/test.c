#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char str[] = "hello world!";
    system("cls");
    printf("%s\n%s\n", strrev(str), str);

    return 0;
}