#include "minishell.h"

char *ft_getenv(char **envp, const char *key)
{
	int key_len;

	key_len = ft_strlen(key);
	while (*envp)
	{
		if (ft_strncmp(*envp, key, key_len) == 0 && (*envp)[key_len] == '=')
		return (*envp + key_len + 1);
		envp++;
	}
	return (NULL);
}

static char *build_env_var(const char *key, const char *value)
{
	char *tmp;
	char *var;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	var = ft_strjoin(tmp, value);
	free(tmp);
	return (var);
}

void ft_setenv(char ***envp, const char *key, const char *value)
{
	int i;
	int key_len;
	char *new_var;
	char **new_envp;

	key_len = ft_strlen(key);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, key_len) == 0
			&& (*envp)[i][key_len] == '=')
		{
			new_var = build_env_var(key, value);
			if (!new_var)
				return ;
			free((*envp)[i]);
			(*envp)[i] = new_var;
			return ;
		}
		i++;
	}
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return ;
	ft_memcpy(new_envp, *envp, sizeof(char *) * i);
	new_var = build_env_var(key, value);
	if (!new_var)
		return ;
	new_envp[i] = new_var;
	new_envp[i + 1] = NULL;
	free(*envp);
	*envp = new_envp;
}

static char *expand_home(char *arg, t_shell *shell)
{
char *home;
char *expanded;

home = ft_getenv(shell->envp, "HOME");
if (!home)
{
write(2, "bash: cd: HOME not set\n", 23);
return (NULL);
}
expanded = ft_strjoin(home, arg + 1);
if (!expanded)
return (NULL);
return (expanded);
}

char *resolve_cd_target(t_cmd *cmd, t_shell *shell)
{
char *home;

if (!cmd->argv[1])
{
home = ft_getenv(shell->envp, "HOME");
if (!home)
{
write(2, "bash: cd: HOME not set\n", 23);
return (NULL);
}
return (ft_strdup(home));
}
return (resolve_cd_argument(cmd->argv[1], shell));
}

char *resolve_cd_argument(char *arg, t_shell *shell)
{
char *oldpwd;

if (ft_strcmp(arg, "-") == 0)
{
oldpwd = ft_getenv(shell->envp, "OLDPWD");
if (!oldpwd)
{
write(2, "bash: cd: OLDPWD not set\n", 25);
return (NULL);
}
printf("%s\n", oldpwd);
return (ft_strdup(oldpwd));
}
else if (arg[0] == '~')
return (expand_home(arg, shell));
return (ft_strdup(arg));
}

void update_pwd_and_oldpwd(t_shell *shell)
{
char *oldpwd;
char *cwd;

oldpwd = ft_getenv(shell->envp, "PWD");
if (oldpwd)
ft_setenv(&shell->envp, "OLDPWD", oldpwd);
cwd = getcwd(NULL, 0);
if (cwd)
{
ft_setenv(&shell->envp, "PWD", cwd);
free(cwd);
}
else
perror("bash: cd");
}

int ft_cd(t_cmd *cmd, t_shell *shell)
{
char *target_dir;

target_dir = resolve_cd_target(cmd, shell);
if (!target_dir)
return (1);
if (chdir(target_dir) != 0)
{
write(2, "bash: cd: ", 10);
write(2, target_dir, ft_strlen(target_dir));
write(2, ": ", 2);
write(2, strerror(errno), ft_strlen(strerror(errno)));
write(2, "\n", 1);
free(target_dir);
return (1);
}
update_pwd_and_oldpwd(shell);
free(target_dir);
return (0);
}
