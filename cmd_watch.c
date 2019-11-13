
void cmd_watch()
{
	char * tok = strtok(s," ");
	if(strcmp(s,"nightswatch")==0)
	{
		char *args[100]={}; 
		int i=0;
		while(tok!=NULL)
		{
			args[i++]=tok;
			tok = strtok(0," ");
		}
		args[0]="watch";
		if(strcmp(args[i-1],"dirty")==0)
		{
			args[i-1]="cat /proc/meminfo | grep -i dirty";
			int status,st=0; 
			pid_t pid = fork(); 
			if (pid == -1)
			{
				printf("can't fork, error occured\n"); 
				exit(EXIT_FAILURE); 
			} 
			else if (pid == 0){ 
				execvp(args[0],args); 
				st=1;
			} 
			else{
				if (wait(&status) <= 0 || st==1) {perror(args[0]);}
			} 
		}
		else if(strcmp(args[i-1],"interrupt")==0)
		{
			args[i-1]="cat /proc/interrupts | head -n 1 && cat /proc/interrupts | head -3 | tail -1";
			int status,st=0; 
			pid_t pid = fork(); 
			if (pid == -1)
			{
				printf("can't fork, error occured\n"); 
				exit(EXIT_FAILURE); 
			} 
			else if (pid == 0){ 
				execvp(args[0],args); 
				st=1;
			} 
			else{  
				if (wait(&status) <= 0 || st==1) {perror(args[0]);}
			} 
		}
		else
		{
			printf("Error: Invalid option :'%s'\n",args[i-1]);
			stx=1;
			strcpy(s,s_save);
			return;
		}
	}
	strcpy(s,s_save);
	return;
}
