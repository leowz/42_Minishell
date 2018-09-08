//
// Created by WENGzhang on 17/08/2018.
//

#include "minishell.h"

void    ms_realloc_env(t_env *env)
{
    char    **tmp;
    int     i;

    i = 0;
    if (!env)
        return ;
    if ((tmp = ft_memalloc(sizeof(char **) * (env->max_size * 2 + 1))))
    {
        while (i < env->max_size)
        {
            tmp[i] = env->tab[i];
            i++;
        }
        free(env->tab);
        env->tab = tmp;
        env->max_size = env->max_size * 2;
    }
}

void    ms_insert_entry(t_env *env, char *line)
{
    if (!env || !line)
        return ;
    if (env->current_size == env->max_size)
        ms_realloc_env(env);
    env->tab[env->current_size] = ft_strdup(line);
    env->current_size++;
}

void    ms_delete_entry(t_env *env, int index)
{
    if (!env || index < 0 || index >= env->current_size)
        return ;
    ft_strdel(env->tab + index);
    ft_memmove(env->tab + index, env->tab + index + 1,
               (env->current_size - index - 1) * sizeof(char **));
    env->current_size--;
    env->tab[env->current_size] = NULL;
}

void    ms_update_entry(t_env *env, const char *name, const char*value)
{
    char    *ptr;
    int     index;

    if (!env || !name)
        return ;
    if ((ptr = ft_strnew(ft_strlen(name) + 1 + ft_strlen(value))))
    {
        ft_strcpy(ptr, name);
        *(ptr + ft_strlen(name)) = '=';
        ft_strcpy(ptr + ft_strlen(name) + 1, value);
        if ((index = ms_search_entry(env, name)) >= 0 &&
                index < env->current_size)
        {
            ft_strdel(env->tab + index);
            env->tab[index] = ft_strdup(ptr);
        }
        else
            ms_insert_entry(env, ptr);
        ft_strdel(&ptr);
    }
}

int     ms_search_entry(t_env *env, const char *name)
{
    int     i;
    char    *ptr;

    if (!env || !name)
        return (-1);
    i = 0;
    while (i < env->current_size && env->tab[i])
    {
        if ((ptr = ft_strstr(env->tab[i], name)) && (ptr == env->tab[i]) &&
                *(ptr + ft_strlen(name)) == '=')
            return (i);
        i++;
    }
    return (-1);
}
