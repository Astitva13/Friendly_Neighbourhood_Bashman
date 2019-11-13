#include "headerFiles.h"
#include "trim.h"
#include "cmd_bg.c"
#include "cmd_cd.c"
#include "cmd_echo.c"
#include "cmd_fg.c"
#include "cmd_ls.c"
#include "cmd_pinfo.c"
#include "cmd_pwd.c"
#include "cmd_watch.c"
#include "functions.h"
#include "redirection.h"
#include "pipe_handle.c"

int idx=0;
int numproc=0;
pid_t currfg;
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
int h[10];
int fl_a,fl_l,fl_dir,ctdir;
struct stat fileStat;

void init(){
	name = (char *)malloc(100*sizeof(char));
	getcwd(name,100*sizeof(char));
	strcpy(homedir,name);
	strcpy(currdir,name);
	stx=0;
	fl_a=0,fl_l=0,fl_dir=0,ctdir=0;
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
	strcpy(name,currdir);
	truncatedir(name);
	printf("\x1b[32m%s\x1b[0m> ", name);
}


void checkpid()
{
	pid_t pid;
	int status;
	char *exit=(char *)malloc(100000);
	char *exit_status=(char *)malloc(100000);
	pid=waitpid(0,&status,WNOHANG);
	char string[100]={0}; 
	for(int i=1;i<=idx;i++)
	{
		if(pid==pidarr[i])
			strcpy(string,pidcmd[i]);
	}
	sprintf(exit,"\n'%s' with pid %d exited ",string,pid);
	if(WIFEXITED(status))
	{
		int r=WEXITSTATUS(status);
		if(r)
			sprintf(exit_status,"abnormally\n");
		else
			sprintf(exit_status,"normally\n");
	}
	if(pid>0)
	{
		write(2,exit,strlen(exit));
		write(2,exit_status,strlen(exit_status));
		numproc--;
	}
	// printf("\n");
	/*for (int i = 1; i <= idx; ++i)
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
		}
	}*/
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
		trim();
		handling();
		// redirection();
		token = strtok_r(NULL, ";", &end_str);
	}
}

void addHistory()
{
	if(strcmp(s,"")==0) return;
	strcpy(s,homedir);
	strcat(s,"/.history");
	int fd = open(s, O_WRONLY | O_CREAT | O_APPEND, 0644);
	int stdoutx = dup(1);
	dup2(fd,1);
	printf("%s\n",inputstring);
	dup2(stdoutx,1);
}

void clearbg()
{
	printf("\n");
	strcpy(s,homedir);
	strcat(s,"/bgproccess");
	int fd = open(s, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd < 0)
	{
		perror("fd");
		return;
	}
	int stdoutx = dup(1);
	dup2(fd,1);
	dup2(stdoutx,1);	
}

void sigintHandler (int sig_nameindex)
{
	signal(SIGINT, sigintHandler);
	fflush(stdout);
}

void sigtstpHandler(int sig_nameindex) 
{ 
	if(currfg!=0) 
	{
		kill(currfg,SIGTTIN);
		kill(currfg,SIGTSTP);
		printf("\nStopped: %d\t%s\n",currfg,s);
		addbg(currfg);
		currfg=0;
	}
	signal(SIGTSTP, sigtstpHandler);
	fflush(stdout);
}


int main()
{
	signal(SIGINT, sigintHandler);
	signal(SIGTSTP, sigtstpHandler);
	memset(s,0,10000*sizeof(char));
	memset(inputstring,0,10000*sizeof(char));
	init();
	int pid,status;
	pid_t initpid = getpid();
	while(strcmp(s,"quit")!=0)
	{
		if(initpid != getpid()) exit(0);
		currfg=0;
		printdetails();
		fgets(s,10000,stdin);
		strtok(s,"\n");
		strcpy(inputstring,s);
		int d = strcmp(s,"\n");
		if(strcmp(s,"quit")==0) return 0;
		if(d!=0) wrapper();
		addHistory();
		checkpid();
	}
}