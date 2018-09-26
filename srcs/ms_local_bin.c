/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_local_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:38:30 by zweng             #+#    #+#             */
/*   Updated: 2018/09/26 19:19:55 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_is_local_bin(char *cmd)
{
	if (!cmd)
		return (FUN_FAIL);
	if (ft_strchr(cmd, '/'))
		return (FUN_SUCS);
	return (FUN_FAIL);
}

int		ms_exec_local_bin(char **argv)
{
	int		status;
	pid_t	pid;

	if (!argv || !*argv)
		return (EXIT_FAILURE);
	if ((pid = fork()) == 0)
	{
		if (execve(argv[0], argv, g_env.tab) < 0)
		{
			if (access(argv[0], F_OK) == -1)
				ms_error("minishell", "no such file or directory", argv[0]);
			else if (access(argv[0], X_OK) == -1)
				ms_error("minishell", "permission denied", argv[0]);
			else
				ms_error("minishell", "execution fail", argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
