#include "minishell.h"

t_token *create_token_safe(t_token_type type, char *line_token)
{
    t_token *token;

    token = create_token(type, line_token);
    if (!token)
        free(line_token);
    return (token);
}

t_token	*create_token(t_token_type type, char *str)
{
	t_token	*token;

	token = NULL;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

static void	add_token(t_token **token_list, t_token *new)
{
	t_token	*current;

	if (*token_list == NULL)
	{
		*token_list = new;
		return ;
	}
	current = *token_list;
	while (current->next)
		current = current->next;
	current->next = new;
}

void	free_tokens(t_token *token_list)
{
	t_token	*current;
	t_token	*next;

	current = token_list;
	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

t_token	*tokenize_line(char *line, t_shell *shell)
{
	t_token	*token_list;
	t_token	*new_token;
	int		i;

	token_list = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\0')
			break ;
		if (line[i] == line[i + 1] && (line[i] == '>' || line[i] == '<'))
			new_token = redir_operators_app_her(line, &i);
		else if (line[i] == '|' || line[i] == '>' || line[i] == '<')
			new_token = simple_redir(line, &i);
		else if (line[i])
			new_token = words_and_quotes(line, &i, shell);
		else if (line[i] == '"' || line[i] == '\'')
			new_token = handle_quotes(line, &i, shell);
		if (!new_token)
			return (free_tokens(token_list), NULL);
		add_token(&token_list, new_token);
	}
	return (token_list);
}
