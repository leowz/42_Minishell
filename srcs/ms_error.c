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

void	ms_error(const char *cmd, const char *msg, const char *cause)
{
	if (!msg || !cmd || !cause)
		return ;
	ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", cmd, msg, cause);
}

void	ms_die(int status)
{
	exit(status);
}

int		ms_is_exit(char *line)
{
	if (!line)
		return (FUN_SUCS);
	return (ft_strcmp(line, "exit") == 0);
}
