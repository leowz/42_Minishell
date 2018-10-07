/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:18:54 by zweng             #+#    #+#             */
/*   Updated: 2018/10/07 12:42:23 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ms_is_empty_cmd(char *input)
{
	char	*ptr;
	int		ret;

	if (!input || !(ptr = ft_strtrim(input)))
		return (FUN_SUCS);
	if (ft_strlen(ptr) > 0)
		ret = FUN_FAIL;
	else
		ret = FUN_SUCS;
	ft_strdel(&ptr);
	return (ret);
}

int		ms_exec_command(char *cmd, int status)
{
	char	**argv;
	int		ret;

	ret = EXIT_SUCCESS;
	signal(SIGINT, ms_proc_signal_handler);
	if ((argv = ms_strsplit(cmd, ' ', "\'\"")) && ms_trim_argv(argv))
	{
		ms_exec_expansion(argv);
		if (ms_is_builtin(argv[0]))
			ret = ms_exec_builtin(argv, status);
		else if (ms_is_local_bin(argv[0]))
			ret = ms_exec_local_bin(argv);
		else
			ret = ms_exec_global_bin(argv);
		ms_delete_tab(&argv);
	}
	return (ret);
}

int		ms_process_commands(char *input, int status)
{
	char	**cmd_tab;
	char	**tab_ptr;
	int		ret;

	ret = EXIT_SUCCESS;
	if ((cmd_tab = ft_strsplit(input, ';')))
	{
		tab_ptr = cmd_tab;
		while (tab_ptr && *tab_ptr)
		{
			if (!ms_is_empty_cmd(*tab_ptr))
				ret = ms_exec_command(*tab_ptr, status);
			tab_ptr++;
		}
		ms_delete_tab(&cmd_tab);
	}
	return (ret);
}

void	ms_display_prompt(int ret)
{
	char *ptr;

	ptr = getcwd(NULL, 0);
	if (ret == EXIT_SUCCESS)
		ft_printf("😄 %s➡︎%s %s%s%s ", GREEN, EOC, CYAN, ms_basename(ptr), EOC);
	else
		ft_printf("😡 %s➡︎%s %s%s%s ", RED, EOC, CYAN, ms_basename(ptr), EOC);
	ft_strdel(&ptr);
}

int		main(int ac, char **av, char **environ)
{
	char	*input;
	int		ret;

	(void)ac;
	(void)av;
	ms_init_env(&g_env, environ);
	ret = EXIT_SUCCESS;
	while (42)
	{
		ms_display_prompt(ret);
		signal(SIGINT, ms_signal_handler);
		if ((get_next_line(STDIN_FILENO, &input) > 0))
		{
			if (!ms_is_empty_cmd(input))
				ret = ms_process_commands(input, ret);
		}
		else
			break ;
		ft_strdel(&input);
	}
	return (EXIT_SUCCESS);
}
