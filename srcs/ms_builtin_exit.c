/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:33:13 by zweng             #+#    #+#             */
/*   Updated: 2018/09/09 11:33:15 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_builtin_exit(void)
{
	ft_printf("%s\n", "Bye~");
	ms_die(EXIT_SUCCESS);
}

int		ms_builtin_pwd(void)
{
	char	*ptr;
	int		ret;

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
