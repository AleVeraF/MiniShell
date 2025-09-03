/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvera-f <alvera-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 19:15:43 by alvera-f          #+#    #+#             */
/*   Updated: 2025/09/03 19:39:39 by alvera-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	int			i;
	t_builtin	builtins[];

	builtins[] = {
	{"cd", ft_cd},
	{"pwd", ft_pwd},
	{"echo", ft_echo},
	{"export", builtin_export},
	{"env", ft_env},
	{"exit", ft_exit},
	{"unset", ft_unset},
	{NULL, NULL}
	};

	if (!cmd->argv || !cmd->argv[0])
		return (1);
	while (builtins[i].name)
	{
		if (strcmp(cmd->argv[0], builtins[i].name) == 0)
			return (builtins[i].func(cmd, shell));
		i++;
	}
	return (1);
}
