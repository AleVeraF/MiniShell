#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h> 
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

// Headers internos del proyecto

typedef enum e_token_type {
	T_WORD,
	T_QUOTED_DOUBLE,  
   	T_QUOTED_SINGLE,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token {
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}t_token;

typedef struct s_cmd
{
	char				**argv;
	char				*infile;
	char				*outfile;
	char				*heredoc_delimiter;
	int					append;
	int					pipe_in;
	int					pipe_out;
	struct s_cmd		*next;
}						t_cmd;


typedef struct s_env
{
	char			*key;    // Nombre de la variable (ejemplo: PATH)
	char			*value;  // Valor de la variable (ejemplo: /usr/bin)
	struct s_env	*next;   // Apunta al siguiente nodo de la lista
}	t_env;

typedef struct s_shell {
	char			**envp;
	int				last_status;
	int				running;
	struct s_cmd	*cmds;
}					t_shell;

typedef struct s_builtin {
    char *name;
    int (*func)(t_cmd *cmd, t_shell *shell);
} t_builtin;


typedef enum e_status
{
	EXIT_OK = 0,// Comando ejecutado correctamente
	EXIT_KO = 1,// Falla general
	INVALID = 2,// Error de sintaxis u otro uso inválido
	CMD_NOT_EXECUTABLE = 126,// Comando encontrado pero no ejecutable
	UNKNOWN_COMMAND = 127,// Comando no encontrado
	LIMITER = 256// Usado internamente para heredoc
}	t_status;

# include "parser.h" // Aquí se declaran las funciones de análisis sintáctico y semántico.
# include "shell.h"  
# include "tokenizer.h" 
# include "signals.h"  // de declara la variable global para manejo de señales.
# include "status.h"  //  aquí va un enum,  para errores etc.
# include "executor.h"
# include "main_aux.h" // funciones auxiliares del main.c y main_aux.c
# include "built.h"

#endif
