#include "minishell.h"
// Busca el valor de una variable
char *ft_getenv(char **envp, const char *key)
{
    int key_len = ft_strlen(key);

    while (*envp)
    {
        if (ft_strncmp(*envp, key, key_len) == 0 && (*envp)[key_len] == '=')
            return *envp + key_len + 1; // Retorna la parte del valor después de '='
        envp++;
    }
    return NULL;
}


// Agrega o modifica una variable del entorno
void ft_setenv(char ***envp, const char *key, const char *value)
{
    int key_len = ft_strlen(key);
    int i = 0;

    // Buscar si la clave ya existe
    while ((*envp)[i])
    {
        if (strncmp((*envp)[i], key, key_len) == 0 && (*envp)[i][key_len] == '=')
        {
            // Reemplazar
            free((*envp)[i]);
            (*envp)[i] = malloc(strlen(key) + ft_strlen(value) + 2); // +1 para '=' y +1 para '\0'
            if (!(*envp)[i])
                return;
            sprintf((*envp)[i], "%s=%s", key, value);
            return;
        }
        i++;
    }

    // No existe, agregar nuevo
    char **new_envp = malloc(sizeof(char *) * (i + 2));
    if (!new_envp)
        return;
    for (int j = 0; j < i; j++)
        new_envp[j] = (*envp)[j];
    
    new_envp[i] = malloc(ft_strlen(key) + ft_strlen(value) + 2);
    if (!new_envp[i])
        return;
    sprintf(new_envp[i], "%s=%s", key, value);
    new_envp[i + 1] = NULL;

    free(*envp); // Ojo: solo si tienes el control total de `envp`
    *envp = new_envp;
}

char *resolve_cd_target(t_cmd *cmd, t_shell *shell)
{
    static char path[1024];

    if (!cmd->argv[1]) {
        char *home = ft_getenv(shell->envp, "HOME");
        if (!home) {
            write(STDERR_FILENO, "cd: variable HOME no establecida\n", 33);
            return NULL;
        }
        return home;
    }
    return resolve_cd_argument(cmd->argv[1], path, shell);
}

char *resolve_cd_argument(char *arg, char *path_buffer, t_shell *shell)
{
    if (strcmp(arg, "-") == 0) {
        char *oldpwd = ft_getenv(shell->envp, "OLDPWD");
        if (!oldpwd) {
            write(STDERR_FILENO, "cd: variable OLDPWD no establecida\n", 35);
            return NULL;
        }
        printf("%s\n", oldpwd);
        return oldpwd;
    } else if (arg[0] == '~') {
        char *home = ft_getenv(shell->envp, "HOME");
        if (!home) {
            write(STDERR_FILENO, "cd: variable HOME no establecida\n", 33);
            return NULL;
        }
            strcpy(path_buffer, home);
            strcat(path_buffer, arg + 1);
        return path_buffer;
    }

    return arg;
}

void update_pwd_and_oldpwd(t_shell *shell)
{
    char cwd[1024];
    char *oldpwd = ft_getenv(shell->envp, "PWD");

    if (oldpwd)
        ft_setenv(&shell->envp, "OLDPWD", oldpwd);

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_setenv(&shell->envp, "PWD", cwd);
    else
        perror("getcwd");
}

int ft_cd(t_cmd *cmd, t_shell *shell)
{
    char *target_dir = resolve_cd_target(cmd, shell);

    if (!target_dir)
        return 1;

    if (chdir(target_dir) != 0) {
        perror("cd");
        return 1;
    }

    update_pwd_and_oldpwd(shell);
    return 0;
}
