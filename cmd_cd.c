#include "headerFiles.h"
void cmd_cd(){
	char tempdir[10000];
	strcpy(tempdir,currdir);
	char* tok;
	tok = strtok(s," ");
	if(strcmp(tok,"cd")==0)
	{
		tok = strtok(0," ");
		if(tok==NULL){
			chdir(homedir);
		}
		else if(strcmp(tok,".")==0){
			chdir(currdir);
		}
		else if(strcmp(tok,"..")==0){
			chdir("..");
		}
		else if(strcmp(tok,"-")==0){
			chdir(prevdir);
		}
		else if(tok[0]=='~')
		{
			char temp[10000];
			strcpy(temp,homedir);
			if(sizeof(tok)>1)
				strcat(temp,&tok[1]);
			if(chdir(temp)!=0) perror(temp);
		}
		else{
			if(chdir(tok)!=0)
			{
				perror(tok);
			}
		}
		stx=1;
	}
	getcwd(name,100*sizeof(char));
	strcpy(currdir,name);
	if(strcmp(currdir,tempdir)!=0)
	{
		strcpy(prevdir,tempdir);
	}
	strcpy(s,s_save);
}