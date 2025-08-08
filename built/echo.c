#include "minishell.h"
/*#include "builtins.h"
#include "../includes/shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>*/

/*
 * check_valid_nflag - chequea si una string es un -n válido (-n, -nnnn)
 */
static int check_valid_nflag(char *arg)
{
    int i;

    if (!arg || arg[0] != '-' || arg[1] != 'n')
        return 0;
    i = 2;
    while (arg[i] && arg[i] == 'n')
        i++;
    if (arg[i] == '\0')
        return 1;
    return 0;
}

/**
 * get_env_value - busca una variable de entorno dentro del shell
 */
static char *get_env_value(char *var, t_shell *shell)
{
    int i;
    size_t len;

    i = 0;
    len = strlen(var);
    while (shell->envp[i])
    {
        if (strncmp(shell->envp[i], var, len) == 0 && shell->envp[i][len] == '=')
            return shell->envp[i] + len + 1;
        i++;
    }
    return "";
}

/**
 * expand_variable - expande variables tipo $VAR
 */
static void expand_variable(char *arg, t_shell *shell)
{
    int i;
    int start;
    char save;
    char *value;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '$' && arg[i + 1] && ((arg[i + 1] >= 'A' && arg[i + 1] <= 'Z') || (arg[i + 1] >= 'a' && arg[i + 1] <= 'z') || arg[i + 1] == '_'))
        {
            i++;
            start = i;
            while (arg[i] && ((arg[i] >= 'A' && arg[i] <= 'Z') || (arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= '0' && arg[i] <= '9') || arg[i] == '_'))
                i++;
            save = arg[i];
            arg[i] = '\0';
            value = get_env_value(&arg[start], shell);
            ft_putstr_fd(value, 1);
            arg[i] = save;
        }
        else
        {
            write(1, &arg[i], 1);
            i++;
        }
    }
}

/**
 * print_argument - imprime el argumento considerando expansión y comillas
 */
static void print_argument(char *arg, t_shell *shell)
{
    int i;
    int in_single;
    int in_double;

    i = 0;
    in_single = 0;
    in_double = 0;
    while (arg[i])
    {
        if (arg[i] == '\'' && in_double == 0)
        {
            in_single = !in_single;
            i++;
        }
        else if (arg[i] == '"' && in_single == 0)
        {
            in_double = !in_double;
            i++;
        }
        else if (arg[i] == '$' && in_single == 0)
        {
            expand_variable(&arg[i], shell);
            while (arg[i] && arg[i] != ' ')
                i++;
        }
        else
        {
            write(1, &arg[i], 1);
            i++;
        }
    }
}

/**
 * ft_echo - función principal para echo
 */
int ft_echo(t_cmd *cmd, t_shell *shell)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    while (cmd->argv[i] && check_valid_nflag(cmd->argv[i]))
    {
        newline = 0;
        i++;
    }
    while (cmd->argv[i])
    {
        print_argument(cmd->argv[i], shell);
        if (cmd->argv[i + 1])
            write(1, " ", 1);
        i++;
    }
    if (newline)
        write(1, "\n", 1);
    shell->last_status = EXIT_OK;
    return 0;
}
