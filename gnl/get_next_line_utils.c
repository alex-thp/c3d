/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 17:12:36 by ade-temm          #+#    #+#             */
/*   Updated: 2020/03/03 12:57:47 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2, int r)
{
	int		i;
	int		j;
	char	*result;

	i = ft_strlen_gnl(s1);
	j = ft_strlen_gnl(s2);
	if (!(result = ft_calloc_gnl(sizeof(char), (i + j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	free((void*)s1);
	while (s2[j] && j < r)
	{
		result[i + j] = s2[j];
		j++;
	}
	return (result);
}

char	*ft_result(char *result)
{
	int		i;
	char	*ret;

	i = 0;
	while (result[i] != '\n' && result[i])
		i++;
	if (!(ret = ft_calloc_gnl(sizeof(char), (i + 1))))
		return (0);
	i = 0;
	while (result[i] != '\n' && result[i])
	{
		ret[i] = result[i];
		i++;
	}
	return (ret);
}

int		is_n(char *buff)
{
	int		i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_next(char *ret, int r)
{
	int		i;
	int		j;
	char	*result;

	j = is_n(ret);
	i = 0;
	if (j != -1)
		i = j + 1;
	j = ft_strlen_gnl(&ret[i]);
	if (r == 0)
	{
		free(ret);
		return (NULL);
	}
	if (!(result = ft_calloc_gnl(sizeof(char), (j + 1))))
		return (NULL);
	j = 0;
	while (ret[j + i])
	{
		result[j] = ret[j + i];
		j++;
	}
	free(ret);
	return (&result[0]);
}
