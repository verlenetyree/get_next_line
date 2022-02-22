/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtyree <vtyree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:01:34 by vtyree            #+#    #+#             */
/*   Updated: 2021/11/10 17:32:38 by vtyree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_output(int fd, char **arr)
{
	char	*out;
	char	*temp;
	char	*next_line;

	next_line = ft_strchr(arr[fd], '\n');
	if (next_line)
	{
		out = ft_substr(arr[fd], 0, next_line - arr[fd]);
		temp = ft_strdup(next_line);
		free(arr[fd]);
		arr[fd] = temp;
	}
	else if (arr[fd][0] == 0)
	{
		free(arr[fd]);
        arr[fd] = NULL;
        out = NULL;
	}
	else
	{
		out = ft_strdup(arr[fd]);
		free(arr[fd]);
		arr[fd] = NULL;
	}
	return (out);
}

char	*get_next_line(int fd)
{
	static char		*arr[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	char			*temp;
	int				ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (arr[fd] == NULL)
			arr[fd] = ft_strdup("");
		temp = ft_strjoin(arr[fd], buf);
		free(arr[fd]);
		arr[fd] = temp;
		if (ft_strchr(buf, '\n'))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	if (arr[fd] == NULL)
		return (NULL);
	return (ft_output(fd, arr));
}
