#include "minishell.h"

static void process_tokens(t_token *tokens, char *line, t_shell *shell);
int  handle_ctrl_c(char **line);

void	start_loop(t_shell *shell)
{
	char	*line;
	t_token *tokens;

	while (shell->running)
	{
		line = read_input();
		if (check_ctrl_d(line))
			break ;
		if (handle_ctrl_c_signal(&line))
		{
		}
		else
		{
			if (isatty(STDIN_FILENO) && history(line))
		    	add_history(line);
		    
			tokens = tokenize_line(line, shell);
			if(tokens)
			{
				process_tokens(tokens, line, shell);	 
			}
			else
				free(line);
		}
	}
}

int	handle_ctrl_c(char **line)
{
	g_signal = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	free(*line);
	*line = NULL;
	return (1);
}

static void process_tokens(t_token *tokens, char *line, t_shell *shell)
{
    t_cmd *commands;
	commands = NULL;

	commands = parse_tokens(tokens, shell);
	if (!commands)
	{
		shell->last_status = INVALID;  // Aquí se actualiza
		free_tokens(tokens);
		free(line);
		printf("Build responde NULL, aun no implemento\n"); 
		return;
	}
	execute_commands(commands, shell);
   /*free_everything(line, tokens, commands);
    free_tokens (tokens);
	free(line);*/
	//print_token_list(tokens);
    free_tokens(tokens);
    free(line);
}

