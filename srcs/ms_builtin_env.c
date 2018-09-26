/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:32:29 by zweng             #+#    #+#             */
/*   Updated: 2018/09/26 19:36:59 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_builtin_env(void)
{
	if (!g_env.tab)
		return (EXIT_FAILURE);
	ms_print_tab(g_env.tab);
	return (EXIT_SUCCESS);
}

int		pf_is_name(const char *str)
{
	if (!str)
		return (FUN_FAIL);
	if (ft_isalpha(*str) || *str == '_')
	{
		while (*str)
		{
			if (!ft_isalpha(*str) && !ft_isdigit(*str) && *str != '_')
				return (FUN_FAIL);
			str++;
		}
		return (FUN_SUCS);
	}
	return (FUN_FAIL);
}

int		ms_builtin_setenv(char **argv)
{
	int		size;
	char	*ptr;

	if (!argv || !*argv)
		return (EXIT_FAILURE);
	size = ms_tab_size(argv);
	if (size == 1)
		ms_print_tab(g_env.tab);
	else if (size == 2)
	{
		if ((ptr = ft_strchr(argv[1], '=')))
		{
			*ptr = 0;
			ms_update_entry(&g_env, argv[1], ptr + 1);
		}
	}
	else if (size > 2 && pf_is_name(argv[1]))
		ms_update_entry(&g_env, argv[1], argv[2]);
	else
	{
		ms_error(argv[0], "not an identifier", argv[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		ms_builtin_unsetenv(char **argv)
{
	int		size;
	int		i;
	int		index;

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
