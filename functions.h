void cmd_jobs()
{
	if (strcmp(s, "jobs") == 0)
	{
		int runs=0;
		int i, p;
		char prname[100], c;
		if (idx < 1 || numproc == 0)
			printf("No processes in background\n");
		else
		{
			for (i = 1; i <= idx; i++)
			{
				strcpy(s, "/proc/");
				char temp[50] = {0};
				sprintf(temp, "%d", pidarr[i]);
				strcat(s, temp);
				strcat(s, "/stat");

				FILE *fd;
				if ((fd = fopen(s, "r")) == NULL)
				{
					continue;
				}
				else
				{
					fscanf(fd, "%d %s %c", &p, prname, &c);
					fclose(fd);
					printf("[%d] ", i);
					if (c == 'T')
						printf("Stopped");
					else
						printf("Running");
					printf(" '%s' [%d]\n", pidcmd[i], pidarr[i]);
					runs++;
				}
			}
		}
		if(runs==0) numproc=0;
		stx = 1;
	}
	strcpy(s, s_save);
}

void cmd_bgonly()
{
	char *ends;
	char *tok = strtok_r(s, " ", &ends);
	if (strcmp(tok, "bg") == 0)
	{
		tok = strtok_r(NULL, " ", &ends);
		int i = atoi(tok);
		fflush(stdout);
		kill(pidarr[i], SIGCONT);
		stx = 1;
		strcpy(s, s_save);
	}
	strcpy(s, s_save);
}

void cmd_env()
{
	char *ends;
	char *tok = strtok_r(s, " ", &ends);
	if (strcmp(tok, "setenv") == 0)
	{
		int numargs=0;
		char arg1[20],arg2[20];
		while(tok!=NULL)
		{
			if(numargs==1) strcpy(arg1,tok);
			if(numargs==2) strcpy(arg2,tok);
			numargs++;
			tok = strtok_r(NULL, " ", &ends);
		}
		if(numargs<1 || numargs>2)
		{
			printf("Error: Only either one or two args allowed.");
			fflush(stdout);
			strcpy(s, s_save);
			stx=1;
			return;
		}
		if(numargs==1) strcpy(arg2," ");
		setenv(arg1,arg2,1);
		stx = 1;
		strcpy(s, s_save);
	}
	else if (strcmp(tok, "unsetenv") == 0)
	{
		int numargs=0;
		char arg1[20];
		while(tok!=NULL)
		{
			if(numargs==1) strcpy(arg1,tok);
			numargs++;
			tok = strtok_r(NULL, " ", &ends);
		}
		if(numargs!=1)
		{
			printf("Error: One argument required.");
			fflush(stdout);
			strcpy(s, s_save);
			stx=1;
			return;
		}
		unsetenv(arg1);
		stx = 1;
		strcpy(s, s_save);

	}
	strcpy(s, s_save);
}

void cmd_overkill()
{
	if (strcmp(s, "overkill") == 0)
	{
		for (int i = 1; i <= idx; i++)
		{
			kill(pidarr[i], 9);
		}
		stx = 1;
	}
	strcpy(s, s_save);
}

void cmd_kjob()
{
	char *ends;
	char *tok = strtok_r(s, " ", &ends);
	if (strcmp(tok, "kjob") == 0)
	{
		tok = strtok_r(NULL, " ", &ends);
		int jid = atoi(tok);
		tok = strtok_r(NULL, " ", &ends);
		int sig = atoi(tok);
		if (kill(pidarr[jid], sig) < 0)
			perror("kjob");
		stx = 1;
		strcpy(s, s_save);
	}
	strcpy(s, s_save);
}

void cmd_fgonly()
{
	char *ends;
	char *tok = strtok_r(s, " ", &ends);
	if (strcmp(tok, "fg") == 0)
	{
		tok = strtok_r(NULL, " ", &ends);
		int i = atoi(tok);
		char s[50] = "/proc/";
		char temp[50] = {0};
		sprintf(temp, "%d", pidarr[i]);
		strcat(s, temp);
		strcat(s, "/stat");
		FILE *fd;
		if ((fd = fopen(s, "r")) == NULL)
		{
			printf("Invalid process\n");
		}
		else
		{
			kill(pidarr[i], SIGCONT);
			waitpid(-1, NULL, WUNTRACED);
		}
		stx = 1;
		strcpy(s, s_save);
	}

	strcpy(s, s_save);
}

void functions()
{
	if(strstr(s,"exit")!=NULL) return;
	stx=0;
	cmd_cd();if(stx==1) return;
	cmd_bg();if(stx==1) return;
	cmd_watch();if(stx==1) return;
	cmd_env();if(stx==1) return;
	cmd_pinfo();if(stx==1) return;
	cmd_pwd();if(stx==1) return;
	cmd_echo();if(stx==1) return;
	cmd_ls();if(stx==1) return;
	cmd_jobs();if(stx==1) return;
	cmd_overkill();if(stx==1) return;
	cmd_kjob();if(stx==1) return;
	cmd_fgonly();if(stx==1) return;
	cmd_bgonly();if(stx==1) return;
	cmd_fg();if(stx==1) return;
}