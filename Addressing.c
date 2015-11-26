#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fpr=NULL,*fpw=NULL,*fp1=NULL,*fp2=NULL;

int main()
{
    char label[10],mnemonic[10] ,operand[10],program_name[10],sym_label[20][10],sym_address[20][10],opcode[10];
    int address=0,line=0,length,x=0,first_address=0,last_address=0,i=0,j=0,k=0,pos1=0,pos2=0,flag1=0,flag2=0,p1=0,p2=0,l=0,z=0;

    char op_mnemonic[26][10]={"LDAC","STAC","SUBJ","MULT","STRL","DIVD","ADDA","STRCH","DT",
    "JMPEQ","LOADCH","DW","SUBR","FIXR","FIX","JMPLT","COMP","CLR","LOADB","J","DR","COMPR","STREX","LOADT","LOADL","LOADX"};

    char op_opcode[26][10]={"10","1C","58","30","24","34","28","44","F0","40","60","EC",
    "4C","C8","3C","39","38","C4","78","3C","E8","D0","20","84","08","04"};

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
        {
            fprintf(fpw,"%s  %X\n",label,address);
            j++;
            z=j;
        }
    }

    last_address=address;      /*Will be used during object file creation */

    fclose(fpr);
    fclose(fpw);

    /*Extracting data from symtab*/

    fp1=fopen("symtab.txt","r");
    i=0;

    while(j--)
    {
        fscanf(fp1,"%s%s",&sym_label[i],&sym_address[i]);
        i++;
    }

    fclose(fp1);

    /*Generating opcodes*/

    fpr=fopen("addressed_file.txt","r");
    fpw=fopen("intermediate.txt","w");

    fscanf(fpr,"%d%s%s%s",&line,&program_name,&mnemonic,&operand);
    fprintf(fpw,"%d\t\t%s\t%s\t%s\t\t--\n",line,program_name,mnemonic,operand);

    while(strcmp(mnemonic,"END")!=0)
    {
        fscanf(fpr,"%d%X%s%s%s",&line,&address,&label,&mnemonic,&operand);

        if(strcmp(mnemonic,"WORD")==0)
            fprintf(fpw,"%d\t%.4X\t%s\t%s\t%s\t\t%.6X\n",line,address,label,mnemonic,operand,atoi(operand));

        else if(strcmp(mnemonic,"BYTE")==0)
        {
            l=strlen(operand);
            k=0;

            for(i=2;i<l-1;i++)
                opcode[k++]=operand[i];
            opcode[k]='\0';

            if(operand[0]=='C')
                fprintf(fpw,"%d\t%.4X\t%s\t%s\t%s\t\t454F46\n",line,address,label,mnemonic,operand);

            if(operand[0]=='X')
                fprintf(fpw,"%d\t%.4X\t%s\t%s\t%s\t\t%s\n",line,address,label,mnemonic,operand,opcode);
        }

        else if(strcmp(mnemonic,"RESERW")==0 || strcmp(mnemonic,"RESERB")==0 || strcmp(mnemonic,"START")==0 || strcmp(mnemonic,"END")==0)
            fprintf(fpw,"%d\t%.4X\t%s\t%s\t%s\t\t--\n",line,address,label,mnemonic,operand);

        else if(strcmp(mnemonic,"SUBR")==0)
            fprintf(fpw,"%d\t%.4X\t%s\t%s\t%s\t\t4C0000\n",line,address,label,mnemonic,operand);

        else
        {
            pos1=pos2=0;

            for(i=0;i<26;i++)
            {
                if(strcmp(mnemonic,op_mnemonic[i])==0)
                {
                    pos1=i;
                    break;
                }
            }

            for(j=0;j<z;j++)
            {
                if(strcmp(operand,sym_label[j])==0)
                {
                    pos2=j;
                    break;
                }
                if(strcmp(sym_label[j],"BUFFER")==0)
                    z=j;

                if(strcmp(operand,"BUFFER,X")==0)
                {
                    pos2=z;
                    break;
                }
            }

            if(strcmp(operand,"BUFFER,X")==0)
            {
                fprintf(fpw,"%d\t%.4X\t%s\t%s\t%s\t%s%s\n",line,address,label,mnemonic,operand,op_opcode[pos1],sym_address[pos2]);
            }
            else
                fprintf(fpw,"%d\t%.4X\t%s\t%s\t%s\t\t%s%s\n",line,address,label,mnemonic,operand,op_opcode[pos1],sym_address[pos2]);
        }
    }

    fclose(fpr);
    fclose(fpw);

    return 0;
}
