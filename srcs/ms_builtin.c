//
// Created by WENGzhang on 17/08/2018.
//

#include "minishell.h"

int     ms_is_builtin(const char *cmd)
{
    if (!cmd)
        return (FUN_FAIL);
    if ((ft_strcmp(cmd, "exit") == 0) || (ft_strcmp(cmd, "echo") == 0) ||
            (ft_strcmp(cmd, "cd") == 0) || (ft_strcmp(cmd, "setenv") == 0) ||
            (ft_strcmp(cmd, "unsetenv") == 0) || (ft_strcmp(cmd, "env") == 0) ||
            (ft_strcmp(cmd, "pwd") == 0))
        return (FUN_SUCS);
    return (FUN_FAIL);
}

int     ms_exec_builtin(char **argv)
{
    int     ret;

    ret = EXIT_SUCCESS;
    if (!argv && !argv[0])
        return (EXIT_FAILURE);
    if (ft_strcmp(argv[0], "exit") == 0)
        ms_builtin_exit();
    else if (ft_strcmp(argv[0], "echo") == 0)
        ret = ms_builtin_echo(argv);
    else if (ft_strcmp(argv[0], "cd") == 0)
        ret = ms_builtin_cd(argv);
    else if (ft_strcmp(argv[0], "setenv") == 0)
        ret = ms_builtin_setenv(argv);
    else if (ft_strcmp(argv[0], "unsetenv") == 0)
        ret = ms_builtin_unsetenv(argv);
    else if (ft_strcmp(argv[0], "pwd") == 0)
        ret = ms_builtin_pwd();
    else if (ft_strcmp(argv[0], "env") == 0)
        ret = ms_builtin_env();
    else
        ret = EXIT_FAILURE;
    return (ret);
}
