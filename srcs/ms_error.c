/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:34:55 by zweng             #+#    #+#             */
/*   Updated: 2018/09/09 11:35:07 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_error(const char *msg)
{
	if (!msg)
		return ;
	ft_dprintf(STDERR_FILENO, "minishell: %s\n", msg);
}

void	ms_die(int status)
{
	exit(status);
}

void	ms_error_and_die(const char *msg, int status)
{
	if (!msg)
		return ;
	ms_error(msg);
	ms_die(status);
}

int		ms_is_exit(char *line)
{
	if (!line)
		return (FUN_SUCS);
	return (ft_strcmp(line, "exit") == 0);
}
