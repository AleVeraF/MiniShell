#include "minishell.h"

#include <stdlib.h>
#include <string.h>

char	**copy_env(char **envp)
{
	int		count;
	char	**new_envp;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	new_envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = strdup(envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}


void	init_shell(t_shell *shell, char **envp)
{
	if (!shell || !envp)
		return ;
	shell->envp = copy_env(envp); // ← ahora apunta a tu copia
	shell->last_status = EXIT_OK;
	shell->running = 1;
	shell->cmds = NULL;
}


void	cleanup_shell(t_shell *shell)
{
	(void)shell;
}
