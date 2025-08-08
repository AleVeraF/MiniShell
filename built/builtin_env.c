#include "minishell.h"

/*
** Imprime las variables del entorno (formato VAR=VALOR).
** Solo muestra las que tienen value (es decir, contienen '=').
** Si se pasa un argumento extra, muestra un error.
*/
int	ft_env(t_cmd *cmd, t_shell *shell)
{
	char **env;

	if (cmd->argv[1])
	{
		write(2, "env: '", 6);
		write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(2, "': No such file or directory\n", 30);
		shell->last_status = 127;
		return (1);
	}
	env = shell->envp;
	while (*env)
	{
		// Solo imprimimos si hay '=' en la variable
		if (ft_strchr(*env, '='))
		{
			write(1, *env, ft_strlen(*env));
			write(1, "\n", 1);
		}
		env++;
	}
	shell->last_status = 0;
	return (0);
}
