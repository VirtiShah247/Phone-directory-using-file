#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node
{
	char *name;
	char *phone_no;
	char *email_id;
	char *string;
	int status;
	struct node *next;
	struct node *prev;
}*head=NULL,*phone,*p,*ptr;
//int p_no;
int p_status,count;
int choice,length;
char search[50];
char modify_name[50],modify_no[15],modify_email[50];
char fname[50],lname[50],email[50],name[100],p_no[15];

void read_file()
{
	count=0;
	FILE *fp;
	fp=fopen("phone_directory.txt","r");
	char str[100];
	struct node *last;
	last=head=NULL;
	while(fgets(str,sizeof(str),fp))
	{
		count++;
		p=(struct node*)malloc(sizeof(struct node));
		p->string=strdup(str);
		p->next=NULL;
		if(head==NULL)
		{
			head=p;
		}
		else
		{
			struct node *last;
			last=head;
			while(last->next!=NULL)
			{
				last=last->next;
			}
			p->prev=last;
			last->next=p;
			last=p;
				
		}	
	}
	phone=last;	
	fclose(fp);
}

int cond_name()
{
	int found=0;
	struct node *temp;
	temp=head;
	while(temp!=NULL)
	{
		if(strstr(temp->string,name) && strstr(temp->string,"\n"))
		{
			found=1;
			return 1;
		}
		temp=temp->next;
	}
	if(found==0)
	{
		return 0;
	}
	
}
int cond_phone_no()
{
	int len;
	len=strlen(p_no);
	if(len==10)
	{
		
		return 0;
	}
	else
	{
		return 1;
	}
}
int cond_email()
{
	int found=0;
	struct node *temp;
	temp=head;
	while(temp!=NULL)
	{
		if(strstr(temp->string,email) && strstr(temp->string,"\n"))
		{
			found=1;
			return 1;
		}
		temp=temp->next;
	}
	if(found==0)
	{
		return 0;
	}
}

void sorted_file()
{
	struct node *i,*j;
	struct node *temp;
	temp=head;
	int no;
	char str[300];
	if(head == NULL)
	{
		printf("DATA NOT FOUND.\n");
	}
	else
	{
		for(i=temp;i->next!=NULL;i = i->next)
		{
			for(j=i->next;j!=NULL;j=j->next)
			{
				no = strcmp(i->string,j->string);
				if(no>0)
				{
					strcpy(str,i->string);
					//no = i->num;
					strcpy(i->string,j->string);
					//i->num = j->num;
					strcpy(j->string,str);
					//j->num = no;
				}
			}
		}
	}
	FILE *fp;
	fp=fopen("phone_directory.txt","w");
	for(i=temp;i!=NULL;i=i->next)
	{
		fputs(i->string,fp);
		//printf("%s\n",i->string);
	}
	fclose(fp);
}

int add()
{
	int i=0;
	p_status=1;
	
	int j=0;
	printf("\n");
	while(j<=60)
	{
		printf("-");
		usleep(5000);
		j++;
	}
	printf("\n");
    printf("                         ADD CONTACT                       ");
    j=0;
	printf("\n");
	while(j<=60)
	{
		printf("-");
		usleep(5000);
		j++;
	}
	printf("\n");
	
	//read_file();
	
	fflush(stdin);
	printf("Enter phone details\n");
	printf("First name: ");
	gets(fname);
	fname[0]=toupper(fname[0]);
	printf("Last name: ");
	gets(lname);
	lname[1]=toupper(lname[1]);
	strcpy(name,fname);
	//strcat(name,"");
	strcat(name,lname);
	i=cond_name();
	while(i==1)
	{
		printf("INVALID NAME!!\nPLEASE REENTER\n\n");
		printf("First name: ");
		gets(fname);
		fname[0]=toupper(fname[0]);
		printf("Last name: ");
		gets(lname);
		lname[0]=toupper(lname[0]);
		strcpy(name,fname);
		//strcat(name,"");
		strcat(name,lname);
		i=cond_name();
		
	}
	printf("Contact no: ");
	//scanf("%d",&p_no);
	gets(p_no);
	while(cond_phone_no())
	{
		printf("INVALID PHONE NO!!\nPLEASE REENTER\n\n");
		printf("Contact no: ");
		gets(p_no);
	}
	fflush(stdin);
	printf("Email id: ");
	gets(email);
	email[0]=tolower(email[0]);
	while(cond_email())
	{
		printf("INVALID EMAIL ID!!\nPLEASE REENTER\n\n");
		printf("Email id: ");
		gets(email);
		email[0]=tolower(email[0]);
	}
	
	phone=(struct node*)malloc(sizeof(struct node));
	fflush(stdin);
	phone->name=strdup(name);
	//phone->last_name=strdup(lname);
	//phone->phone_no=p_no;
	phone->phone_no=strdup(p_no);
	phone->email_id=strdup(email);
	phone->status=p_status;
	phone->prev=head;
	phone->next=NULL;
	FILE *fp;
	fp=fopen("phone_directory.txt","a");
	//fseek(fp,0,SEEK_END);
	//printf("phone->name %s",phone->name);
	fprintf(fp,"N:%s C:%s E:%s S:%d\n",phone->name,phone->phone_no,phone->email_id,phone->status);
	fclose(fp);
	read_file();
	sorted_file();
	printf("PHONE DETAILS ADDED SUCCESSFULLY!!!\n");	
}
int search_contact()
{
	read_file();
	int found=0;
	struct node *temp;
	temp=head;
	if(temp==NULL)
	{
		printf("Empty directory!!!");
	}
	else
	{
		while(temp!=NULL)
		{
			if(strstr(temp->string,search) && strstr(temp->string,"1\n"))
			{
				printf("%s\n",temp->string);
				found=1;
			}
			temp=temp->next;	
		}
	}
	if(found==0)
	{
		printf("NOT FOUND\n");
		return 0;	
	}
}

void edit()
{
	int found=0,i,len,j;
	char str[15];
	read_file();
	
	FILE *fp;
	fp=fopen("phone_directory.txt","w");
	struct node *temp;
	temp=head;
	if(temp==NULL)
	{
		printf("Empty directory!!!");
	}
	else
	{
		while(temp!=NULL)
		{
			if(strstr(temp->string,search) && strstr(temp->string,"1\n"))
			{
				found=1;
				len=strlen(temp->string);
				int i=0;
				while(i<len)
				{
					//printf("1.\n");
					if(choice==1 && temp->string[i]=='N' && temp->string[i+1]==':' )
					{
						fputc('N',fp);
						i++;
						fputc(':',fp);
						i++;
						while(temp->string[i+1]!='C' && temp->string[i+2]!=':')
						{
							i++;
						}
						
						j=0;
						while(j<length)
						{
							fputc(modify_name[j],fp);
							//i++;
							j++;	
						}
						fputc(' ',fp);
						strcpy(search,modify_name);
					}
					else if(choice ==2 && temp->string[i]=='C' && temp->string[i+1]==':')
					{
						//printf("temp->string[i] %c",temp->string[i]);
						fputc('C',fp);
						i++;
						fputc(':',fp);
						i++;
						j=0;
						while(j<10)
						{
							fputc(modify_no[j],fp);
							i++;
							j++;	
						}
						fputc(' ',fp);	
					}
					
					else if(choice==3 && temp->string[i]=='E' && temp->string[i+1]==':' )
					{
						fputc('E',fp);
						i++;
						fputc(':',fp);
						i++;
						while(temp->string[i+1]!='S' && temp->string[i+2]!=':')
						{
							i++;
						}
						
						j=0;
						while(j<length)
						{
							fputc(modify_email[j],fp);
							//i++;
							j++;	
						}
						fputc(' ',fp);
					}
					else
					{
						fputc(temp->string[i],fp);
					}
					i++;
						
				}
			}
			else
			{
				fputs(temp->string,fp);
			}
			temp=temp->next;
		}
			
		
	}
	if(found==1)
	{
		printf("PHONE DETAILS EDITED SUCCESSFULLY!!!\n");	
	}
	fclose(fp);
}
void delete_contact()
{
	int found=0;
	char str[50],chr;
	int j=0;
	printf("\n");
	while(j<=60)
	{
		printf("-");
		usleep(5000);
		j++;
	}
	printf("\n");
    printf("                         DELETE CONTACT                       ");
    j=0;
	printf("\n");
	while(j<=60)
	{
		printf("-");
		usleep(5000);
		j++;
	}
	printf("\n");
	read_file();
	
	FILE *fp;
	fp=fopen("phone_directory.txt","w");
	struct node *temp;
	temp=head;
	if(temp==NULL)
	{
		printf("Empty directory!!!");
	}
	else
	{
		fflush(stdin);
		printf("Enter contact name to be deleted: ");
		gets(str);
		while(temp!=NULL)
		{
			//printf("1.\n");
			fputs(temp->string,fp);
			//printf("2.\n");
			if(strstr(temp->string,str) && strstr(temp->string,"1\n"))
			{
				//printf("temp->string %s\n str %s \n",temp->string,str);
				fseek(fp,-3,SEEK_CUR);
				chr=fgetc(fp);
				fputc('0',fp);
				fputc('\n',fp);
				found=1;
			}
			temp=temp->next;
		}
	}
	fclose(fp);
    if(found==1)
    {
    	printf("\nPHONE DETAILS IS DELETED SUCCESSFULLY!!!\n");
	}
	else
	{
		printf("\nTRAIN NOT FOUND!!!\n");
	}
	
}

int display()
{
	
	int j=0;
	printf("\n");
	while(j<=70)
	{
		printf("-");
		usleep(5000);
		j++;
	}
	printf("\n");
    printf("                         DISPLAY CONTACT LIST                       ");
    j=0;
	printf("\n");
	while(j<=70)
	{
		printf("-");
		usleep(5000);
		j++;
	}
	printf("\n");
	read_file();
	//head=NULL;
	struct node *p;
	p=head;
	if(p==NULL)
	{
		printf("Empty directory!!!");
	}
	else
	{
		while(p!=NULL)
		{
			if(strstr(p->string,"1\n"))
			{
				printf("%s\n",p->string);
			}
			p=p->next;
		}
	}
}
void main()
{
	int ch,ans;
	do
	{
		system("CLS");
		int j=0;
		printf("\n");
		while(j<=60)
		{
			printf("-");
			usleep(5000);
			j++;
		}
		printf("\n");
	    printf("                         PHONE DIRECTORY                       ");
	    j=0;
		printf("\n");
		while(j<=60)
		{
			printf("-");
			usleep(5000);
			j++;
		}
		printf("\n");
		printf("\n1.Add phone details\n2.Search contact name\n3.Edit contact details\n4.Delete contact\n5.Display\n6.Exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				system("CLS");
				add();
				printf("press any key to continue!!!!\n");
				getch();
				break;
			case 2:
				system("CLS");
				do
				{
					
					int j=0;
					printf("\n");
					while(j<=60)
					{
						printf("-");
						usleep(5000);
						j++;
					}
					printf("\n");
				    printf("                         SEARCH CONTACT                       ");
				    j=0;
					printf("\n");
					while(j<=60)
					{
						printf("-");
						usleep(5000);
						j++;
					}
					printf("\n");
					printf("1.Name\n2.Contact No\n3.Email\n4.Exit");
					scanf("%d",&choice);
					fflush(stdin);
					switch(choice)
					{
						case 1:
							fflush(stdin);
							printf("Enter the Name to be searched: ");
							gets(search);
							search_contact();
							
							break;
						case 2:
							printf("Enter the Contact No to be searched: ");
							gets(search);
							search_contact();
							break;
						case 3:
							printf("Enter the Email to be modified: ");
							gets(search);
							search_contact();
						case 4:
							break;
						default:
							printf("Invalid Input!!");
							break;
					}	
				}while(choice!=4);
				printf("press any key to continue!!!!\n");
				getch();
				break;
			case 3:
				//edit();
				system("CLS");
				fflush(stdin);
				printf("Enter the Name to be searched: ");
				gets(search);
				ans=search_contact();
				/*if(ans==0)
				{
					//printf("Not found");
					//printf("press any key to continue!!!!\n");
					//getch();
					break;
				}*/
				do
				{
					int k=0;
					printf("\n");
					while(k<=60)
					{
						printf("-");
						usleep(5000);
						k++;
					}
					printf("\n");
				    printf("                         EDIT CONTACT                       ");
				    k=0;
					printf("\n");
					while(k<=60)
					{
						printf("-");
						usleep(5000);
						k++;
					}
					printf("\n");
					if(choice==1)
					{
						strcpy(search,modify_name);
					}
					printf("1.Name\n2.Contact No\n3.Email\n4.Exit");
					scanf("%d",&choice);
					fflush(stdin);
					switch(choice)
					{
						case 1:
							/*fflush(stdin);
							printf("Enter the Name to be searched: ");
							gets(search);*/
							printf("Enter the Name to be modified: ");
							gets(modify_name);
							length=strlen(modify_name);
							edit();
							break;
						case 2:
							/*fflush(stdin);
							printf("Enter the Name to be searched: ");
							gets(search);*/
							printf("Enter the Contact No to be modified: ");
							gets(modify_no);
							edit();
							break;
						case 3:
							/*fflush(stdin);
							printf("Enter the Name to be searched: ");
							gets(search);*/
							printf("Enter the Email to be modified: ");
							gets(modify_email);
							length=strlen(modify_email);
							edit();
						case 4:
							break;
						default:
							printf("Invalid Input!!");
							break;
					}
				}while(choice!=4);
					
				
				printf("press any key to continue!!!!\n");
				getch();
				break;
			case 4:
				system("CLS");
				delete_contact();
				printf("press any key to continue!!!!\n");
				getch();
				break;
			case 5:
				system("CLS");
				display();
				printf("press any key to continue!!!!\n");
				getch();
				break;
			case 6:
				exit(0);
			default:
				printf("Invalid choice");
				break;	
		}
	}while(ch!=7);
	
}
