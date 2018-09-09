/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zweng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 11:40:09 by zweng             #+#    #+#             */
/*   Updated: 2018/09/09 11:41:12 by zweng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		pf_quote_contains(char const *s, char *quote)
{
	int			i;

	i = 0;
	if (!s || !quote)
		return (-1);
	while (quote[i])
	{
		if (ft_strchr(s, quote[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int		pft_count_word(char const *s, char c, char *quote)
{
	int			counted;
	int			ret;
	int			in_quote;

	counted = 0;
	ret = 0;
	in_quote = -1;
	while (*s)
	{
		if (*s != c && !counted && (in_quote < 0))
		{
			ret++;
			counted = 1;
		}
		if (*s == c && counted && (in_quote < 0))
			counted = 0;
		if (in_quote >= 0 && *s == quote[in_quote])
			in_quote = -1;
		if (in_quote < 0 && (ft_strchr(quote, *s)) && (ft_strchr(s + 1, *s)))
			in_quote = ft_strchr(quote, *s) - quote;
		s++;
	}
	return (ret);
}

static void		pf_remove_quote(char **str, char *quote)
{
	char	*ptr;
	char	*p1;
	char	*p2;

	if (!str || !*str || !quote)
		return ;
	ptr = *str;
	while (*ptr)
	{
		if ((ft_strchr(quote, *ptr)) && (p2 = ft_strchr(ptr + 1, *ptr)))
		{
			p1 = ptr;
			ft_strcpy(p2, p2 + 1);
			ft_strcpy(p1, p1 + 1);
			return ;
		}
		ptr++;
	}
}

static char		*pft_next_word(char const **s, char c, char *quote)
{
	char const	*tp;
	char		*ret;
	int			in_quote;

	in_quote = -1;
	while (**s == c)
		(*s)++;
	tp = *s;
	while (*tp && (*tp != c || in_quote >= 0))
	{
		if (in_quote >= 0 && *tp == quote[in_quote])
			in_quote = -1;
		if (in_quote < 0 && (ft_strchr(quote, *tp)) &&
				(ft_strchr(tp + 1, *tp)))
			in_quote = ft_strchr(quote, *tp) - quote;
		tp++;
	}
	if ((ret = ft_strsub(*s, 0, tp - *s)) &&
			(pf_quote_contains(ret, quote) >= 0))
		pf_remove_quote(&ret, quote);
	*s = tp;
	return (ret);
}

char			**ms_strsplit(char const *s, char c, char *quote)
{
	char		**ret;
	char		**tp;
	int			word_count;

	ret = 0;
	if (!s)
		return (0);
	if (!quote || (ft_strlen(quote) == 0) || (pf_quote_contains(s, quote) < 0))
		return (ft_strsplit(s, c));
	word_count = pft_count_word(s, c, quote);
	if ((ret = ft_memalloc(sizeof(char *) * (word_count + 1))))
	{
		tp = ret;
		while (word_count--)
			*tp++ = pft_next_word(&s, c, quote);
		*tp = 0;
	}
	return (ret);
}
