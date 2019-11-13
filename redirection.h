void redirection()
{
	char s_temp[10000],final_s[10000];
	strcpy(s_temp,s);
	char* endstr;
	char* tok = strtok_r(s,"<>",&endstr);
	strcpy(final_s,tok);
	// int original_in,original_out;
	// original_in = dup(0);
	// original_out = dup(1);

	if(strstr(s_temp,"<")!=NULL && strstr(s_temp,">")!=NULL)
	{

		int flg=0;
		if(strstr(s_temp,"<")<strstr(s_temp,">")) flg=1;
		int in, out;
		tok = strtok_r(NULL,"<>",&endstr);
		trim_r(tok);
		if(flg==1)
		{
			in = open(tok, O_RDONLY);
		}
		else
		{
			if(strstr(s_temp,">>"))
				out = open(tok, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			else
				out = open(tok, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);	
		}
		tok = strtok_r(NULL,"<>",&endstr);
		trim_r(tok);
		if(flg==0)
		{
			in = open(tok, O_RDONLY);
		}
		else
		{
			if(strstr(s_temp,">>"))
				out = open(tok, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			else
				out = open(tok, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);	
		}
		if(in<0 || out<0)
		{
			perror("Error '<>'");
			return;
		}
		dup2(in, 0);
		dup2(out, 1);
	}
	else if(strstr(s_temp,"<")!=NULL)
	{
		int in;
		tok = strtok_r(NULL,"<>",&endstr);
		trim_r(tok);
		in = open(tok, O_RDONLY);
		if(in<0)
		{
			perror("Error '<'");
			return;
		}
		dup2(in, 0);
	}
	else if(strstr(s_temp,">")!=NULL)
	{
		int out;
		tok = strtok_r(NULL,"<>",&endstr);
		trim_r(tok);
		if(strstr(s_temp,">>"))
		{
			out = open(tok, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		}
		else
			out = open(tok, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
		if(out<0)
		{
			perror("Error '>'");
			return;
		}
		dup2(out, 1);
	}

	strcpy(s,final_s);
	strcpy(s_save,final_s);
	functions();
	// dup2(original_in,0);
	// dup2(original_out,1);
	// dup2(0,original_in);
	// dup2(1,original_out);
	// printf("**%s -- %s\n", final_s,s);
}
