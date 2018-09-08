//
// Created by WENGzhang on 17/08/2018.
//

#include "minishell.h"

void    ms_expande_tilde(char **param)
{
    char    *ptr;
    char    *tmp;
    int     size;

    tmp = NULL;
    if (!param || !*param)
        return ;
    if (param[0][0] == '~')
    {
        size = ft_strlen(*param + 1);
        if ((ptr = ms_get_env_var("HOME")))
            size += ft_strlen(ptr);
        if ((tmp = ft_strnew(size)))
        {
            ft_strcpy(tmp, ptr);
            ft_strcat(tmp, *param + 1);
            free(*param);
            *param = tmp;
        }
    }
}

void ms_expande_param(char **param)
{
    char    *ptr;
    char    *tmp;
    char    *name;
    int     size;

    tmp = NULL;
    if (!param || !*param)
        return ;
    if ((name = ft_strchr(*param, '$')) && ft_strlen(name) > 1)
    {
        size = ft_strlen(*param) - ft_strlen(name);
        if ((ptr = ms_get_env_var(name + 1)))
            size += ft_strlen(ptr);
        if ((tmp = ft_strnew(size)))
        {
            ft_strcpy(tmp, *param);
            ft_strcpy(tmp + (ft_strlen(*param) - ft_strlen(name)), ptr);
            free(*param);
            *param = tmp;
        }
    }
}

void ms_exec_expasion(char **argv)
{
    int     i;

    i = 1;
    if (!argv || !*argv || !argv[1])
        return ;
    while (argv && argv[i])
    {
        if (argv[i][0] == '~')
            ms_expande_tilde(argv + i);
        if (ft_strchr(argv[i], '$'))
            ms_expande_param(argv + i);
        i++;
    }
}


