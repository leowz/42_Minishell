/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:41:29 by zweng             #+#    #+#             */
/*   Updated: 2018/05/04 16:42:01 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ms_is_empty_cmd(char *input)
{
    char    *ptr;
    int     ret;

    if (!input || !(ptr = ft_strtrim(input)))
        return (FUN_SUCS);
    if (ft_strlen(ptr) > 0)
        ret = FUN_FAIL;
    else
        ret = FUN_SUCS;
    ft_strdel(&ptr);
    return (ret);
}

int     ms_exec_command(char *cmd)
{
    char    **argv;
    int     ret;

    ret = EXIT_SUCCESS;
    if ((argv = ms_strsplit(cmd, ' ', "\'\"")) && ms_trim_argv(argv))
    {
        ms_exec_expasion(argv);
        if (ms_is_builtin(argv[0]))
            ret = ms_exec_builtin(argv);
        else if (ms_is_local_bin(argv[0]))
            ret = ms_exec_local_bin(argv);
        else
            ret = ms_exec_global_bin(argv);
        ms_delete_tab(&argv);
    }
    return (ret);
}

int     ms_process_commands(char *input)
{
    char    **cmd_tab;
    char    **tab_ptr;
    int     ret;

    ret = EXIT_SUCCESS;
    if ((cmd_tab = ft_strsplit(input, ';')))
    {
        tab_ptr = cmd_tab;
        while (tab_ptr && *tab_ptr)
        {
            if (!ms_is_empty_cmd(*tab_ptr))
                ret = ms_exec_command(*tab_ptr);
            tab_ptr++;
        }
        ms_delete_tab(&cmd_tab);
    }
    return (ret);
}

void    ms_display_prompt(int ret)
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
    char    *input;
    int     ret;

    (void)ac;
    (void)av;
    ms_init_env(&g_env, environ);
    ms_install_signal_handler();
    ret = EXIT_SUCCESS;
    while (42)
	{
	    ms_display_prompt(ret);
	    if ((get_next_line(STDIN_FILENO, &input) > 0))
        {
            if (!ms_is_empty_cmd(input))
                ret = ms_process_commands(input);
        }
        else
            break ;
	    ft_strdel(&input);
	}
	return (EXIT_SUCCESS);
}
