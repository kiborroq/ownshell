/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 12:23:53 by kiborroq          #+#    #+#             */
/*   Updated: 2021/02/01 23:24:00 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static int	find_lb(char *str, size_t *to_lb)
{
	size_t	lb;

	if (!str)
		return (0);
	lb = *to_lb;
	while (str[lb] != '\n' && str[lb])
		lb++;
	*to_lb = lb;
	if (str[lb] == '\n')
		return (1);
	return (0);
}

static char	*ft_strjoin_wrapper(char *save, char *buf)
{
	char *s_b;

	s_b = ft_strjoin(save, buf);
	free(save);
	if (!s_b)
		return (0);
	return (s_b);
}

static char	*get_line(char *save, size_t to_lb)
{
	char *l;

	if (!(l = (char *)malloc((to_lb + 1) * sizeof(char))))
		return (0);
	ft_memcpy(l, save, to_lb);
	l[to_lb] = '\0';
	return (l);
}

int			get_next_line(int fd, char **line)
{
	char		*buf;
	static char *save;
	size_t		to_lb;
	int			readed;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	if (!(buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	readed = 1;
	to_lb = 0;
	while (!find_lb(save, &to_lb) && (readed = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[readed] = '\0';
		if (!(save = ft_strjoin_wrapper(save, buf)))
			return (-1);
	}
	free(buf);
	if (readed == -1 || !(*line = get_line(save, to_lb)))
		return (-1);
	free(save);
	save = NULL;
	if (readed == 0)
		return (0);
	return (1);
}
