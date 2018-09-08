//
// Created by WENGzhang on 01/09/2018.
//

#include "minishell.h"

int     ms_is_local_bin(char *cmd)
{
    if (!cmd)
        return (FUN_FAIL);
    if (ft_strchr(cmd, '/'))
        return (FUN_SUCS);
    return (FUN_FAIL);
}

int    ms_exec_local_bin(char **argv)
{
    int     status;
    pid_t   pid;

    if (!argv || !*argv)
        return (EXIT_FAILURE);
    if ((pid = fork()) == 0)
    {
        if (execve(argv[0], argv, g_env.tab) < 0)
        {
            ft_printf("%s: Command not found.\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (EXIT_FAILURE);
}
