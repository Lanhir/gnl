/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malibert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 00:59:40 by malibert          #+#    #+#             */
/*   Updated: 2018/12/11 01:13:00 by malibert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strfjoin(char *s1, char *s2)
{
	size_t	lens;
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);		
	len2 = ft_strlen(s2);
	lens = (len1 + len2);
	str = (char *)malloc(sizeof(str) * (lens + 1));
	if (str == 0)
		return (NULL);
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	str[lens + 1] = '\0';
	ft_strdel(&s1);
	return (str);
}

static int	ft_findnl(char **temp, char **line)
{
	char	*add;
	int		nl;
	int		len;

	nl = -1;
	len = ft_strlen(*temp);
	while (++nl < len)
	{
		if (temp[0][nl] == '\n')
		{
			add = ft_strsub(*temp, 0, nl);
			*line = ft_strdup(add);
			ft_strdel(&add);
			add = ft_strsub(*temp, nl + 1, len - nl);
			free(*temp);
			*temp = ft_strdup(add);
			ft_strdel(&add);
			return (1);
		}
	}
	return (0);
}

static void	ft_read(int ret, char *buffer, char **temp)
{
	buffer[ret] = '\0';
	if (*temp)
		*temp = ft_strfjoin(*temp, buffer);
	else
		*temp = ft_strdup(buffer);
}

int			get_next_line(const int fd, char **line)
{
	static char	*temp;
	char		buffer[BUFF_SIZE + 1];
	int			ret;

	if (temp && ft_findnl(&temp, line) == 1)
		return (1);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		ft_read(ret, buffer, &temp);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	if ((ret == -1) || (!line) || (fd < 0))
		return (-1);
	if ((temp) && ft_findnl(&temp, line) == 1)
		return (1);
	if ((ret == 0) && (temp) && (ft_strlen(temp)))
	{
		*line = ft_strdup(temp);
		free(temp);
		temp = NULL;
		return (1);
	}
	return (0);
}
