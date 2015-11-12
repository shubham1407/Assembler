#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fpr=NULL,*fpw=NULL;

int main()
{
    char label[10],mnemonic[10],operand[10],program_name[10];
    int address=0,line=0,length,x=0,first_address=0,last_address=0;

    /*Adressing*/

    fpr=fopen("new_input.txt","r");
    fpw=fopen("addressed_file.txt","w");

    fscanf(fpr,"%s%s%X",&program_name,&mnemonic,&address);  /*Reading data from input.txt*/
    line++;
    fprintf(fpw,"%d\t\t%s\t%s\t%.4X\n",line,program_name,mnemonic,address);  /*Writing data into addressed_file.txt */

    while(strcmp(mnemonic,"END")!=0)
    {
        if(strcmp(label,".")!=0)        /*For checking comments*/
        {
            fscanf(fpr,"%s%s%s",&label,&mnemonic,&operand);
            line++;

            /*Writing data into addressed_file.txt */

            fprintf(fpw,"%d\t%.4X\t%s\t%s\t%s\n",line,address,label,mnemonic,operand);

            /*checking conditions for various mnemonics*/

            if(strcmp(mnemonic,"BYTE")==0)
            {
                length=0;
                length=strlen(operand);

                length-=3;          /*excluding C'' ,X'' */

                if(operand[0]=='C')
                        address+=length;
                else
                {
                    length=(length/2);
                    address+=length;
                }
            }
            else if(strcmp(mnemonic,"WORD")==0)
            {
                address+=3;
            }
            else if(strcmp(mnemonic,"RESERW")==0)
            {
                x=atoi(operand);    /*converting character into integer */
                address+=(x*3);     /*1 WORD = 3 BYTES */
            }
            else if(strcmp(mnemonic,"RESERB")==0)
            {
                x=atoi(operand);    /*change RESERB's string mnemonic into integer --> x */
                address+=x;
            }
            else
                address+=3;
        }
        else
        {
            fprintf(fpw,"\n");
        }
    }

    fclose(fpr);
    fclose(fpw);

    /*Creating Symtab*/

    fpr=fopen("addressed_file.txt","r");
    fpw=fopen("symtab.txt","w");

    fscanf(fpr,"%d%s%s%s",&line,&program_name,&mnemonic,&operand);

    while(strcmp(mnemonic,"END")!=0)
    {
        fscanf(fpr,"%d%X%s%s%s",&line,&address,&label,&mnemonic,&operand);

        if(line==2)
            first_address=address;     /*Will be used during object file creation */

        if(strcmp(label,"--")!=0)
            fprintf(fpw,"%s  %X\n",label,address);
    }

    last_address=address;      /*Will be used during object file creation */

    fclose(fpr);
    fclose(fpw);

    return 0;
}
