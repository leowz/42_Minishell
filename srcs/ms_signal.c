//
// Created by WENGzhang on 18/08/2018.
//

#include "minishell.h"

void    ms_signal_handler(int sig)
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

void    ms_install_signal_handler(void)
{
    signal(SIGINT, ms_signal_handler);
}

