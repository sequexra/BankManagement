#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Bank_Account{
	char no[10];
	char name[20];
	char balance[15];
}acc;
int main()
{
	float minbal = 5000;
	long int pos1, pos2, pos;
	FILE *fp;
	char *ano,*amt;
	char choice;
	int type,flag=0;
	float bal;
	do{
		system("clear");
		fflush(stdin);
		printf("1. Add new Account Holder\n");
		printf("2. Display\n");
		printf("3. Deposit or Withdraw\n");
		printf("4. No. of Account Honders whose Balance is less than MINIMUM BALANCE\n");
		printf("5. Exit\n");
		choice=getchar();
		switch(choice)
		{
			case '1':
			fflush(stdin);
			fp=fopen("acc.dat","a");
			printf("\nEnter Account Number: ");
			gets(acc.no);
			printf("\nEnter Account Holder's Name: ");
			gets(acc.name);
			printf("\nEnter Initial Deposit: ");
			gets(acc.balance);
			fseek(fp,0,2);
			fwrite(&acc,sizeof(acc),1,fp);
			fclose(fp);
			break;
			case '2':
			fp=open("acc.dat","r");
			if(fp==NULL)
				printf("\nFile is Empty");
			else
			{
				printf("\nA/c Number\tName\tBalance\n");
				while(fread(&acc,sizeof(acc),1,fp)==1)
					printf("%-10s\t\t%-20s\t%s\n",acc.no,acc.name,acc.balance);
				fclose(fp);	
			}
			break;
			case '3':
			fflush(stdin);
			flag=0;
			fp=fopen("acc.dat","r+");
			printf("\nEnter Account Number: ");
			gets(ano);
			for(pos1=ftell(fp);fread(&acc,sizeof(acc),1,fp)==1;pos1=ftell(fp))
			{
				if(strcmp(acc.no,ano)==0)
				{
					printf("\nEnter the Type 1 for deposit & 2 for withdrawal: ");
					scanf("%d",&type);
					printf("\nCurrent Balance: %s",acc.balance);
					printf("\nEnter Amount:");
					fflush(stdin);
					gets(amt);
					if(type==1)
						bal = atof(acc.balance)+atof(amt);
					else
					{
						bal = atof(acc.balance)+atof(amt);
						if(bal<0)
						{
							printf("\n.₹ %s not available in your A/c\n ",amt);
							flag=2;
							break;
						}
					}
					if(flag==1)
					{
						pos2 = ftell(fp);
						pos = pos2-pos1;
						fseek(fp,-pos,1);
						sprintf(amt,"%.2f",bal);
						strcpy(acc.balance,amt);
						fwrite(&acc,sizeof(acc),1,fp);
					}
					else if(flag==0)
						printf("\n A/c Number does not exist!");
				}
			}
			fclose(fp);
			break;
		case '4':
		fp=fopen("acc.dat","r");
		flag=0;
		while(fread(&acc,sizeof(acc),1,fp)==1)
		{
			bal = atof(acc.balance);
			if(bal<minbal)
				flag++;
		}
		printf("\nNo. of A/c Holders whose balance Less the MINIMUM BALANCE: %d",flag);
		fclose(fp);
		break;
		case '5':
		fclose(fp);
		exit(0);
		}
		printf("\nPress any key to continue....");
		getch();
	}while(choice!='5');
}
