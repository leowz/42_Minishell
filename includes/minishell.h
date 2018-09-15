/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:43:50 by zweng             #+#    #+#             */
/*   Updated: 2018/09/09 11:48:26 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"

# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define BLACK	"\033[1;30m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define PURPLE "\033[1;35m"
# define CYAN	"\033[1;36m"
# define WHITE	"\033[1;37m"
# define EOC	"\033[0;0m"

# define ENV_SIZE	(50)

typedef struct	s_env
{
	int			current_size;
	int			max_size;
	char		**tab;
}				t_env;

t_env			g_env;

int				ms_trim_argv(char **argv);

void			ms_print_tab(char **tab);
int				ms_tab_size(char **tab);
void			ms_delete_tab(char ***tab);
char			*ms_basename(const char *filename);
void			ms_init_env(t_env *env, char **environ);
void			ms_delete_tab(char ***tab);
void			ms_insert_entry(t_env *env, char *line);
void			ms_delete_entry(t_env *env, int index);
int				ms_search_entry(t_env *env, const char *name);
void			ms_update_entry(t_env *env, const char *name, const char*value);
char			*ms_get_env_var(const char *name);
void			ms_exec_expansion(char **argv);
int				ms_is_builtin(const char *cmd);
int				ms_exec_builtin(char **argv, int status);
void			ms_setenv(char *key, char *value);
void			ms_error(const char *cmd, const char *msg, const char *cause);
void			ms_die(int status);
int				ms_is_exit(char *line);
char			**ms_strsplit(char const *s, char c, char *quote);
void			ms_builtin_exit(char **argv, int status);
int				ms_builtin_echo(char **argv);
int				ms_builtin_env(void);
int				ms_builtin_pwd(void);
int				ms_builtin_setenv(char **argv);
int				ms_builtin_unsetenv(char **argv);
int				ms_builtin_cd(char **argv);
int				ms_is_local_bin(char *cmd);
int				ms_exec_local_bin(char **argv);
int				ms_exec_global_bin(char **argv);
#endif
