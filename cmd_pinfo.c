void cmd_pinfo()
{
	char * tok = strtok(s," ");
	if(strcmp(tok,"pinfo")==0)
	{
		char location[1000] = "/proc/";
		tok = strtok(0," ");
		if(tok==NULL || tok=="")
		{
			strcat(location,"self/stat");
		}
		else
		{
			char * temp = strtok(0," ");
			if(temp != NULL)
			{
				printf("Single argument expected\n");
				strcpy(s,s_save);
				stx=1;return;
			}
			else{
				strcat(location,tok);
				strcat(location,"/stat");

			}
		}

		int fileIn = open(location, O_RDONLY);
		if (fileIn<0){ 
			printf("Invalid pid\n");
			strcpy(s,s_save);
			stx=1;return;
		}
		char *data = (char *) calloc(buff_size,sizeof(char));
		int temp = read(fileIn, data, buff_size);
		tok = strtok(data," ");
		char *args[100]={};int i=0;
		while(tok!=NULL)
		{
			args[i++]=tok;
			tok = strtok(0," ");
		}
		printf("pid -- %s\n",args[0]);
		printf("Process Status -- %s\n",args[2]);
		printf("memory -- %s\n",args[22]);
		strcpy(location,"/proc/");
		strcat(location,args[0]);
		strcat(location,"/exe");
		strcpy(data,"");
		ssize_t len = readlink(location, data, buff_size);
		if (len != -1) data[len] = '\0';
		truncatedir(data);
		printf("Executable Path -- %s\n",data);
		stx=1;
	}
	strcpy(s,s_save);
}

