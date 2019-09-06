
void cmd_pwd(){
	char* tok = strtok(s," ");
	if(strcmp(tok,"pwd")==0)
	{
		char* name = (char *)malloc(100*sizeof(char));
		getcwd(name,100*sizeof(char));
		printf("%s\n",name);
		stx=1;
	}
	strcpy(s,s_save);
}