void call(int id,char filename[])
{
	if(stat(filename,&fileStat) < 0)    
		return;
	if(fl_a==0 && id==0)
		if(filename[0]=='.') return;
	if(fl_l==1){
		printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
		printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
		printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
		printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
		printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
		printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
		printf(" %d",fileStat.st_nlink);
		printf(" %s",getpwuid(fileStat.st_uid)->pw_name);
		printf(" %s",getgrgid(fileStat.st_gid)->gr_name);
		printf(" %d",fileStat.st_size);
		char time[1025]="";
		strftime (time, 1024,"%b %d %R",localtime (&fileStat.st_mtime));
		printf(" %s",time);
	}
	printf(" %s\n",filename);
}


void cmd_ls()
{
	if(strstr(s,"&")==NULL)
	{
		char * tok = strtok(s," ");
		if(strcmp(tok,"ls")==0)
		{
			char dirarr[100][1000];
			tok = strtok(0," ");
			ctdir = 0;fl_l = 0;fl_a = 0;
			while(tok!=NULL)
			{
				if(tok[0]=='-')
				{
					if(strstr(tok,"a")) fl_a=1;
					if(strstr(tok,"l")) fl_l=1;
				}
				else
				{
					strcpy(dirarr[ctdir++],tok);
				}
				tok = strtok(0," ");
			}
			// while(ctdir--)
			// 	printf("%s\n", dirarr[ctdir]);
			char filename[1024]="";
			DIR *d;
			struct dirent *dir;
			if(ctdir==0)
			{
				d = opendir(currdir);
				struct dirent *dir;
				if (d)
				{
					while ((dir = readdir(d)) != NULL)
					{
						strcpy(filename,dir->d_name);
						call(0,filename);
					}
				}
			}
			else
			{
				for (int i = 0; i < ctdir; ++i)
				{
					name = dirarr[i];
					if(stat(name,&fileStat)<0){
						perror(name);
						continue;
					}
					if(S_ISDIR(fileStat.st_mode))
					{
						char temp[10000]={},tempcurr[10000]={},tempprev[10000]={};
						strcpy(tempcurr,currdir);
						strcpy(tempprev,prevdir);
						strcpy(temp,"cd ");
						strcat(temp,name);
						strcpy(s,temp);
						strcpy(temp,name);
						cmd_cd();
						if(i!=0) printf("\n");
						if(strstr(currdir,tempcurr))
							printf("./%s:\n",temp);
						else
							printf("%s:\n",currdir );
						stx=0;
						d = opendir(currdir);
						struct dirent *dir;
						if (d)
						{
							while ((dir = readdir(d)) != NULL)
							{
								strcpy(filename,dir->d_name);
								call(0,filename);
							}
						}
						// call(d);
						strcpy(temp,"cd ");
						strcat(temp,tempcurr);
						strcpy(s,temp);
						cmd_cd();
						strcpy(prevdir,tempprev);
					}
					else
					{
						if(i!=0) printf("\n");
						strcpy(filename,name);
						call(1,filename);
					}
				}
			}

			stx=1;
		}
		strcpy(s,s_save);
	}
}