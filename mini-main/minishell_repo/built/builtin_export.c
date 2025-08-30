#include "minishell.h"

static int str_cmp(const void *a, const void *b)
{
    char * const *sa = (char * const *)a;
    char * const *sb = (char * const *)b;
    return strcmp(*sa, *sb);
}

static char **sort_envp(char **envp)
{
    int count = 0;
    char **copy;

    // haz una copia con tu función
    copy = copy_env(envp);
    if (!copy)
        return (NULL);

    // cuenta elementos
    while (copy[count])
        count++;

    // ordénalos
    qsort(copy, count, sizeof(char *), str_cmp);

    return (copy);
}

static int is_valid_identifier_aux(const char *str)
{
    int i;

    if (!str || !str[0])
        return (0);
    if (!(ft_isalpha(str[0]) || str[0] == '_'))
        return (0);

    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!(ft_isalnum(str[i]) || str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

void print_export_error(const char *arg)
{
    write(2, "bash: export: `", 15);
    write(2, arg, ft_strlen(arg));
    write(2, "': not a valid identifier\n", 26);
}

static int print_exported_vars(char **envp)
{
    int i;
    char *equal;
    char **sorted;

    sorted = sort_envp(envp);
    if (!sorted)
        return (1);

    i = 0;
    while (sorted[i])
    {
        write(1, "declare -x ", 11);
        equal = ft_strchr(sorted[i], '=');
        if (equal)
        {
            write(1, sorted[i], equal - sorted[i] + 1);
            write(1, "\"", 1);
            write(1, equal + 1, ft_strlen(equal + 1));
            write(1, "\"", 1);
        }
        else
        {
            write(1, sorted[i], ft_strlen(sorted[i]));
        }
        write(1, "\n", 1);
        free(sorted[i]);
        i++;
    }
    free(sorted);
    return (0);
}

int builtin_export(t_cmd *cmd, t_shell *shell)
{
    int i;
    char *sep;
    char *key;
    char *value;

    if (!cmd->argv[1])
        return (print_exported_vars(shell->envp));

    i = 1;
    while (cmd->argv[i])
    {
        if (!is_valid_identifier_aux(cmd->argv[i]))
        {
            print_export_error(cmd->argv[i]);
        }
        else
        {
            sep = ft_strchr(cmd->argv[i], '=');
            if (sep)
            {
                key = ft_substr(cmd->argv[i], 0, sep - cmd->argv[i]);
                value = sep + 1;
                ft_setenv(&shell->envp, key, value);
                free(key);
            }
            else
            {
                ft_setenv(&shell->envp, cmd->argv[i], "");
            }
        }
        i++;
    }
    return (0);
}
