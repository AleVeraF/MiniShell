#include "minishell.h"
#include <stdio.h>
int ft_strcmp(char *s1, char *s2)
{
	int i;
	i = 0;

	if(!s1 || !s2)
		return(1);
	while(s1[i] && s2[i])
	{
		if(s1[i] == s2[i])
			i++;
		else
			break;
	}		
	return(s1[i] - s2[i]);
}

char **ultra_split(t_token *token_list)
{
	int i;
	char **argv;
	int word;
	t_token *current;
	current = token_list;

	word = 0;
	i = 0;
	argv = NULL;

	while(current)
	{
		word++;
		current = current->next; 
	}
	current = token_list;
	argv = malloc(sizeof(char *) * (word + 1));

	while(current)
	{
		argv[i] = ft_strdup(current->str);
		current = current->next;
		i++;
	}
	argv[i] = NULL;
	return(argv);
}

		


	
		


