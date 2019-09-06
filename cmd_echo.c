void strrem(char *s, char c){ 
	int j, n = strlen(s); 
	for (int i=j=0; i<n; i++) if (s[i] != c) s[j++] = s[i]; 
		s[j] = '\0'; 
}

void cmd_echo()
{
	char* tok;
	tok = strtok(s," ");
	if(strcmp(tok,"echo")==0)
	{
		tok = strtok(0,"");
		strrem(tok,'"');
		strrem(tok,'\'');
		printf("%s\n", tok);
		stx=1;
	}
	strcpy(s,s_save);
}