#include "minishell.h"

static int	join_token_part(char **final_token, char *part)
{
	char	*temp;

	if (!part)
	{
		free(*final_token);
		return (1);
	}
	temp = *final_token;
	*final_token = ft_strjoin(*final_token, part);
	free(temp);
	free(part);
	if (!*final_token)
		return (1);
	return (0);
}

t_token	*words_and_quotes(char *line, int *i, t_shell *shell)
{
	char type_quote;
	int count_quote;
	int count_word;
	char	*part;
	char	*final_token;

	count_word = 0;
	count_quote = 0;
	type_quote = 0;

	final_token = ft_strdup("");
	if (!final_token)
		return (NULL);
	while (line[*i] && line[*i] != ' ' && line[*i] != '|' && \
		   line[*i] != '>' && line[*i] != '<')
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			type_quote = line[*i]; 
			part = handle_quotes_join(line, i, shell);
			count_quote++;
		}	
		else
		{
			part = words_join(line, i, shell);
			count_word++;
		}	
		if (join_token_part(&final_token, part) != 0)
			return (NULL);
	}
	if(count_word == 0 && count_quote == 1)
	{
		if(type_quote == '"')
			return(create_token_safe(T_QUOTED_DOUBLE, final_token));
		if(type_quote == '\'')
			return(create_token_safe(T_QUOTED_SINGLE, final_token));
	}	
	return (create_token_safe(T_WORD, final_token));
}
