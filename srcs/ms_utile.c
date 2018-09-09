/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:42:35 by zweng             #+#    #+#             */
/*   Updated: 2018/09/09 11:42:47 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_printf("%s| size %d\n", *tab, ft_strlen(*tab));
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

void	ms_trim(char *str)
{
	char	*p1;
	char	*p2;

	if (!(p1 = str) || ft_strlen(p1) == 0)
		return ;
	p2 = p1 + ft_strlen(p1) - 1;
	while (p2 >= p1 && (*p2 == '\t' || *p2 == ' ' || *p2 == '\v'))
	{
		*p2 = 0;
		p2--;
	}
	while (*p1 && p1 < p2 && (*p1 == '\t' || *p1 == ' ' || *p1 == '\v'))
		ft_memmove(p1, p1 + 1, ft_strlen(p1));
}

void	ms_argv_relex(char **av)
{
	char	**ptr;
	char	*tmp;

	while (av && *av)
	{
		if (!(ft_strlen(*av) > 0))
		{
			ptr = av + 1;
			while (ptr && *ptr)
			{
				if (ft_strlen(*ptr) > 0)
				{
					tmp = *av;
					*av = *ptr;
					*ptr = tmp;
					break ;
				}
				ptr++;
			}
		}
		av++;
	}
}

int		ms_trim_argv(char **av)
{
	char	**ptr;

	if (!av)
		return (FUN_FAIL);
	ptr = av;
	while (ptr && *ptr)
	{
		ms_trim(*ptr);
		ptr++;
	}
	ms_argv_relex(av);
	return (FUN_SUCS);
}
