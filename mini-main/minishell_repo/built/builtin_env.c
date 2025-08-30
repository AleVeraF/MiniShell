#include "minishell.h"

int ft_env(t_cmd *cmd, t_shell *shell)
{
    char **env;
    
    if (cmd->argv[1])
    {
        write(2, "env: '", 6);
        write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
        write(2, "': No such file or directory\n", 30);
        shell->last_status = 127;
        return (127);
    }
    env = shell->envp;
    while (env && *env)
    {
        if (ft_strchr(*env, '=')) // Solo si tiene '='
        {
            write(1, *env, ft_strlen(*env));
            write(1, "\n", 1);
        }
        env++;
    }
    shell->last_status = 0;
    return (0);
}
