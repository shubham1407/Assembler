/*  ===========================================================================================
    Program  :
    Author   : Ashutosh Verma( B.tech - CSE, 5th Semester(A), GEU)
    Language : C
    Compiler : GNU GCC Compiler for MSP430
    IDE      : Codeblocks svn 8549
    Email-id : ashutoshvrm8@gmail.com
    ===========================================================================================
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fpr=NULL,*fpw=NULL;

int main()
{
    char label[10],mnemonic[10],operand[10],program_name[10];
    int address=0,first_address=0,previous_address=0,last_address=0,line=0;

    /*Adressing*/

    fpr=fopen("input.txt","r");
    fpw=fopen("addressed_file.txt","w");

    fscanf(fpr,"%s%s%d",&program_name,&mnemonic,&address);
    fprintf(fpw,"\t%s\t%s\t%d\n",program_name,mnemonic,address);
    line++;

    printf("\n%d\n",address);

    while(strcmp(mnemonic,"END")!=0)
    {
        if(strcmp(label,".")!=0)
        {
            fscanf(fpr,"%s%s%s",&label,&mnemonic,&operand);
            line++;

            if(line>=2)
            {
                fprintf(fpw,"%.4d\t%s\t%s\t%s\n",address,label,mnemonic,operand);
                address+=3;
            }
        }
        else
        {
            fprintf(fpw,"\n");
        }
    }

    fclose(fpr);
    fclose(fpw);

    return 0;
}

