/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:54:42 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/03 15:25:04 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

t_color get_color(char *str)
{
	int		j;
	t_color	res;

	j = 0;
	res.red = ft_atoi(str[j + 1]);
	while (str[j] != ',')
		j++;
	res.green = ft_atoi(str[j + 1]);
	j++;
	while (str[j] != ',')
		j++;
	res.blue = ft_atoi(str[j + 1]);
	return (res);
}

t_map	parse_map(char **av)
{
	int		i;
	int		j;
	int		fd;
	char	*tab;
	t_map	res;

	i = 1;
	res.map = malloc(1);
	res.map[0] = 0;
	res.hauteur = 0;
	fd = open(av[1], O_RDONLY);
	while (i > 0)
	{
		j = 0;
		i = get_next_line(fd, &tab);
		if (tab[0] == 'R')
		{
			while (ft_is_digit(tab[j]) == 0)
				j++;
			res.size_x = ft_atoi(tab[j]);
			while (ft_is_digit(tab[j]) == 1)
				j++;
			while (ft_is_digit(tab[j]) == 0)
				j++;
			res.size_y = ft_atoi(tab[j]);
		}
		if (tab[0] == 'F')
			res.floor = get_color(tab);
		if (tab[0] == 'C')
			res.plafond = get_color(tab);
		else if (ft_is_digit(tab[0]) == 1)
		{
			res.largeur = ft_strlen(tab);
			res.map = ft_strjoin(res.map, tab, 2147483647);
			free(tab);
			res.hauteur += 1;
		}
	}
	return (res);
}

int		print_map(t_map tab)
{
	int i;

	i = 0;
	while (i < tab.largeur * tab.hauteur)
	{
		if (i % tab.largeur == 0 && i != 0)
			ft_putchar('\n');
		if (i == tab.pos)
			ft_putchar('H');
		else
			ft_putchar(tab.map[i]);
		i++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_map	*map;
	int		i;

	if (!(map = (t_map*)malloc(sizeof(t_map))))
		return (-1);
	i = 0;
	if (ac != 1)
		*map = parse_map(av);
	map->pos = 6;
	print_map(*map);
}