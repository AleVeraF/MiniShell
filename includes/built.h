#include "minishell.h"

# ifndef BUILT_H
# define BUILT_H

// Prototipos de funciones built-in

// CD
int ft_cd(t_cmd *cmd, t_shell *shell);
char *ft_getenv(char **envp, const char *key);
void ft_setenv(char ***envp, const char *key, const char *value);
char *resolve_cd_argument(char *arg, char *path_buffer, t_shell *shell);
char *resolve_cd_target(t_cmd *cmd, t_shell *shell);
void update_pwd_and_oldpwd(t_shell *shell);
// CD FIN


// PWD
int ft_pwd(t_cmd *cmd, t_shell *shell);
// PWD FIN

int ft_echo(t_cmd *cmd, t_shell *shell);



int builtin_export(t_cmd *cmd, t_shell *shell);
int	is_valid_identifier(char *str);
t_env	*create_env_node(char *key, char *value);
t_env	*add_export_var(t_env *env_list, char *arg);
int	print_exported_vars(t_env *env);
void	print_export_error(char *arg);




int	ft_env(t_cmd *cmd, t_shell *shell);
int ft_exit(t_cmd *cmd, t_shell *shell);
void free_env_array(char **envp);

// Función para ejecutar built-ins
int exec_builtin(t_cmd *cmd, t_shell *shell);
char *get_env_value(char *var, t_shell *shell);


int	ft_unset(t_cmd *cmd, t_shell *shell);
// Declaración externa del array de built-ins
extern t_builtin builtins[];

#endif
