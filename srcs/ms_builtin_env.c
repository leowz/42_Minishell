//
// Created by WENGzhang on 19/08/2018.
//

#include "minishell.h"

int     ms_builtin_env(void)
{
    if (!g_env.tab)
        return (EXIT_FAILURE);
    ms_print_tab(g_env.tab);
    return (EXIT_SUCCESS);
}

int     ms_builtin_setenv(char **argv)
{
    int     size;
    char    *ptr;

    if (!argv || !*argv)
        return (EXIT_FAILURE);
    size = ms_tab_size(argv);
    if (size == 2 && (ptr = ft_strchr(argv[1], '=')))
    {
        *ptr = 0;
        ms_update_entry(&g_env, argv[1], ptr + 1);
    }
    else if (size > 2)
        ms_update_entry(&g_env, argv[1], argv[2]);
    return (EXIT_SUCCESS);
}

int     ms_builtin_unsetenv(char **argv)
{
    int     size;
    int     i;
    int     index;

    if (!argv || !*argv)
        return (EXIT_FAILURE);
    size = ms_tab_size(argv);
    i = 1;
    while (i < size)
    {
        if ((index = ms_search_entry(&g_env, argv[i])) >= 0 &&
                index < g_env.current_size)
        {
            ms_delete_entry(&g_env, index);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}


