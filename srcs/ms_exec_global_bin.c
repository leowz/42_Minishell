/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_global_bin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:37:16 by zweng             #+#    #+#             */
/*   Updated: 2018/09/09 11:38:14 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_is_gbin_exist(char *cmd, char *path)
{
	DIR				*dirp;
	struct dirent	*dp;

	if (!cmd || !path)
		return (FUN_SUCS);
	if ((dirp = opendir(path)))
	{
		while ((dp = readdir(dirp)))
		{
			if (ft_strcmp(dp->d_name, cmd) == 0)
			{
				(void)closedir(dirp);
				return (FUN_SUCS);
			}
		}
		(void)closedir(dirp);
	}
	return (FUN_FAIL);
}

int		ms_add_cmd_path(char **argv, char *path)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!path)
		return (FUN_FAIL);
	if ((tmp = ft_strnew(ft_strlen(argv[0]) + ft_strlen(path) + 1)))
	{
		ft_strcpy(tmp, path);
		tmp[ft_strlen(path)] = '/';
		ft_strcpy(tmp + ft_strlen(path) + 1, argv[0]);
		free(argv[0]);
		argv[0] = tmp;
		return (FUN_SUCS);
	}
	return (FUN_FAIL);
}

char	*ms_get_env_var(const char *name)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (!name)
		return (ret);
	if ((i = ms_search_entry(&g_env, name)) >= 0 && i < g_env.current_size)
	{
		ret = g_env.tab[i];
		return (ft_strchr(ret, '=') + 1);
	}
	return (ret);
}

int		ms_exec_global_bin(char **argv)
{
	int		i;
	char	**path;

	i = 0;
	if (!argv || !*argv || !(ft_strlen(argv[0]) > 0) ||
		!(path = ft_strsplit(ms_get_env_var("PATH"), ':')))
		return (EXIT_FAILURE);
	while (path && path[i])
	{
		if (ms_is_gbin_exist(argv[0], path[i]) &&
				ms_add_cmd_path(argv, path[i]))
		{
			ms_delete_tab(&path);
			return (ms_exec_local_bin(argv));
		}
		i++;
	}
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
			"command not found", argv[0]);
	ms_delete_tab(&path);
	return (EXIT_FAILURE);
}
