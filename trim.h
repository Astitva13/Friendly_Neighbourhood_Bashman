void trim()
{
	char str[10000];
	strcpy(str,s);
	int n = strlen(str); 
	int i = 0, j = -1; 
	int spaceFound = 0; 
	while (++j < n && str[j] == ' '); 
	while (j < n) 
	{ 
		if (str[j] != ' ') 
		{ 
			if ((str[j] == ',' || 
				str[j] == '?') && i - 1 >= 0 && 
				str[i - 1] == ' ') 
				str[i - 1] = str[j++]; 
			else
				str[i++] = str[j++]; 
			spaceFound = 0; 
		} 
		else if (str[j++] == ' ') 
		{ 
			if (spaceFound==0) 
			{ 
				str[i++] = ' '; 
				spaceFound = 1; 
			} 
		} 
	} 
	char temp_str[10000]="";
	if (i <= 1)
		strncpy(temp_str,str,i+1);
	else
		strncpy(temp_str,str,i);
	strcpy(s,temp_str);
	strcpy(s_save,temp_str);
}

void trim_r(char * string)
{
	char str[10000];
	strcpy(str,string);
	int n = strlen(str); 
	int i = 0, j = -1; 
	int spaceFound = 0; 
	while (++j < n && str[j] == ' '); 
	while (j < n) 
	{ 
		if (str[j] != ' ') 
		{ 
			if ((str[j] == ',' || 
				str[j] == '?') && i - 1 >= 0 && 
				str[i - 1] == ' ') 
				str[i - 1] = str[j++]; 
			else
				str[i++] = str[j++]; 
			spaceFound = 0; 
		} 
		else if (str[j++] == ' ') 
		{ 
			if (spaceFound==0) 
			{ 
				str[i++] = ' '; 
				spaceFound = 1; 
			} 
		} 
	} 
	char temp_str[10000]="";
	if (i <= 1)
		strncpy(temp_str,str,i+1);
	else
		strncpy(temp_str,str,i);
	while(temp_str[strlen(temp_str)-1]==' ')
		temp_str[strlen(temp_str)-1]='\0';
	strcpy(string,temp_str);
}