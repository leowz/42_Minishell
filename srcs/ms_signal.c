/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:39:20 by zweng             #+#    #+#             */
/*   Updated: 2018/09/09 11:39:32 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_signal_handler(int sig)
{
	ft_printf("received signal is %d\n", sig);
	if (sig == SIGINT)
	{
		ft_printf("catch ctrl-c\n");
		exit(EXIT_SUCCESS);
	}
	else
		ft_printf("catch signal %d\n", sig);
}

void	ms_install_signal_handler(void)
{
	signal(SIGINT, ms_signal_handler);
}
