/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:08:32 by thverney          #+#    #+#             */
/*   Updated: 2019/10/16 19:27:25 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*temp;
	size_t	res;

	res = count * size;
	if (!(temp = (char*)malloc(sizeof(char) * res)))
		return (NULL);
	ft_bzero(temp, res);
	return (temp);
}
