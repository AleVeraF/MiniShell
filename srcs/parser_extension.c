#include "minishell.h"

t_cmd *one_word_command(t_token *token_list)
{
	t_cmd *new_command;
	new_command = NULL;

	new_command = ft_calloc(1, sizeof(t_cmd));
	if(!new_command)
		return(NULL);
	new_command->argv = super_split(token_list->str,' ', '\t');
	/*printf("%s %c", new_command->argv[0], '\n');*/
	return(new_command);
 }

t_cmd *words_plus_cmd(t_token *token_list)
{
/*	int i;*/
	t_token *current;
	t_cmd *new_command;
	new_command = NULL;
	current = token_list;

/*	i = 0;*/

	new_command = ft_calloc(1, sizeof(t_cmd));
	if(!new_command)
		return(NULL);
	while(current)
	{
		if(current->next && is_token_word(current->next))
			current = current->next;
		else 
			break;
	}
	if(is_token_word(current)
		&& current->next == NULL)
		new_command->argv = ultra_split(token_list);
   /*while(new_command->argv[i])
	{
		printf("%s", new_command->argv[i]);
		i++;
	}*/
	return(new_command);
}



             


		

		
		
		


