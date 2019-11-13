
void cmd_fg()
{
	char * tok = strtok(s," ");
	char *args[100]={}; 
	int i=0;
	while(tok!=NULL)
	{
		args[i++]=tok;
		tok = strtok(0," ");
	}
	int status,st=0; 
	pid_t pid = fork(); 
	if (pid == -1)
	{
		printf("can't fork, error occured\n"); 
		exit(EXIT_FAILURE); 
	} 
	else if (pid == 0){ 
		if(execvp(args[0],args)<0) printf("%s: command not found\n",args[0]);;
		st=1;
	} 
	else{  
		currfg = pid;
		if (waitpid(-1,&status,WUNTRACED) <= 0 || st==1) perror(args[0]);
	} 
	stx=1;
	strcpy(s,s_save);
}


