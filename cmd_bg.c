void addbg(int pidx)
{
	idx++;
	numproc++;
	pidarr[idx]=pidx;
	pidctr[idx]=idx;

	strcpy(pidcmd[idx],s_save);
	// printf("%d %d %s\n", idx,pidarr[idx],pidcmd[idx]);

}

void cmd_bg()
{
	if(strstr(s,"&"))
	{
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
		int final_in = dup(0),final_out = dup(1);
		if (pid == -1)
		{
			printf("can't fork, error occured\n"); 
			exit(EXIT_FAILURE); 
		}
		else if(pid > 0) {
			addbg(pid);
			waitpid(-1, &status, WNOHANG); 
			dup2(final_in,0);
			dup2(final_in,1);
			stx=1;
		} 
		else
		{
			stx=1;
			printf("%d.[%d] - [%s]\n",idx+1,getpid(),s_save);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			int x = open("/dev/null", O_RDWR);
			dup(x);
			dup(x);
			if(execvp(args[0],args)<0) {
				dup2(final_in,0);
				dup2(final_in,1);
				perror(args[0]);
			}
			exit(1);
		}
	}
	strcpy(s,s_save);
}