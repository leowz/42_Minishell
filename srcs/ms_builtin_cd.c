//
// Created by WENGzhang on 19/08/2018.
//

#include "minishell.h"

int     ms_change_dir(char *path, int print_path)
{
    char	*cwd;
    int     ret;

    cwd = getcwd(NULL, 0);
    if (!chdir(path))
    {
        if (print_path)
            ft_printf("%s\n", path);
        ms_update_entry(&g_env, "OLDPWD", cwd);
        ret = EXIT_SUCCESS;
    }
    else
    {
        if (access(path, F_OK) == -1)
            ft_dprintf(STDERR_FILENO, "cd: no such file or directory: %s\n", path);
        else if (access(path, R_OK) == -1)
            ft_dprintf(STDERR_FILENO, "cd: permission denied: %s\n", path);
        else
            ft_dprintf(STDERR_FILENO, "cd: not a directory: %s\n", path);
        ret = EXIT_FAILURE;
    }
    ft_strdel(&cwd);
    return (ret);
}

int     ms_builtin_cd(char **argv)
{
    int     size;
    char    *ptr;
    int     ret;

    if (!argv || !*argv)
        return (EXIT_FAILURE);
    size = ms_tab_size(argv);
    if (size == 1 && (ms_search_entry(&g_env, "HOME") >= 0))
    {
        ptr = g_env.tab[ms_search_entry(&g_env, "HOME")];
        ret = ms_change_dir(ft_strchr(ptr, '=') + 1, 0);
    }
    else
    {
        if (ft_strcmp(argv[1], "-") == 0 &&
            (ms_search_entry(&g_env, "OLDPWD") >= 0))
        {
            ptr = g_env.tab[ms_search_entry(&g_env, "OLDPWD")];
            ret = ms_change_dir(ft_strchr(ptr, '=') + 1, 1);
        }
        else
            ret = ms_change_dir(argv[1], 0);
    }
    return (ret);
}
