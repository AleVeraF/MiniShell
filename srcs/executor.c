#include "minishell.h"                                                           

void    execute_commands(t_cmd *commands, t_shell *shell)
{
	(void)shell;
	if(ft_strcmp(commands->argv[0], "echo") == 0)
		ft_echo(commands, shell);		
	if(ft_strncmp(commands->argv[0], "pwd", 3) == 0)
		ft_pwd(commands, shell);
	if(ft_strncmp(commands->argv[0], "cd", 2) == 0)
		ft_cd(commands, shell);
	if(ft_strncmp(commands->argv[0], "unset", 5) == 0)
		ft_unset(commands, shell);
	if(ft_strncmp(commands->argv[0], "export", 6) == 0)
		builtin_export(commands, shell);
	if(ft_strncmp(commands->argv[0], "env", 3) == 0)
		ft_env(commands, shell);
	if(ft_strncmp(commands->argv[0], "exit", 4) == 0)
		ft_exit(commands, shell);
}

