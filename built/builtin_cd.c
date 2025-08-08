#include "minishell.h"
// Busca el valor de una variable
char *ft_getenv(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return env->value;
		env = env->next;
	}
	return NULL;
}

// Agrega o modifica una variable del entorno
void ft_setenv(t_env **env, const char *key, const char *value)
{
	t_env *current = *env;

	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return;
		}
		current = current->next;
	}

	// No existe: crear nuevo nodo
	t_env *new = malloc(sizeof(t_env));
	if (!new)
		return;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
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
