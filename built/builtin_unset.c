#include "minishell.h"


/*
** Valida si un nombre de variable es válido para unset.
*/
static int	is_valid_unset_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(str[0] == '_' || (str[0] >= 'A' && str[0] <= 'Z') ||
			(str[0] >= 'a' && str[0] <= 'z')))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(str[i] == '_' || (str[i] >= 'A' && str[i] <= 'Z') ||
				(str[i] >= 'a' && str[i] <= 'z') ||
				(str[i] >= '0' && str[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

/*
** Elimina una variable de la lista enlazada t_env.
*/
static void	remove_env_var(t_env **env, const char *key)
{
	t_env	*prev;
	t_env	*curr;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

/*
** Builtin unset: elimina una o más variables del entorno.
*/
int	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd || !cmd->argv || !shell)
		return (1); // Salida segura

	i = 1;
	while (cmd->argv[i])
	{
		if (!is_valid_unset_identifier(cmd->argv[i]))
		{
			write(2, "unset: `", 8);
			write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
			write(2, "': not a valid identifier\n", 27);
			shell->exit_status = 1;
		}
		else if (shell->envp) // ⚠️ Evita segfault si shell->env es NULL
			remove_env_var(&shell->envp, cmd->argv[i]);
		i++;
	}
	return (0);
}

