//
// Created by WENGzhang on 16/08/2018.
//

#include "minishell.h"

void    ms_init_env(t_env *env, char **environ)
{
    if (!env)
        return ;
    if ((env->tab = ft_memalloc(sizeof(char *) * (ENV_SIZE + 1))))
    {
        env->current_size = 0;
        env->max_size = ENV_SIZE;
        while (environ && *environ)
        {
            ms_insert_entry(env, *environ);
            environ++;
        }
    }
}
