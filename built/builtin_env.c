#include "minishell.h"

/*
** Imprime las variables del entorno (formato VAR=VALOR).
** Solo muestra las que tienen value (es decir, contienen '=').
** Si se pasa un argumento extra, muestra un error.
*/
int	ft_env(t_cmd *cmd, t_shell *shell)
{
	t_env	*env;

	if (cmd->argv[1])
	{
		write(2, "env: '", 6);
		write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(2, "': No such file or directory\n", 30);
		shell->exit_status = 127;
		return (1);
	}
	env = shell->envp;
	while (env)
	{
		if (env->value)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	shell->exit_status = 0;
	return (0);
}
