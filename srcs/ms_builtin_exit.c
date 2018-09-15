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

int     pf_is_numeric(char *str)
{
    if (!str)
        return (FUN_FAIL);
    while (*str)
    {
        if (!ft_isdigit(*str))
        	return (FUN_FAIL);
		str++;
    }
    return (FUN_SUCS);
}

void	ms_builtin_exit(char **argv, int status)
{
    int     size;

	if (!argv || !*argv)
		return ;
	size = ms_tab_size(argv);
	if (size <= 2)
	{
		ft_printf("%s\n", "Bye~");
		if (size == 2) {
			if (pf_is_numeric(argv[1]))
				ms_die(ft_atoi(argv[1]));
			else
			{
				ms_error("exit", "numeric argument required", argv[1]);
				ms_die(EXIT_FAILURE);
			}
		}
		ms_die(status);
	}
	else
		ms_error("exit", "too many arguments", "");
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
		ft_dprintf(STDERR_FILENO, "pwd: cwd NULL\n");
		ret = EXIT_FAILURE;
	}
	return (ret);
}
