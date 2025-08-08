#include "minishell.h"

// Tabla de builtins
t_builtin builtins[] = {
    {"cd", ft_cd},
    {"pwd", ft_pwd},
    {"echo", ft_echo},
    {"export", builtin_export},
    {"env", ft_env},
    {"exit", ft_exit},
    {"unset", ft_unset}, // Asegúrate de implementar ft_unset
    {NULL, NULL} // Fin
};

// Ejecuta el builtin si existe
int exec_builtin(t_cmd *cmd, t_shell *shell)
{
    int i = 0;

    if (!cmd->argv || !cmd->argv[0]) // Verificamos que haya comando
        return 1;

    while (builtins[i].name) {
        if (strcmp(cmd->argv[0], builtins[i].name) == 0)
            return builtins[i].func(cmd, shell);
        i++;
    }

    return 1; // No se encontró
}
