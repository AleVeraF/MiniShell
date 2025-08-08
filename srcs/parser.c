#include "minishell.h" 

static int general_check(t_token *token_list);
static t_cmd *build_commands(t_token *token_list);

t_cmd   *parse_tokens(t_token *token_list, t_shell *shell)
{
	(void)shell;
	t_token *current;
	current = token_list;

	if(current)
	{
		if(general_check(token_list))
		{	
			printf("no se genero token\n");
			return (NULL);
		}
		return (build_commands(token_list));
	}
	return(NULL);
}

static int general_check(t_token *token_list)
{
	if (check_initial_token(token_list))
		return(1);
	if (check_all_redirections(token_list))
		return(1);
	if (check_all_pipe(token_list))	
		return(1);
	return(0);
}

t_cmd *build_commands(t_token *token_list)
{
	t_cmd *new_command;
	new_command = NULL;
	
	if(is_token_word(token_list)
		&& token_list->next == NULL)
	new_command = one_word_command(token_list);
	if(is_token_word(token_list)
		&& token_list->next != NULL)
	new_command = words_plus_cmd(token_list);	
	return(new_command);
}
/*
	printf("si se genero token\n");
	print_token_list(token_list);
	return(NULL);
}*/













