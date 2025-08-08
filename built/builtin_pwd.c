#include "minishell.h"

// Muestra el directorio actual
int ft_pwd(t_cmd *cmd, t_shell *shell)
{
    (void)cmd;
    (void)shell;

    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
    else {
        write(STDERR_FILENO, "pwd: ", 5);
        write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
        write(STDERR_FILENO, "\n", 1);
    }

    return 0;
}
