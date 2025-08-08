#include "minishell.h"

#ifndef EXECUTOR_H
#define EXECUTOR_H

void    execute_commands(t_cmd *commands, t_shell *shell);
int		ft_strcmp(char *s1, char *s2);
char	**ultra_split(t_token *token_list);

#endif
