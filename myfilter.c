#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX_LINE_LENGTH 2048

FILE	*input_file;
char	line[MAX_LINE_LENGTH];

int	open_file(const char *filename)
{
	input_file = fopen(filename, "r");
	if (input_file == NULL)
	{
		perror("Error opening input file");
		return (0);
	}
	return (1);
}

void	close_file(void)
{
	if (input_file != NULL)
		fclose(input_file);
}

char	*get_next_line(void)
{
	static char	result[MAX_LINE_LENGTH];
	char		*newline;

	if (input_file == NULL || fgets(line, sizeof(line), input_file) == NULL)
		return (NULL);
	newline = strchr(line, '\n');
	if (newline)
		*newline = '\0';
	strcpy(result, line);
	return (result);
}

int	Get_Password(char *str)
{
	int	i;
	int password_index;

	i = 0;
	while(str[i])
		i++;
	i--;
	while (str[i] && i > 0)
	{
		if (str[i] == ';' || str[i] == ':' || str[i] == '|')
		{	
			i++;
			break;
		}
		i--;
	}
	password_index = i;
	return (password_index);
}

int	Get_user(char *str)
{
	int	i;
	int	email_index;

	i = Get_Password(str);
	i=i-2;
	while(str[i] && i > 0)
	{
		if (str[i] == ';' || str[i] == ':' || str[i] == '|' || str[i] == '/' || str[i] == ' ' || str[i] == '	' || (str[i] == 'n' && str[i-1] == 'e' && str[i-2] == 't'))
		{
			i++;
			break;
		}
		i--;
	}
		email_index= i;
		return (email_index);
}

char *to_email_pass(char *str)
{
	int password;
	int email;
	int splitter;
	char *Mailpass;
	int pass_len;
	int email_len;
	int	i;

	i = 0;
	password = Get_Password(str);
	email = Get_user(str);
	splitter = password - 1;
	email_len = (email - password - 1) * -1;
	pass_len = strlen(str) - password;
	Mailpass = malloc(100);
	while (str[email])
	{
		Mailpass[i] = str[email];
		email++;
		i++;
		if(str[email] == ';' || str[email] == ':' || str[email] == '/' || str[email] == ' ' || str[email] == '	' || str[email] == '|')
			break;
	}
	Mailpass[i] = ':';
	i++;
	while (str[password])
	{
		Mailpass[i] = str[password];
		password++;
		i++;
	}
	return (Mailpass);
}

int	main(void)
{
	char	*result;
	char	*line;

	if (!open_file("paste.txt"))
		return (1);
	while ((line = get_next_line()) != NULL)
	{
		to_email_pass(line);
		result = to_email_pass(line);
		printf("%s\n",result);
	}
	close_file();
	return (0);
}
