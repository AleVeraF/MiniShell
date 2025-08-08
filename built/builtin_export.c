#include "minishell.h"
/*
** Verifica si el nombre de la variable es válido.
** Retorna 1 si es válido, 0 si es inválido.
*/
int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!(str[0] >= 'A' && str[0] <= 'Z') &&
		!(str[0] >= 'a' && str[0] <= 'z') &&
		str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(str[i] >= 'A' && str[i] <= 'Z') &&
			!(str[i] >= 'a' && str[i] <= 'z') &&
			!(str[i] >= '0' && str[i] <= '9') &&
			str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
** Crea un nuevo nodo del tipo t_env con su clave y valor.
*/
t_env	*create_env_node(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}


t_env	*find_env_var(t_env *env, const char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

/*
** Añade una nueva variable al principio de la lista de export.
** Si hay '=', guarda clave y valor; si no, solo la clave.
*/

/**
 * create_new_export_node - crea un nuevo nodo export con key y valor
 */
 static t_env	*create_new_export_node(char *key, char *val)
 {
	 t_env	*new;
 
	 new = malloc(sizeof(t_env));
	 if (!new)
	 {
		 free(key);
		 free(val);
		 return (NULL);
	 }
	 new->key = key;
	 new->value = val;
	 new->next = NULL;
	 return (new);
 }
 
 /**
  * update_existing_env_var - actualiza el valor de una variable ya existente
  */
 static void	update_existing_env_var(t_env *existing, char *val)
 {
	 free(existing->value);
	 existing->value = val;
 }
 
 /**
  * split_key_value - separa clave y valor desde un argumento con '='
  */
 static void	split_key_value(char *arg, char **key, char **val)
 {
	 char	*equal;
 
	 equal = ft_strchr(arg, '=');
	 if (equal)
	 {
		 *key = ft_substr(arg, 0, equal - arg);
		 *val = ft_strdup(equal + 1);
	 }
	 else
	 {
		 *key = ft_strdup(arg);
		 *val = NULL;
	 }
 }
 
 /**
  * add_export_var - agrega o actualiza una variable de entorno exportada
  */
 t_env	*add_export_var(t_env *env_list, char *arg)
 {
	 char	*key;
	 char	*val;
	 t_env	*existing;
	 t_env	*new;
 
	 split_key_value(arg, &key, &val);
	 existing = find_env_var(env_list, key);
	 if (existing)
	 {
		 if (val)
			 update_existing_env_var(existing, val);
		 free(key);
		 return (env_list);
	 }
	 new = create_new_export_node(key, val);
	 if (!new)
		 return (env_list);
	 new->next = env_list;
	 return (new);
 }
 

/*
** Imprime todas las variables exportadas con formato declare -x.
*/
int	print_exported_vars(t_env *env)
{
	while (env)
	{
		write(1, "declare -x ", 11);
		write(1, env->key, strlen(env->key));
		if (env->value)
		{
			write(1, "=\"", 2);
			write(1, env->value, strlen(env->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}

/*
** Muestra un error si el identificador es inválido.
*/
void	print_export_error(char *arg)
{
	write(2, "export: `", 9);
	write(2, arg, strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

/*
** Comando export usando lista enlazada t_cmd para argumentos
** y t_shell que contiene la lista de variables exportadas.
*/
int builtin_export(t_cmd *cmd, t_shell *shell)
{
    int i;

    if (!cmd->argv[1])
        return (print_exported_vars(shell->envp)); // Lista t_env* donde tienes las variables exportadas

    i = 1;
    while (cmd->argv[i])
    {
        if (!is_valid_identifier(cmd->argv[i]))
            print_export_error(cmd->argv[i]);
        else
            shell->envp = add_export_var(shell->envp, cmd->argv[i]); // Aquí agregas/modificas variable
        i++;
    }
    return (0);
}

