/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtyree <vtyree@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 18:01:34 by vtyree            #+#    #+#             */
/*   Updated: 2021/11/10 15:58:50 by vtyree           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_update_array(char *arr)
{
	char	*temp;
	char	*next_line;

	if (!arr)
		return (NULL);
	next_line = ft_strchr(arr, '\n');
	if (next_line)
	{
		temp = ft_strdup(next_line);
		free(arr);
		arr = temp;
	}
	else if (arr[0] == 0)
	{
		free(arr);
	}
	else
	{
		free(arr);
		arr = NULL;
	}
	return (arr);
}

static char	*ft_output(char *arr)
{
	char	*out;
	char	*next_line;

	if (!arr)
		return (NULL);
	next_line = ft_strchr(arr, '\n');
	if (next_line)
	{
		out = ft_substr(arr, 0, next_line - arr);
	}
	else if (arr[0] == 0)
	{
		out = NULL;
	}
	else
	{
		out = ft_strdup(arr);
	}
	return (out);
}

char	*get_next_line(int fd)
{
	static char		*arr;
	char			buf[BUFFER_SIZE + 1];
	char			*out;
	char			*temp;
	int				ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (arr == NULL)
			arr = ft_strdup("");
		temp = ft_strjoin(arr, buf);
		free(arr);
		arr = temp;
		if (ft_strchr(buf, '\n'))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
	out = ft_output(arr);
	arr = ft_update_array(arr);
	return (out);
}
