#include "minishell.h"

/**
 * free_env_array - libera un array de variables de entorno
 */
void free_env_array(char **envp)
{
	int i = 0;

	if (!envp)
		return;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

/**
 * is_numeric - verifica si una cadena representa un número válido
 */
static int	is_numeric(const char *str)
{
	int	i = 0;

	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * print_exit_error - imprime error de argumento no numérico y sale
 */
static void	print_exit_error(char *arg, t_shell *shell)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 29);
	free_env_array(shell->envp);
	exit(255);
}

/**
 * handle_exit_arguments - maneja los argumentos de salida y valida
 */
static int	handle_exit_arguments(t_cmd *cmd, t_shell *shell)
{
	int	exit_code;

	if (!is_numeric(cmd->argv[1]))
		print_exit_error(cmd->argv[1], shell);
	if (cmd->argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		shell->last_status = 1;
		return (1);
	}
	exit_code = ft_atoi(cmd->argv[1]);
	free_env_array(shell->envp);
	exit(exit_code);
}

/**
 * ft_exit - builtin principal para salir de la minishell
 */
int	ft_exit(t_cmd *cmd, t_shell *shell)
{
	write(1, "exit\n", 5);
	if (!cmd->argv[1])
	{
		free_env_array(shell->envp);
		exit(shell->last_status);
	}
	return (handle_exit_arguments(cmd, shell));
}
