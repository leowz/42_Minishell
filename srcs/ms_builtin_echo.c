//
// Created by WENGzhang on 19/08/2018.
//

#include "minishell.h"

int ms_builtin_echo(char **argv)
{
    int n_flag;
    int size;
    int i;

    n_flag = 0;
    if (!argv || !*argv)
        return (EXIT_FAILURE);
    size = ms_tab_size(argv);
    if (size > 1)
    {
        i = 1;
        while (i < size)
        {
            if (i == 1 && ft_strcmp(argv[1], "-n") == 0)
                n_flag = 1;
            else
                {
                ft_printf("%s", argv[i]);
                if (i < size - 1)
                    ft_printf(" ");
                }
            i++;
        }
    }
    if (n_flag == 0)
        ft_printf("\n");
    return (EXIT_SUCCESS);
}