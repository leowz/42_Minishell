/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:09:04 by zweng             #+#    #+#             */
/*   Updated: 2018/10/07 12:43:43 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		ms_display_prompt(EXIT_FAILURE);
		signal(SIGINT, ms_signal_handler);
	}
}

void	ms_proc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, ms_proc_signal_handler);
	}
}
