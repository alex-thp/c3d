/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:54:42 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/27 16:09:02 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     ft_is_num(char c)
{
    if (c > 47 && c < 58)
        return (1);
    return (0);
}

char	*clean_str(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = ft_strlen(str);
	if (!(res = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != 32)
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = 0;
	free(str);
	return (res);
}

void    ft_parse_doc(int fd, t_doc *doc)
{
    char    *line;
    int     i;

    i = 0;
    get_next_line(fd, &line);
    while (ft_is_num(line[i]) == 0)
        i++;
    doc->res_x = ft_atoi(&line[i]);
    while (ft_is_num(line[i]) == 1)
        i++;
    doc->res_y = ft_atoi(&line[i]);
    get_next_line(fd, &doc->NO);
    get_next_line(fd, &doc->SO);
    get_next_line(fd, &doc->WE);
    get_next_line(fd, &doc->EA);
    get_next_line(fd, &doc->S);
    i = 0;
    get_next_line(fd, &line);
    while (ft_is_num(line[i]) == 0)
        i++;
    doc->sol.red = ft_atoi(&line[i]);
    while (ft_is_num(line[i]) == 1)
        i++;
    while (ft_is_num(line[i]) == 0)
        i++;
    doc->sol.green = ft_atoi(&line[i]);
    while (ft_is_num(line[i]) == 1)
        i++;
    while (ft_is_num(line[i]) == 0)
        i++;
    doc->sol.blue = ft_atoi(&line[i]);
     i = 0;
    get_next_line(fd, &line);
    while (ft_is_num(line[i]) == 0)
        i++;
    doc->plafond.red = ft_atoi(&line[i]);
    while (ft_is_num(line[i]) == 1)
        i++;
    while (ft_is_num(line[i]) == 0)
        i++;
    doc->plafond.green = ft_atoi(&line[i]);
    while (ft_is_num(line[i]) == 1)
        i++;
    while (ft_is_num(line[i]) == 0)
        i++;
    doc->plafond.blue = ft_atoi(&line[i]);
    
    doc->map = malloc(1);
	doc->map[0] = 0;
	while (i)
	{
		i = get_next_line(fd, &line);
		doc->map = ft_strjoin_gnl(doc->map, line, 2147483647);
		doc->map = ft_strjoin_gnl(doc->map, ".", 2147483647);
	}
    doc->map = clean_str(doc->map);
}

void	position(t_map *tab)
{
	int		x;
	int		y;

	x = 0;
	while (tab->map[x])
	{
		y = 0;
		while (tab->map[x][y])
		{
			if (ft_is_num(tab->map[x][y]) == 0)
			{
				if (tab->map[x][y] == 'E')
					tab->angle = 90;
				if (tab->map[x][y] == 'N')
					tab->angle = 180;
				if (tab->map[x][y] == 'W')
					tab->angle = 270;
				if (tab->map[x][y] == 'S')
					tab->angle = 0;
				tab->pos_y = y + 0.5;
				tab->pos_x = x + 0.5;
				tab->map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}

void    wall_distance(t_map *tab)
{
    if (tab->dist->side == 0)
        tab->dist->WallDist = fabs(((tab->map_x - tab->pos_x + (1 - tab->dist->stepX) / 2) / tab->dist->rayDirX));
    else
        tab->dist->WallDist = fabs(((tab->map_y - tab->pos_y + (1 - tab->dist->stepY) / 2) / tab->dist->rayDirY));    
    tab->dist->WallDist = tab->dist->WallDist == 0 ? 0.001 : tab->dist->WallDist;
    tab->dist->hauteur_line = abs((int)(tab->doc->res_y / tab->dist->WallDist));
    tab->dist->draw_start = (int)(-(tab->dist->hauteur_line / 2) + tab->dist->res_y / 2);
    tab->dist->draw_end = (int)((tab->dist->hauteur_line / 2) + tab->dist->res_y / 2);
    if (tab->dist->draw_start < 0)
        tab->dist->draw_start = 0;
    if (tab->dist->draw_end >= tab->dist->res_y)
        tab->dist->draw_end = tab->dist->res_y - 1;
}

void    ft_init_ray(t_map *tab)
{
    tab->dist->res_x = tab->doc->res_x;
    tab->dist->res_y = tab->doc->res_y;
    tab->dist->camera = (2 * (double)tab->dist->x / (double)tab->dist->res_x) - 1;
    tab->dist->rayDirX = cos((tab->angle + (30 * tab->dist->camera)) * (3.1415926535 / 180));
    tab->dist->rayDirY = sin((tab->angle + (30 * tab->dist->camera)) * (3.1415926535 / 180));
    tab->dist->deltaDistX = sqrt(1 + (tab->dist->rayDirY * tab->dist->rayDirY) / (tab->dist->rayDirX * tab->dist->rayDirX));
    tab->dist->deltaDistY = sqrt(1 + (tab->dist->rayDirX * tab->dist->rayDirX) / (tab->dist->rayDirY * tab->dist->rayDirY));
    tab->dist->hit = 0;
    tab->map_x = (int)tab->pos_x;
    tab->map_y = (int)tab->pos_y;
}

void    calc_dist_xy(t_map *tab)
{
    if (tab->dist->rayDirX < 0)
    {
        tab->dist->stepX = -1;
        tab->dist->sideDistX = (tab->pos_x - tab->map_x) * tab->dist->deltaDistX;
    }
    else
    {
        tab->dist->stepX = 1;
        tab->dist->sideDistX = (tab->map_x + 1.0 - tab->pos_x) * tab->dist->deltaDistX;
    }
    if (tab->dist->rayDirY < 0)
    {
        tab->dist->stepY = -1;
        tab->dist->sideDistY = (tab->pos_y - tab->map_y) * tab->dist->deltaDistY;
    }
    else
    {
        tab->dist->stepY = 1;
        tab->dist->sideDistY = (tab->map_y + 1.0 - tab->pos_y) * tab->dist->deltaDistY;
    }
}

void    calc_dist(t_map *tab)
{
    ft_init_ray(tab);
    calc_dist_xy(tab);
    while (tab->dist->hit == 0)
    {
        if (tab->dist->sideDistX < tab->dist->sideDistY)
        {
            tab->dist->sideDistX += tab->dist->deltaDistX;
            tab->map_x += tab->dist->stepX;
            tab->dist->side = 0;
        }
        else
        {
            tab->dist->sideDistY += tab->dist->deltaDistY;
            tab->map_y += tab->dist->stepY;
            tab->dist->side = 1;
        }
        if (tab->map[tab->map_x][tab->map_y] == '1')
            tab->dist->hit = 1;
    }
    wall_distance(tab);
}

void    init_image(t_map *tab)
{
    int     i;

    i = 0;
    tab->first_round = 1;
    tab->mlx.ptr = mlx_init();
    tab->mlx.win = mlx_new_window(tab->mlx.ptr, tab->doc->res_x, tab->doc->res_y, "Cub3d");
    tab->mlx.img = mlx_new_image(tab->mlx.ptr, tab->doc->res_x, tab->doc->res_x);
    tab->mlx.var = (int*)mlx_get_data_addr(tab->mlx.img, &i, &i, &i);
}

void    display_ray(t_map *tab)
{
    int     i;
    
    i = -1;
    while(++i <= tab->dist->draw_start)
        tab->mlx.var[i * tab->doc->res_x + tab->dist->x] = 0x006699;
    while(i <= tab->dist->draw_end)
    {
        if (tab->dist->side == 0)
            tab->mlx.var[i * tab->doc->res_x + tab->dist->x] = 0x909090;
        else
            tab->mlx.var[i * tab->doc->res_x + tab->dist->x] = 0x898989;
        i++;
    }
    while(i <= tab->doc->res_y)
    {
        tab->mlx.var[i * tab->doc->res_x + tab->dist->x] = 0x336600;
        i++;
    }
    tab->dist->x += 1;
}

int     loop_game(t_map *tab)
{
    if (tab->moove.tourner_d == 1)
    {
        tab->angle += 0.2;
        tab->angle = tab->angle > 359 ? tab->angle - 360 : tab->angle; 
    }
    else if (tab->moove.tourner_g == 1)
    {
        tab->angle -= 0.2;
        tab->angle = tab->angle < 0 ? 360 - tab->angle : tab->angle;
    }
    else if (tab->moove.gauche == 1 && tab->map[(int)(tab->pos_x - cos((tab->angle + 90) * 3.1415926535 / 180) * 0.01)][(int)(tab->pos_y - sin((tab->angle + 90) * 3.1415926535 / 180) * 0.01)] == '0')
    {
        tab->pos_x -= cos((tab->angle + 90) * 3.1415926535 / 180) * 0.01;
        tab->pos_y -= sin((tab->angle + 90) * 3.1415926535 / 180) * 0.01;
    }
    else if (tab->moove.droite == 1 && tab->map[(int)(tab->pos_x + cos((tab->angle + 90) * 3.1415926535 / 180) * 0.01)][(int)(tab->pos_y + sin((tab->angle + 90) * 3.1415926535 / 180) * 0.01)] == '0')
    {
        tab->pos_x += cos((tab->angle + 90) * 3.1415926535 / 180) * 0.01;
        tab->pos_y += sin((tab->angle + 90) * 3.1415926535 / 180) * 0.01; 
    }
    else if (tab->moove.avancer == 1 && tab->map[(int)(tab->pos_x + cos((tab->angle) * 3.1415926535 / 180) * 0.01)][(int)(tab->pos_y + sin((tab->angle) * 3.1415926535 / 180) * 0.01)] == '0')
    {
        tab->pos_x += cos((tab->angle) * 3.1415926535 / 180) * 0.01;
        tab->pos_y += sin((tab->angle) * 3.1415926535 / 180) * 0.01;
    }
    else if (tab->moove.reculer == 1 && tab->map[(int)(tab->pos_x - cos((tab->angle) * 3.1415926535 / 180) * 0.01)][(int)(tab->pos_y - sin((tab->angle) * 3.1415926535 / 180) * 0.01)] == '0')
    {
        tab->pos_x -= cos((tab->angle) * 3.1415926535 / 180) * 0.01;
        tab->pos_y -= sin((tab->angle) * 3.1415926535 / 180) * 0.01;
    }
    tab->dist->x = 0;
    if (tab->first_round || tab->moove.tourner_d || tab->moove.tourner_g || tab->moove.avancer || tab->moove.reculer || tab->moove.gauche || tab->moove.droite)
    {
        tab->first_round = 0;
        while (tab->dist->x <= tab->doc->res_x)
        {
            calc_dist(tab);
            display_ray(tab);
        }
    }
    mlx_put_image_to_window(tab->mlx.ptr, tab->mlx.win, tab->mlx.img, 0, 0);
    return (0);
}

int     appuyer(int keycode, t_map *tab)
{
    printf("press : %d\n", keycode);
    if (keycode == 101 && tab->moove.tourner_d == 0)
    {
        tab->moove.tourner_d = 1;
        tab->moove.tourner_g = 0;
        tab->moove.avancer = 0;
        tab->moove.reculer = 0;
        tab->moove.gauche = 0;
        tab->moove.droite = 0;
    }
    else if (keycode == 101 && tab->moove.tourner_d == 1)
    {
        tab->moove.tourner_d = 0;
        tab->moove.tourner_g = 0;
        tab->moove.avancer = 0;
        tab->moove.reculer = 0;
        tab->moove.gauche = 0;
        tab->moove.droite = 0;
    }
    else if (keycode == 97 && tab->moove.tourner_g == 0)
    {
        tab->moove.tourner_g = 1;
        tab->moove.tourner_d = 0;
        tab->moove.avancer = 0;
        tab->moove.reculer = 0;
        tab->moove.gauche = 0;
        tab->moove.droite = 0;
    }
    else if (keycode == 97 && tab->moove.tourner_g == 1)
    {
        tab->moove.tourner_g = 0;
        tab->moove.tourner_d = 0;
        tab->moove.avancer = 0;
        tab->moove.reculer = 0;
        tab->moove.gauche = 0;
        tab->moove.droite = 0;
    }
    else if (keycode == 122 && tab->moove.avancer == 0)
    {
        tab->moove.avancer = 1;
        tab->moove.reculer = 0;
        tab->moove.gauche = 0;
        tab->moove.droite = 0;
    }
    else if (keycode == 122 && tab->moove.avancer == 1)
    {
        tab->moove.avancer = 0;
        tab->moove.reculer = 0;
        tab->moove.gauche = 0;
        tab->moove.droite = 0;
    }
    else if (keycode == 115 && tab->moove.reculer == 0)
    {
        tab->moove.avancer = 0;
        tab->moove.reculer = 1;
        tab->moove.gauche = 0;
        tab->moove.droite = 0;
    }
    else if (keycode == 115 && tab->moove.reculer == 1)
    {
        tab->moove.avancer = 0;
        tab->moove.reculer = 0;
        tab->moove.gauche = 0;
        tab->moove.droite = 0;
    }
    else if (keycode == 113 && tab->moove.gauche == 0)
    {
        tab->moove.avancer = 0;
        tab->moove.reculer = 0;
        tab->moove.gauche = 1;
        tab->moove.droite = 0;
    }
    else if (keycode == 113 && tab->moove.gauche == 1)
    {
        tab->moove.avancer = 0;
        tab->moove.reculer = 0;
        tab->moove.gauche = 0;
        tab->moove.droite = 0;
    }
    else if (keycode == 100 && tab->moove.droite == 0)
    {
        tab->moove.avancer = 0;
        tab->moove.reculer = 0;
        tab->moove.gauche = 0;
        tab->moove.droite = 1;
    }
    else if (keycode == 100 && tab->moove.droite == 1)
    {
        tab->moove.avancer = 0;
        tab->moove.reculer = 0;
        tab->moove.gauche = 0;
        tab->moove.droite = 0;
    }
    loop_game(tab);
    return (0);
}

int     main(int ac, char **av)
{
    int     fd;
    t_doc   *doc;
    t_map   *tab;
    t_pos   *dist;

    if (!(doc = (t_doc*)malloc(sizeof(t_doc))))
        return (-1);
    if (!(tab = (t_map*)malloc(sizeof(t_map))))
        return (-1);
    if (!(dist = (t_pos*)malloc(sizeof(t_pos))))
        return (-1);
    if (ac < 2)
        return (0);
    tab->doc = doc;
    tab->dist = dist;
    fd = open(av[1], O_RDONLY);
    ft_parse_doc(fd, doc);
    fd = 0;
    tab->map = ft_split(tab->doc->map, '.');
    position(tab);
    init_image(tab);
    //int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
    printf("lol");
    //mlx_hook(tab->mlx.win, 2, 0, appuyer, tab);
    mlx_key_hook(tab->mlx.win, &appuyer, tab);
    printf("%d\n", 123);
	//mlx_hook(tab->mlx.win, 3, 0, relacher, tab);
    printf("%d\n", 456);
    mlx_loop_hook(tab->mlx.ptr, &loop_game, tab);
    printf("%d\n", 789);
    mlx_loop(tab->mlx.ptr);
}
/*
    printf("pos_x : %f, pos_y : %f, angle : %f", tab->pos_x, tab->pos_y, tab->angle);
    printf("res_x : %d, res_y : %d\n NO : %s S : %s\nsol.red : %d sol.green : %d, sol.blue : %d\nplafond.red : %d, plafond.green : %d, plafond.blue : %d", tab->doc->res_x, tab->doc->res_y, tab->doc->NO, tab->doc->S, tab->doc->sol.red, tab->doc->sol.green, tab->doc->sol.blue, tab->doc->plafond.red, tab->doc->plafond.green, tab->doc->plafond.blue);
    int i = 0;
    while(tab->map[i])
    {
        ft_putstr_fd(tab->map[i], 1);
        ft_putchar_fd('\n', 1);
        i++;
    }
    while(doc->map[fd])
    {
        if (doc->map[fd] != '.')
        {
            ft_putchar_fd(doc->map[fd], 1);
            fd++;
        }
        else
        {
            ft_putchar_fd('\n', 1);
            fd++;
        }
    }
*/