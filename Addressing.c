#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fpr=NULL,*fpw=NULL;

int main()
{
    char label[10],mnemonic[10],operand[10],program_name[10];
    int address=0,first_address=0,previous_address=0,last_address=0,line=0,c=0,p1=0,p2=0,i=0,length,x=0;

    /*Adressing*/

    fpr=fopen("input.txt","r");
    fpw=fopen("addressed_file.txt","w");

    fscanf(fpr,"%s%s%d",&program_name,&mnemonic,&address);
    line++;
    fprintf(fpw,"%d\t\t%s\t%s\t%d\n",line,program_name,mnemonic,address);

    while(strcmp(mnemonic,"END")!=0)
    {
        if(strcmp(label,".")!=0)
        {
            fscanf(fpr,"%s%s%s",&label,&mnemonic,&operand);
            line++;

            if(line>=2)
            {
                fprintf(fpw,"%d\t%.4d\t%s\t%s\t%s\n",line,address,label,mnemonic,operand);

                if(strcmp(mnemonic,"BYTE")==0)
                {
                    length=0;
                    length=strlen(operand);

                    length-=3; /*excluding C'' */

                    address+=length;
                }
                else if(strcmp(mnemonic,"WORD")==0)
                {
                    address+=3;
                }
                else if(strcmp(mnemonic,"RESW")==0)
                {
                    x=atoi(operand); /*converting character into integer */
                    address+=(x*3); /*1 WORD = 3 BYTES */
                }
                else if(strcmp(mnemonic,"RESB")==0)
                {
                    x=atoi(operand); /*change RESB's mnemonic into hexadecimal --> x, address+=x; */
                    address+=x;
                }
                else
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

