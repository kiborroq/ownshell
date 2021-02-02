/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 16:51:47 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/31 19:11:51 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t i;
	size_t num;

	i = 0;
	num = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			num++;
		while (s[i] != c && s[i])
			i++;
	}
	return (num);
}

static char		*fill_word(char *s, char c)
{
	size_t	word_len;
	char	*word;

	word_len = 0;
	while (s[word_len] != c && s[word_len])
		word_len++;
	if (!(word = ft_substr(s, 0, word_len)))
		return (0);
	return (word);
}

static void		free_strs(char **strs, unsigned int n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char		**fill_strs(char *s, char c, unsigned int num_words)
{
	char	**strs;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(strs = (char **)ft_calloc(num_words + 1, sizeof(char *))))
		return (0);
	while (j < num_words && s[i])
	{
		while (s[i] == c)
			i++;
		if (!(strs[j] = fill_word(&s[i], c)))
		{
			free_strs(strs, j);
			return (0);
		}
		if (s[i])
			j++;
		while (s[i] != c && s[i])
			i++;
	}
	return (strs);
}

char			**ft_split(char const *s, char c)
{
	size_t	num_words;
	char	**strs;

	if (!s)
		return (0);
	num_words = count_words(s, c);
	if (!(strs = fill_strs((char *)s, c, num_words)))
		return (0);
	return (strs);
}
