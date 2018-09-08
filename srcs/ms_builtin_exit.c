//
// Created by WENGzhang on 18/08/2018.
//

#include "minishell.h"

void    ms_builtin_exit(void)
{
    ft_printf("%s\n", "Bye~");
    ms_die(EXIT_SUCCESS);
}

int     ms_builtin_pwd(void)
{
    char    *ptr;
    int     ret;

    if ((ptr = getcwd(NULL, 0)))
    {
        ft_printf("%s\n", ptr);
        ft_strdel(&ptr);
        ret = EXIT_SUCCESS;
    }
    else
    {
        ms_error("Error cwd NULL");
        ret = EXIT_FAILURE;
    }
    return (ret);
}
