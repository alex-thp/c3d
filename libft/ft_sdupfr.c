/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sdupfr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:05:40 by thverney          #+#    #+#             */
/*   Updated: 2020/03/03 11:37:43 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*sdupfr(char *s1, size_t n)
{
	int		i;
	char	*dest;

	i = 0;
	while (s1[i])
		i++;
	if (!(dest = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		dest[i] = s1[i];
	dest[i] = '\0';
	n == 1 ? free(s1) : 1;
	return (dest);
}
