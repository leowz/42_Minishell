/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:21:42 by zweng             #+#    #+#             */
/*   Updated: 2018/09/09 11:31:36 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pf_print(int size, char **argv)
{
	int n_flag;
	int i;

	n_flag = 0;
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
}

int		ms_builtin_echo(char **argv)
{
	int size;

	if (!argv || !*argv)
		return (EXIT_FAILURE);
	size = ms_tab_size(argv);
	pf_print(size, argv);
	return (EXIT_SUCCESS);
}
