#include "minishell.h"

/*
** is_valid_identifier:
** Comprueba si el nombre de variable es válido (sin el valor).
*/
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(str[0] >= 'A' && str[0] <= 'Z') &&
		!(str[0] >= 'a' && str[0] <= 'z') &&
		str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(str[i] >= 'A' && str[i] <= 'Z') &&
			!(str[i] >= 'a' && str[i] <= 'z') &&
			!(str[i] >= '0' && str[i] <= '9') &&
			str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
** find_env_index:
** Busca la posición de una variable por su clave (KEY).
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
** ft_realloc_envp:
** Añade una variable nueva al final del array envp.
*/
static char	**ft_realloc_envp(char **envp, char *new_var)
{
	int		count;
	char	**new_envp;
	int		i;

	count = 0;
	while (envp && envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (envp);
	i = 0;
	while (i < count)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[count] = ft_strdup(new_var);
	new_envp[count + 1] = NULL;
	free(envp);
	return (new_envp);
}

/*
** set_env_var:
** Agrega o actualiza una variable en formato KEY=VALUE.
*/
static char	**set_env_var(char **envp, char *arg)
{
	char	*equal;
	char	*key;
	int		index;

	equal = ft_strchr(arg, '=');
	if (equal)
		key = ft_substr(arg, 0, equal - arg);
	else
		key = ft_strdup(arg);
	if (!key)
		return (envp);
	index = find_env_index(envp, key);
	free(key);
	if (index != -1)
	{
		free(envp[index]);
		envp[index] = ft_strdup(arg);
		return (envp);
	}
	envp = ft_realloc_envp(envp, arg);
	return (envp);
}

/*
** sort_envp:
** Crea una copia de envp y la ordena alfabéticamente.
*/
static char	**sort_envp(char **envp)
{
	int		i;
	int		j;
	char	*tmp;
	char	**sorted;

	i = 0;
	while (envp[i])
		i++;
	sorted = malloc(sizeof(char *) * (i + 1));
	if (!sorted)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		sorted[i] = ft_strdup(envp[i]);
		i++;
	}
	sorted[i] = NULL;
	i = 0;
	while (sorted[i])
	{
		j = i + 1;
		while (sorted[j])
		{
			if (ft_strcmp(sorted[i], sorted[j]) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (sorted);
}

/*
** print_exported_vars:
** Imprime las variables en orden alfabético con formato declare -x.
*/
static int	print_exported_vars(char **envp)
{
	int		i;
	char	*equal;
	char	**sorted;

	sorted = sort_envp(envp);
	if (!sorted)
		return (1);
	i = 0;
	while (sorted[i])
	{
		write(1, "declare -x ", 11);
		equal = ft_strchr(sorted[i], '=');
		if (equal)
		{
			write(1, sorted[i], equal - sorted[i] + 1);
			write(1, "\"", 1);
			write(1, equal + 1, ft_strlen(equal + 1));
			write(1, "\"", 1);
		}
		else
			write(1, sorted[i], ft_strlen(sorted[i]));
		write(1, "\n", 1);
		free(sorted[i]);
		i++;
	}
	free(sorted);
	return (0);
}

/*
** print_export_error:
** Muestra un error si el identificador no es válido.
*/
void	print_export_error(char *arg)
{
	write(2, "export: `", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

/*
** builtin_export:
** Implementa el comando export usando char **envp en t_shell.
*/
int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;

	if (!cmd->argv[1])
		return (print_exported_vars(shell->envp));
	i = 1;
	while (cmd->argv[i])
	{
		if (!is_valid_identifier(cmd->argv[i]))
			print_export_error(cmd->argv[i]);
		else
			shell->envp = set_env_var(shell->envp, cmd->argv[i]);
		i++;
	}
	return (0);
}
