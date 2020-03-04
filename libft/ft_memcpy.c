/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:48:13 by ade-temm          #+#    #+#             */
/*   Updated: 2020/02/26 13:06:38 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (src || dst)
	{
		while (i < n)
		{
			((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
			i++;
		}
		return (dst);
	}
	return (0);
}
