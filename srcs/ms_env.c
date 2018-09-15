/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:33:34 by zweng             #+#    #+#             */
/*   Updated: 2018/09/09 11:33:37 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_init_env(t_env *env, char **environ)
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

void	ms_delete_tab(char ***tab)
{
	char	**tab_t;

	if (!tab || !*tab)
		return ;
	tab_t = *tab;
	while (tab_t && *tab_t)
	{
		free(*tab_t);
		tab_t++;
	}
	free(*tab);
	*tab = NULL;
}

void	ms_print_tab(char **tab)
{
	while (tab && *tab)
	{
		ft_printf("%s\n", *tab);
		tab++;
	}
}

int		ms_tab_size(char **tab)
{
	int ret;

	ret = 0;
	if (tab && *tab)
	{
		while (tab[ret])
			ret++;
	}
	return (ret);
}
