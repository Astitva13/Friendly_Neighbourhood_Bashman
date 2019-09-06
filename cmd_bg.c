void addbg(int pidx)
{
	pidarr[idx]=pidx;
	pidctr[idx]=counter;
	strcpy(pidcmd[idx],s_save);
}

void cmd_bg()
{
	if(strstr(s,"&"))
	{
		counter++;
		strtok(s,"&");
		char * tok = strtok(s," ");
		char *args[100]={}; 
		int i=0;
		while(tok!=NULL)
		{
			args[i++]=tok;
			tok = strtok(0," ");
		}
		int status,st=0; 
		pid_t pid = fork(),sid; 
		if (pid == -1)
		{
			printf("can't fork, error occured\n"); 
			exit(EXIT_FAILURE); 
		}
		else if(pid > 0) { 
			stx=1;
			idx++;
			addbg(pid);
			return;
		} 
		else
		{
			stx=1;
			printf("[%d] %d\n",counter,getpid());
			// fflush(stdout);
			// execvp(args[0],args);
			if(execvp(args[0],args)<0) perror(args[0]);
			// exit(0);
		}
	}
	strcpy(s,s_save);
}