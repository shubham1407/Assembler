/*  ===========================================================================================
    Program  : Finding the program name
    Author   : Ashutosh Verma( B.tech - CSE, 5th Semester(A), GEU)
    Language : C
    Compiler : GNU GCC Compiler for MSP430
    IDE      : Codeblocks svn 8549
    Email-id : ashutoshvrm8@gmail.com
    ===========================================================================================
*/

#include<stdio.h>
#include<string.h>

FILE *fpr=NULL,*fpw=NULL;

int main()
{
    char mnemonic[10],operand[10],program_name[10];

    fpr=fopen("input.txt","r");

    fscanf(fpr,"%s%s%s",&program_name,&mnemonic,&operand);

    fclose(fpr);

    printf("%s",program_name);

    return 0;
}

