#ifndef SHELL_H
# define SHELL_H

#include <minishell.h>

/*typedef struct s_cmd
{
	char				**argv;
	char				*infile;
	char				*outfile;
	char				*heredoc_delimiter;
	int					append;
	int					pipe_in;
	int					pipe_out;
	struct s_cmd		*next;
}						t_cmd;*/


/* Inicializa el estado del shell */
void	init_shell(t_shell *shell, char **envp);

/* Libera los recursos del shell al terminar */
void	cleanup_shell(t_shell *shell);

#endif
