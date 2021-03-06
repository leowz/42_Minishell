/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_cd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:21:15 by zweng             #+#    #+#             */
/*   Updated: 2018/09/09 11:21:19 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pf_update_env(char *opwd)
{
	char	*cwd;

	if ((cwd = getcwd(NULL, 0)))
	{
		ms_update_entry(&g_env, "PWD", cwd);
		ft_strdel(&cwd);
	}
	ms_update_entry(&g_env, "OLDPWD", opwd);
}

int		ms_change_dir(char *path, int print_path)
{
	char	*cwd;
	int		ret;

	cwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (print_path)
			ft_printf("%s\n", path);
		pf_update_env(cwd);
		ret = EXIT_SUCCESS;
	}
	else
	{
		if (access(path, F_OK) == -1)
			ft_dprintf(STDERR_FILENO, "cd: no such file or directory: %s\n",
					path);
		else if (access(path, R_OK) == -1)
			ft_dprintf(STDERR_FILENO, "cd: permission denied: %s\n", path);
		else
			ft_dprintf(STDERR_FILENO, "cd: not a directory: %s\n", path);
		ret = EXIT_FAILURE;
	}
	ft_strdel(&cwd);
	return (ret);
}

int		ms_builtin_cd(char **argv)
{
	int		size;
	char	*ptr;
	int		ret;

	if (!argv || !*argv)
		return (EXIT_FAILURE);
	size = ms_tab_size(argv);
	if (size == 1 && (ms_search_entry(&g_env, "HOME") >= 0))
	{
		ptr = g_env.tab[ms_search_entry(&g_env, "HOME")];
		ret = ms_change_dir(ft_strchr(ptr, '=') + 1, 0);
	}
	else
	{
		if (ft_strcmp(argv[1], "-") == 0 &&
			(ms_search_entry(&g_env, "OLDPWD") >= 0))
		{
			ptr = g_env.tab[ms_search_entry(&g_env, "OLDPWD")];
			ret = ms_change_dir(ft_strchr(ptr, '=') + 1, 1);
		}
		else
			ret = ms_change_dir(argv[1], 0);
	}
	return (ret);
}
