#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char	*to_email_pass(char *str)
{
	int	i;
	int	j;
	char *result;

	i = 0;
	j = 0;
	while(str[i])
		i++;
	while(str[i] && (str[i] != ':' || str[i] != ';' || str[i] != '|' ))
		i--;
	while(i > 0 && (str[i] != ':' || str[i] != ';' || str[i] != '|' || str[i] != ' ' ))
		i--;
	i++;

	result = malloc(strlen(str + 1));
	while(str[i])
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

int	main(void)
{
	char	*line;

	if (!open_file("paste.txt"))
		return (1);
	while ((line = get_next_line()) != NULL)
		printf("%s\n", to_email_pass(line));
	close_file();
	return (0);
}
