/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_doc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 09:47:03 by ade-temm          #+#    #+#             */
/*   Updated: 2020/03/04 10:35:08 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "gnl/get_next_line.h"
#include <stdio.h>

int     is_whitespace(char c)
{
    if (c == 32 || c == 9 || (c <= 13 && c >= 11))
        return (0);
    return (1);
}

int     ft_is_num(char c)
{
    if (c > 47 && c < 58)
        return (1);
    return (0);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 || s2)
	{
		while ((unsigned char)s1[i] && (unsigned char)s2[i] && i < n)
		{
			if ((unsigned char)s1[i] != (unsigned char)s2[i])
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			i++;
		}
		if (i == n)
			return (0);
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

void    parse_resolution(char *str, t_map *tab)
{
    if (tab->doc->res == 1)
        ft_error(-1);
    tab->doc->res_x = ft_atoi(str + 1);
    while (*(str + 1) != ' ')
        str++;
    while (ft_is_num(*(str + 1)) == 0)
        str++;
    while (ft_is_num(*(str + 1)) == 1)
        str++;
    tab->doc->res_y = ft_atoi(str + 1);
    if (tab->doc->res_x <= tab->doc->res_y || !tab->doc->res_x || !tab->doc->res_y)
        ft_error(0);
    tab->doc->res = 1;
}

void    parse_texture(char *str, t_map *tab, int i)
{
    char    *text;

    text = ft_strdup(str);
    while (is_whitespace(*(text)) == 0)
        text++;
    text += 2;
    while (is_whitespace(*(text)) == 0)
        text++;
    if (i == 1)
    {
        if (tab->doc->NO)
            ft_error(11);
        tab->doc->NO = (text + 2);
    }
    else if (i == 2)
    {
        if (tab->doc->SO)
            ft_error(11);
        tab->doc->SO = (text + 2);
    }
    else if (i == 3)
    {
        if (tab->doc->WE)
            ft_error(11);
        tab->doc->WE = (text + 2);
    }
    else if (i == 4)
    {
        if (tab->doc->EA)
            ft_error(11);
        tab->doc->EA = (text + 2);
    }
    else if (i == 5)
    {
        if (tab->doc->S)
            ft_error(11);
        tab->doc->S = (text + 2);
    }
}


int     what_is_it(char *str)
{
    while (is_whitespace(*str) == 0)
        str++;
    if (ft_strncmp(str, "R", 1) == 0)
        return (0);
    else if (ft_strncmp(str, "NO", 2) == 0)
        return (1);
    else if (ft_strncmp(str, "SO", 2) == 0)
        return (2);
    else if (ft_strncmp(str, "WE", 2) == 0)
        return (3);
    else if (ft_strncmp(str, "EA", 2) == 0)
        return (4);
    else if (ft_strncmp(str, "S", 1) == 0)
        return (5);
    else if (ft_strncmp(str, "F", 1) == 0)
        return (6);
    else if (ft_strncmp(str, "C", 1) == 0)
        return (7);
    else //Verifier que ça fonctionne bien
    {
        while (*str && ft_is_num(*str) == 0)
            str++;
        if (ft_is_num(*str) == 1)
            return (8);
    }
    //Ici la fonction check que mes donnes ont bien ete collectees et sont exactes
    return (-1);
}

t_color    ft_parse_color(t_color stuff, char *str)
{
    str += 1;
    while (*str == ' ')
        str++;
    stuff.red = ft_atoi(str);
    while (ft_is_num(*str) == 1)
        str++;
    while (ft_is_num(*str) == 0)
        str++;
    stuff.green = ft_atoi(str);
    while (ft_is_num(*str) == 1)
        str++;
    while (ft_is_num(*str) == 0)
        str++;
    stuff.blue = ft_atoi(str);
    return (stuff);
}

void    parse_map(t_map *tab, char *line)
{
    char *tmp;
    if (!(tab->doc->map))
    {
        tab->doc->map = malloc(1);
        tab->doc->map[0] = 0;
    }
    tmp = ft_strjoin_gnl(tab->doc->map, line, 2147483647);
    tab->doc->map = ft_strjoin_gnl(tmp, ".", 2147483647);
}

int    ft_get_color(t_color stuff)
{
    return (stuff.red * (256 * 256) +  stuff.green * 256 + stuff.blue);
}

void    parse_line(char *str, t_map *tab)
{
    int     i;

    i = what_is_it(str);
    if (i == 0)
        parse_resolution(str, tab);
    else if (i >= 1 && i <= 5)
        parse_texture(str, tab, i);
    else if (i == 6)
    {
        tab->doc->sol = ft_parse_color(tab->doc->sol, str);
        tab->doc->sol.total = ft_get_color(tab->doc->sol);
    }
    else if (i == 7)
    {
        tab->doc->plafond = ft_parse_color(tab->doc->plafond, str);
        tab->doc->plafond.total = ft_get_color(tab->doc->plafond);
    }
    else if (i == 8)
        parse_map(tab, str);
    
}

void    ft_error(int i)
{
    if (i == -1)
        ft_putstr_fd("Error, avoid defining resolution twice\n", 1);
    if (i == 0)
        ft_putstr_fd("Error, please make sure the res X is superior than res Y\n", 1);
    if (i == 1)
        ft_putstr_fd("Error, texture not found\n", 1);
    if (i == 2)
        ft_putstr_fd("Error, bad red value for sky/floor\n", 1);
    if (i == 3)
        ft_putstr_fd("Error, bad green value for sky/floor\n", 1);
    if (i == 4)
        ft_putstr_fd("Error, bad blue value for sky/floor\n", 1);
    if (i == 5)
        ft_putstr_fd("Error, bad extention for map document\n", 1);
    if (i == 6)
        ft_putstr_fd("Error, map not correct\n", 1);
    if ( i == 7)
        ft_putstr_fd("Error, map should be rectangular\n", 1);
    if (i == 8)
        ft_putstr_fd("Error, structures can't be malloced\n", 1);
    if (i == 9)
        ft_putstr_fd("Error, no map included in line command\n", 1);
    if (i == 10)
        ft_putstr_fd("Error, bad starting position\n", 1);
    if (i == 11)
        ft_putstr_fd("Error, double definition of texture\n", 1);
    exit(0);
}

int     is_correct(char c)
{
    if (c < '0' || c > '2')
    {
        if (c != 'N' && c!= 'S' && c != 'E'&& c != 'W')
            return (1);
    }
    return (0);
}

int     is_okay(char c)
{
    if (c == '1' || c == ' ')
        return (1);
    return (0);
}

int     is_valid(t_map *tab, int i, int j)
{
    // 1 pour une erreur, 0 pour okay
    if (tab->map[i][j + 1] == ' ' || tab->map[i][j + 1] == 0)
        return (1);
    if (tab->map[i][j - 1] == ' ' || tab->map[i][j - 1] == 0)
        return (1);
    if (tab->map[i - 1][j] == ' ' || tab->map[i - 1][j] == 0)
        return (1);
    if (tab->map[i + 1][j] == ' ' || tab->map[i + 1][j] == 0)
        return (1);
    return (0);
}

int     check_around(t_map *tab, int i, int j)
{
    int     tmp;
    int     tmp2;
    // 1 pour une erreur, 0 pour okay
    
    tmp = 0;
    tmp2 = 0;
    while (tab->map[tmp])
        tmp++;
    while (tab->map[i][tmp2])
        tmp2++;
    if (i == 0)
        return (1);
    if (j == 0)
        return (1);
    if (i == tmp - 1)
        return (1);
    if (j == tmp2 - 1)
        return (1);
    if (is_valid(tab, i, j) == 1) 
        return (1);
    return (0);
}

void    check_map(t_map *tab)
{
    int     i;
    int     j;

    i = 0;
    while (tab->map[i])
    {
        j = 0;
        while (tab->map[i][j])
        {
            if (is_okay(tab->map[i][j]) == 0)
            {
                if (check_around(tab, i, j) == 1)
                    ft_error(6);
            }
            j++;
        }
        i++;
    }
}

void    check_parse(t_map *tab)
{
    if (tab->doc->sol.red < 0 || tab->doc->sol.red > 255)
        ft_error(2);
    if (tab->doc->sol.green < 0 || tab->doc->sol.green > 255)
        ft_error(3);
    if (tab->doc->sol.blue < 0 || tab->doc->sol.blue > 255)
        ft_error(4);
    if (tab->doc->plafond.red < 0 || tab->doc->plafond.red > 255)
        ft_error(2);
    if (tab->doc->plafond.green < 0 || tab->doc->plafond.green > 255)
        ft_error(3);
    if (tab->doc->plafond.blue < 0 || tab->doc->plafond.blue > 255)
        ft_error(4);
    check_map(tab);
}

void    parse_doc(char *str, t_map *tab)
{
    char    *line;
    int     i;
    int     fd;

    fd = open(str, O_RDONLY);
    i = 1;
    while (i)
    {
        i = get_next_line(fd, &line);
        parse_line(line, tab);
        free(line);
    }
    // tab->doc->map = clean_str(tab->doc->map);
    tab->map = ft_split(tab->doc->map, '.');
    check_parse(tab);
}

void    check_doc(char *str, t_map *tab)
{
    tab->doc->res = 0;
    if (ft_strncmp(str + ft_strlen(str) - 4, ".cub", 4) != 0)
        ft_error(5);
    else
        parse_doc(str, tab);
}
