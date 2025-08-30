#include "minishell.h"

int ft_pwd(t_cmd *cmd, t_shell *shell)
{
    char cwd[1024];

    (void)cmd;
    (void)shell;
    if (getcwd(cwd, sizeof(cwd)))
    {
        write(1, cwd, ft_strlen(cwd));
        write(1, "\n", 1);
        return (0);
    }
    perror("pwd");
    return (1);
}