/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:19:34 by zweng             #+#    #+#             */
/*   Updated: 2018/10/07 17:00:53 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_basename(const char *filename)
{
	char	*ptr;

	if (!filename)
		return (NULL);
	if (ft_strcmp(filename, "/") == 0)
		return ((char *)filename);
	ptr = ft_strrchr(filename, '/');
	return (ptr ? ptr + 1 : (char *)filename);
}
