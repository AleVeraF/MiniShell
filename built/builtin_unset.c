#include "minishell.h"

/*
** is_valid_unset_identifier:
** Comprueba si un nombre de variable es válido para el comando unset.
** Reglas:
**  - Debe comenzar con letra o '_'.
**  - El resto de caracteres puede ser letra, número o '_'.
** Retorna 1 si es válido, 0 si no lo es.
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
** find_env_index:
** Busca el índice de una variable (KEY) en el array envp.
** Retorna el índice si existe, -1 si no se encuentra.
*/
static int	find_env_index(char **envp, char *key)
{
	int		i;
	size_t	len;

	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

/*
** remove_env_var_array:
** Elimina una variable del array envp (char **).
** - Busca el índice de la variable.
** - Libera la memoria de esa posición.
** - Desplaza el resto para cerrar el hueco.
*/
static char	**remove_env_var_array(char **envp, char *key)
{
	int	index;
	int	i;

	index = find_env_index(envp, key);
	if (index == -1)
		return (envp);
	free(envp[index]);
	i = index;
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	return (envp);
}

/*
** ft_unset:
** Implementación del comando unset.
** - Recorre todos los argumentos pasados.
** - Si el identificador es inválido → muestra error.
** - Si es válido → elimina la variable del envp.
*/
int	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd || !cmd->argv || !shell)
		return (1);
	i = 1;
	while (cmd->argv[i])
	{
		if (!is_valid_unset_identifier(cmd->argv[i]))
		{
			write(2, "unset: `", 8);
			write(2, cmd->argv[i], ft_strlen(cmd->argv[i]));
			write(2, "': not a valid identifier\n", 27);
			shell->last_status = 1;
		}
		else if (shell->envp)
			shell->envp = remove_env_var_array(shell->envp, cmd->argv[i]);
		i++;
	}
	return (0);
}
