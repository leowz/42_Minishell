//
// Created by WENGzhang on 18/08/2018.
//

#include "minishell.h"

void    ms_error(const char *msg)
{
    if (!msg)
        return ;
    ft_dprintf(STDERR_FILENO, "minishell: %s\n", msg);
}

void    ms_die(int status)
{
    exit(status);
}

void    ms_error_and_die(const char *msg, int status)
{
    if (!msg)
        return ;
    ms_error(msg);
    ms_die(status);
}

int     ms_is_exit(char *line)
{
    if (!line)
        return (FUN_SUCS);
    return (ft_strcmp(line, "exit") == 0);
}

