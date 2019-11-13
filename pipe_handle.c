void handling()
{
	trim_r(s);
	char s_handle[10000];
	strcpy(s_handle, s);
	char *tempstr;
	char *tokhandle = strtok_r(s_handle, "|", &tempstr);
	int pipes[2];
	int number = 0;
	while (tokhandle != NULL)
	{
		trim_r(tokhandle);
		if (strcmp(tokhandle, "") != 0)
		{
			number++;
		}
		tokhandle = strtok_r(NULL, "|", &tempstr);
	}
	strcpy(s_handle, s);
	tokhandle = strtok_r(s_handle, "|", &tempstr);
	int i = 0, out_final = dup(1), in_final = dup(0);
	while (tokhandle != NULL)
	{
		if (i != 0)
		{
			// printf("Not first: %s\n", tokhandle);
			fflush(stdout);
			close(pipes[1]);
			if (dup2(pipes[0], 0) == -1)
				perror("Pipe Error (Read)");
			close(pipes[0]);
		}

		if (i != number - 1)
		{
			// printf("Not last: %s\n", tokhandle);
			fflush(stdout);
			pipe(pipes);
			if (dup2(pipes[1], 1) == -1)
				perror("Pipe Error (Write)");
		}
		trim_r(tokhandle);
		strcpy(s, tokhandle);
		redirection();
		fflush(stdout);
		dup2(in_final, 0);
		dup2(out_final, 1);
		i++;
		tokhandle = strtok_r(NULL, "|", &tempstr);
	}
}