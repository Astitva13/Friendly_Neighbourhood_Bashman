#include "headerFiles.h"
#include "cmd_bg.c"
#include "cmd_cd.c"
#include "cmd_echo.c"
#include "cmd_fg.c"
#include "cmd_ls.c"
#include "cmd_pinfo.c"
#include "cmd_pwd.c"
#include "cmd_watch.c"

int idx=-1;
int counter=0;
int pidarr[10000];
int pidctr[10000];
char pidcmd[10000][100];
char s[10000];
char s_save[10000];
char inputstring[10000];
char homedir[10000];
char currdir[10000];
char prevdir[10000];
char* name;
int stx=0;
int fl_a=0,fl_l=0,fl_dir=0,ctdir=0;
struct stat fileStat;

void init(){
	name = (char *)malloc(100*sizeof(char));
	/*
		strcpy(homedir,"/home/");
		strcat(homedir,name);
	*/
	getcwd(name,100*sizeof(char));
	/**/
	strcpy(homedir,name);
	strcpy(currdir,name);
	idx=-1;
	counter=0;
	stx=0;
	fl_a=0,fl_l=0,fl_dir=0,ctdir=0;
	/**/
}

void truncatedir(char * name)
{
	if(strstr(name,homedir)!=NULL)
	{
		char * match;
		int len = strlen(homedir);
		while(match = strstr(name,homedir))
		{
			*match = '\0';
			strcat(name,match+len);
		}
		char temp[1000] ="~";
		strcat(temp,name);
		strcpy(name,temp); 
	}
}

void printdetails(){
	name = getlogin();
	printf("<\x1b[31m%s\x1b[0m@", name);
	gethostname(name,100*sizeof(char));
	printf("\x1b[33m%s\x1b[0m:", name);
	// getcwd(name,100*sizeof(char));
	strcpy(name,currdir);
	truncatedir(name);
	printf("\x1b[32m%s\x1b[0m> ", name);
}




void checkpid()
{
	for (int i = 0; i <= idx; ++i)
	{
		if(pidarr[i]!=-1)
		{
			char integer[100];
			snprintf( integer, 10000, "%d",pidarr[i] );
			char location[1000] = "/proc/";
			strcat(location,integer);
			strcat(location,"/stat");
			int fileIn = open(location, O_RDONLY);
			if(fileIn<0)
			{
				pidarr[i]=-1;
				printf("[%d]\t-done\t\t%s\n",pidctr[i],pidcmd[i]);
			}
			// else printf("opened\n");
		}
	}
}



void functions()
{
	stx=0;
	cmd_cd();if(stx==1) return;
	cmd_bg();if(stx==1) return;
	cmd_watch();if(stx==1) return;
	cmd_pinfo();if(stx==1) return;
	cmd_pwd();if(stx==1) return;
	cmd_echo();if(stx==1) return;
	cmd_ls();if(stx==1) return;
	cmd_fg();if(stx==1) return;
}

void trim()
{
	char str[10000];
	strcpy(str,s);
	int n = strlen(str); 
	int i = 0, j = -1; 
	int spaceFound = 0; 
	while (++j < n && str[j] == ' '); 
	while (j < n) 
	{ 
		if (str[j] != ' ') 
		{ 
			if ((str[j] == '.' || str[j] == ',' || 
				str[j] == '?') && i - 1 >= 0 && 
				str[i - 1] == ' ') 
				str[i - 1] = str[j++]; 
			else
				str[i++] = str[j++]; 
			spaceFound = 0; 
		} 
		else if (str[j++] == ' ') 
		{ 
			if (spaceFound==0) 
			{ 
				str[i++] = ' '; 
				spaceFound = 1; 
			} 
		} 
	} 
	char temp_str[10000]="";
	if (i <= 1)
		strncpy(temp_str,str,i+1);
	else
		strncpy(temp_str,str,i);
	strcpy(s,temp_str);
	strcpy(s_save,temp_str);
}

void wrapper()
{
	char str[10000];
	strcpy(str,s);
	char *end_str;
	char *token = strtok_r(str, ";", &end_str);
	int i=0;
	while (token != NULL)
	{
		if(!i++==0){printf("\n");}
		strcpy(s,token);
		if(!strstr(s,"cd ")) trim();
		functions();
		token = strtok_r(NULL, ";", &end_str);
	}
}



int main()
{
	memset(s,0,10000*sizeof(char));
	memset(pidarr,-1,10000);
	memset(inputstring,0,10000*sizeof(char));
	init();
	while(strcmp(s,"exit")!=0)
	{
		printdetails();
		fgets(s,10000,stdin);
		strtok(s,"\n");
		strcpy(inputstring,s);
		wrapper();
		checkpid();
	}
}