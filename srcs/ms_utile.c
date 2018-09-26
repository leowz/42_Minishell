/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:42:35 by zweng             #+#    #+#             */
/*   Updated: 2018/09/26 19:18:42 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_trim(char *str)
{
	char	*p1;

	if (!(p1 = str) || ft_strlen(p1) == 0)
		return ;
	while (*p1 && (*p1 == '\t' || *p1 == ' ' || *p1 == '\v'))
	{
		if (ft_strlen(p1 + 1) == 0)
			return ;
		else
			ft_strcpy(p1, p1 + 1);
	}
}

int		pf_need_change(char *str)
{
	if (!str || !(ft_strlen(str) > 0))
		return (1);
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\v')
			return (0);
		str++;
	}
	return (1);
}

void	ms_argv_relex(char **av)
{
	char	**ptr;
	char	*tmp;

	while (av && *av)
	{
		if (pf_need_change(*av))
		{
			ptr = av + 1;
			while (ptr && *ptr)
			{
				if (!pf_need_change(*ptr))
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

void	ms_argv_remove(char **av)
{
	char	**ptr;

	if (!av)
		return ;
	ptr = av;
	while (*ptr && !(pf_need_change(*ptr)))
		ptr++;
	while (*ptr)
	{
		ft_strdel(ptr);
		ptr++;
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
	ms_argv_remove(av);
	return (FUN_SUCS);
}
