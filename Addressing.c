#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *fpr=NULL,*fpw=NULL;

int main()
{
    char label[10],mnemonic[10],operand[10],program_name[10],char_address[10],char_lh[10],char_rh[10];
    int address=0,first_address=0,last_address=0,line=0,length,x=0,right_half=0,left_half=0,temp=0,l=0;

    /*Adressing*/

    fpr=fopen("input.txt","r");
    fpw=fopen("addressed_file.txt","w");

    fscanf(fpr,"%s%s%d",&program_name,&mnemonic,&address);  /*Reading data from input.txt*/
    line++;
    fprintf(fpw,"%d\t\t%s\t%s\t%d\n",line,program_name,mnemonic,address);  /*Writing data into addressed_file.txt */

    while(strcmp(mnemonic,"END")!=0)
    {
        if(strcmp(label,".")!=0)        /*For checking comments*/
        {
            fscanf(fpr,"%s%s%s",&label,&mnemonic,&operand);
            line++;

             /*Addressing in hexadecimal format */

                temp=address;
                
                if(address<100)
                {
                    right_half=address;
                    left_half=0;
                }
               else if(address>=100)
               {
                right_half=temp%100;    /*contains right half of the address */
                temp/=100;
                left_half=temp;         /*contains left half of the address */
               }

                itoa(left_half,char_lh,10);    /*converts integer into string */
                itoa(right_half,char_rh,16);    /*converts integer into hexadecimal */
                   
                 l=strlen(char_lh);
                 
                 if(l==1)
                 {
                    char_lh[2]='\0';
                    char_lh[1]=char_lh[0];
                    char_lh[0]='0';
                 }
                strcat(char_lh,char_rh);

                l=strlen(char_lh);

                if(l==3)
                {
                    char_lh[4]='\0';
                    char_lh[3]=char_lh[2];
                    char_lh[2]='0';
                }

                /*printf("\n%s",char_lh);*/



                /*Writing data into addressed_file.txt */

                fprintf(fpw,"%d\t%s\t%s\t%s\t%s\n",line,char_lh,label,mnemonic,operand);



                /*checking conditions for various mnemonics*/

                if(strcmp(mnemonic,"SIZE")==0)
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
                    x=atoi(operand);    /*change RESB's mnemonic into hexadecimal --> x, address+=x; */
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

    return 0;
}
