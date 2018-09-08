//
// Created by WENGzhang on 15/08/2018.
//

#include "minishell.h"

char    *ms_basename(const char *filename)
{
    char    *ptr;

    if (!filename)
        return (NULL);
    ptr = ft_strrchr(filename, '/');
    return (ptr ? ptr + 1 : (char *)filename);
}
