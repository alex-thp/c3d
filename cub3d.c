/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:54:42 by ade-temm          #+#    #+#             */
/*   Updated: 2020/02/23 09:41:15 by ade-temm         ###   ########.fr       */
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
    doc->texture = doc->NO;
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
					tab->angle = 90.1;
				if (tab->map[x][y] == 'N')
					tab->angle = 180.1;
				if (tab->map[x][y] == 'W')
					tab->angle = 270.1;
				if (tab->map[x][y] == 'S')
					tab->angle = 0.1;
				tab->pos_y = y + 0.5;
				tab->pos_x = x + 0.5;
				tab->map[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}

double   ft_no_fish_eye(t_map *tab)
{
    double   result;

    result = ((((double)tab->dist->x / (double)tab->dist->res_x) * 60.0) - 30.0);
    result *= M_PI / 180;
    result = cos(result);
    return (result);
}

void    ft_init_ray(t_map *tab)
{
    tab->dist->res_x = tab->doc->res_x;
    tab->dist->res_y = tab->doc->res_y;
    tab->dist->camera = (2 * (double)tab->dist->x / (double)tab->dist->res_x) - 1;
    tab->dist->rayDirX = cos((tab->angle + (30 * tab->dist->camera)) * (M_PI / 180));
    tab->dist->rayDirY = sin((tab->angle + (30 * tab->dist->camera)) * (M_PI / 180));
    tab->dist->deltaDistX = sqrt(1 + (tab->dist->rayDirY * tab->dist->rayDirY) / (tab->dist->rayDirX * tab->dist->rayDirX));
    tab->dist->deltaDistY = sqrt(1 + (tab->dist->rayDirX * tab->dist->rayDirX) / (tab->dist->rayDirY * tab->dist->rayDirY));
    tab->dist->hit = 0;
    tab->map_x = (int)tab->pos_x;
    tab->map_y = (int)tab->pos_y;

    

    // printf("raydirX [%f], raydirY [%f]\n", tab->dist->rayDirX, tab->dist->rayDirY);
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

//Mettre à jour quand on fait les sprites, la ré-appeller
void       init_dir(t_map *tab)
{
    // if (tab->angle < 270 && tab->angle > 90)
        // tab->dist->dirX = -cos(tab->angle * M_PI / 180);//-1;
    // if (tab->angle >= 270 || tab->angle <= 90)
        tab->dist->dirX = cos(tab->angle * M_PI / 180);//1;
    // if (tab->angle > 180)
        tab->dist->dirY = sin(tab->angle * M_PI / 180);//-1;
    // if (tab->angle <= 180)
        // tab->dist->dirY = -sin(tab->angle * M_PI / 180);//1;
}

void    init_image(t_map *tab)
{
    int     i;

    i = 0;
    tab->first_round = 1;
    tab->moove.speed = 0.1;
    tab->mlx.ptr = mlx_init();
    tab->mlx.win = mlx_new_window(tab->mlx.ptr, tab->doc->res_x, tab->doc->res_y, "Cub3d");
    tab->mlx.img = mlx_new_image(tab->mlx.ptr, tab->doc->res_x, tab->doc->res_x);
    tab->mlx.var = (int*)mlx_get_data_addr(tab->mlx.img, &i, &i, &i);
    init_dir(tab);
}

void    ft_get_column(t_map *tab, char c)
{
    double      angle;

    angle = (double)tab->dist->x / tab->dist->res_x;
    angle = (tab->angle - 30) + angle * 60;
    if (c == 'y')
    {
        tab->texture[tab->num].column = (double)cos((angle) * M_PI / 180) * (double)tab->dist->WallDistNoFish + ((double)tab->pos_x - (int)tab->pos_x);
        if (tab->dist->stepY < 0)
            tab->texture[tab->num].column = 1 - tab->texture[tab->num].column;
    }
    else if (c == 'x')
    {
        tab->texture[tab->num].column = (double)sin((angle) * M_PI / 180) * (double)tab->dist->WallDistNoFish + ((double)tab->pos_y - (int)tab->pos_y);
        if (tab->dist->stepX > 0)
            tab->texture[tab->num].column = 1 - tab->texture[tab->num].column;
    }
    tab->texture[tab->num].column = tab->texture[tab->num].column - (int)tab->texture[tab->num].column;
    tab->texture[tab->num].column = tab->texture[tab->num].column * *(tab->texture[tab->num].width);
}

int     ft_get_pixel_from_texture(t_map *tab)
{
    int     result;

    result = tab->texture[tab->num].img[(int)tab->texture[tab->num].column + tab->texture[tab->num].line * *(tab->texture[tab->num].width)];
    return (result);
}

void     ft_get_line(t_map *tab, int i)
{
    double  tmp;

    tmp = (double)tab->dist->draw_end - (double)tab->dist->draw_start;
    tab->texture[tab->num].line = (((double)i - (double)tab->dist->draw_start) / tmp) * (double)*(tab->texture[tab->num].height);
}

int    ft_get_color(t_color stuff)
{
    return (stuff.red * (256 * 256) +  stuff.green * 256 + stuff.blue);
}

void    display_ray(t_map *tab)
{
    int     i;

    i = -1;
    while(++i < tab->dist->draw_start)
        tab->mlx.var[i * tab->doc->res_x + tab->doc->res_x - tab->dist->x] = tab->doc->plafond.total;
    while(i < tab->dist->draw_end && i < tab->doc->res_y)
    {
        ft_get_line(tab, i);
        tab->mlx.var[i * tab->doc->res_x + tab->doc->res_x - tab->dist->x] = ft_get_pixel_from_texture(tab);
        i++;
    }
    while(i <= tab->doc->res_y)
    {
        tab->mlx.var[i * tab->doc->res_x + tab->doc->res_x - tab->dist->x] = tab->doc->sol.total;
        i++;
    }
    tab->dist->x += 1;
}

void    wall_distance(t_map *tab)
{
    if (tab->dist->side == 0)
        tab->dist->WallDist = fabs((tab->map_x - tab->pos_x + (1.0 - (double)tab->dist->stepX) / 2.0) / tab->dist->rayDirX);
    else
        tab->dist->WallDist = fabs((tab->map_y - tab->pos_y + (1.0 - (double)tab->dist->stepY) / 2.0) / tab->dist->rayDirY);
    if (tab->dist->side == 1)
        ft_get_column(tab, 'y');
    else
        ft_get_column(tab, 'x');
    tab->dist->WallDistNoFish = tab->dist->WallDist * (ft_no_fish_eye(tab));
    tab->dist->WallDistNoFish = tab->dist->WallDistNoFish == 0 ? 0.001 : tab->dist->WallDistNoFish;
    tab->dist->hauteur_line = (int)(tab->doc->res_y / tab->dist->WallDistNoFish);
    tab->dist->draw_start = (int)(-(tab->dist->hauteur_line / 2) + tab->dist->res_y / 2);
    tab->dist->draw_end = (tab->dist->hauteur_line / 2) + tab->dist->res_y / 2;
    tab->zbuffer[tab->dist->x] = tab->dist->WallDistNoFish;
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
    if (tab->dist->side == 0 && tab->dist->stepX < 0)
        tab->num = 0 ;
    if (tab->dist->side == 0 && tab->dist->stepX > 0)
        tab->num = 1;
    if (tab->dist->side == 1 && tab->dist->stepY < 0)
        tab->num = 2;
    if (tab->dist->side == 1 && tab->dist->stepY > 0)
        tab->num = 3;
    wall_distance(tab);
}

int     check_game(t_map *tab)
{
    if (tab->moove.tourner_d == 1)
    {
        tab->angle += 3;
        tab->angle = tab->angle > 360 ? tab->angle - 360 : tab->angle;
        tab->planeX = cos((tab->angle + 90) * M_PI / 180);// * 0.66;
        tab->planeY = sin((tab->angle + 90) * M_PI / 180);
        // tab->oldPlaneX = tab->planeX;
        // tab->planeX = tab->planeX * cos(3 * (M_PI / 180)) + tab->planeY * sin(3 * (M_PI / 180));
        // tab->planeY = tab->oldPlaneX * sin(3 * (M_PI / 180)) + tab->planeY * cos(3 * (M_PI / 180));
    }
    if (tab->moove.tourner_g == 1)
    {
        tab->angle -= 3;
        tab->angle = tab->angle < 0 ? 360 - tab->angle : tab->angle;
        tab->planeX = cos((tab->angle + 90) * M_PI / 180);// * 0.66;
        tab->planeY = sin((tab->angle + 90) * M_PI / 180);
        // tab->oldPlaneX = tab->planeX;
        // tab->planeX = tab->planeX * cos(-3 * (M_PI / 180)) + tab->planeY * sin(-3 * (M_PI / 180));
        // tab->planeY = tab->oldPlaneX * sin(-3 * (M_PI / 180)) + tab->planeY * cos(-3 * (M_PI / 180));
    }
    if (tab->moove.droite)
    {
        tab->planeX = cos((tab->angle + 90) * M_PI / 180);// * 0.66;
        tab->planeY = sin((tab->angle + 90) * M_PI / 180);// * 0.66;
        if (tab->map[(int)(tab->pos_x - cos((tab->angle + 90) * M_PI / 180) * tab->moove.speed)]
        [(int)(tab->pos_y - sin((tab->angle + 90) * M_PI / 180) * tab->moove.speed)] == '0')
        {
            tab->pos_x -= cos((tab->angle + 90) * M_PI / 180) * tab->moove.speed;
            tab->pos_y -= sin((tab->angle + 90) * M_PI / 180) * tab->moove.speed;
        }
    }
    if (tab->moove.gauche)
    {
        tab->planeX = cos((tab->angle + 90) * M_PI / 180);// * 0.66;
        tab->planeY = sin((tab->angle + 90) * M_PI / 180);// * 0.66;
        if (tab->map[(int)(tab->pos_x + cos((tab->angle + 90) * M_PI / 180) * tab->moove.speed)]
        [(int)(tab->pos_y + sin((tab->angle + 90) * M_PI / 180) * tab->moove.speed)] == '0')
        {
            tab->pos_x += cos((tab->angle + 90) * M_PI / 180) * tab->moove.speed;
            tab->pos_y += sin((tab->angle + 90) * M_PI / 180) * tab->moove.speed;
        }
    }
    if (tab->moove.avancer)
    {
        if (tab->map[(int)(tab->pos_x + cos((tab->angle) * M_PI / 180) * tab->moove.speed)]
        [(int)(tab->pos_y + sin((tab->angle) * M_PI / 180) * tab->moove.speed)] == '0')
        {
            tab->pos_x += cos((tab->angle) * M_PI / 180) * tab->moove.speed;
            tab->pos_y += sin((tab->angle) * M_PI / 180) * tab->moove.speed;
        }
    }
    if (tab->moove.reculer)
    {
        if (tab->map[(int)(tab->pos_x - cos((tab->angle) * M_PI / 180) * tab->moove.speed)]
        [(int)(tab->pos_y - sin((tab->angle) * M_PI / 180) * tab->moove.speed)] == '0')
        {
            tab->pos_x -= cos((tab->angle) * M_PI / 180) * tab->moove.speed;
            tab->pos_y -= sin((tab->angle) * M_PI / 180) * tab->moove.speed;
        }
    }
    tab->dist->x = 0;
    return (0);
}

int     loop_game(t_map *tab)
{
    int     i;

    i = 0;
    check_game(tab);
    if (tab->first_round || tab->moove.tourner_d || tab->moove.tourner_g || tab->moove.avancer ||
    tab->moove.reculer || tab->moove.gauche || tab->moove.droite)
    {
        tab->first_round = 0;
        while (tab->dist->x <= tab->doc->res_x)
        {
            calc_dist(tab);
            display_ray(tab);
        }
        init_dir(tab);
        while (i < tab->nb_sprite)
        {
            ft_sort_sprite(tab);
            ft_print_sprite(tab, i);
            i++;
        }
    }
    mlx_put_image_to_window(tab->mlx.ptr, tab->mlx.win, tab->mlx.img, 0, 0);
    return (0);
}

int     read_xpm_texture(t_doc *doc, t_map *tab, int num)
{
    int     *size;
    int     i;
    char    *str;

    i = 4;
    if (!(size = malloc(sizeof(int) * 2)))
        return (0);
    size[0] = 0;
    size[1] = 0;
    if (num == 0)
        str = doc->NO;
    if (num == 1)
        str = doc->SO;
    if (num == 2)
        str = doc->WE;
    if (num == 3)
        str = doc->EA;
    if (num == 4)
        str = doc->S;
    str += num < 4 ? 5 : 4; //Pour pas segfault sur le sprite
    tab->texture[num].texture_w = mlx_xpm_file_to_image(tab->mlx.ptr, str, &size[0], &size[1]);
    tab->texture[num].width = &size[0];
    tab->texture[num].height = &size[1];
    tab->texture[num].img = (int*)mlx_get_data_addr(tab->texture[num].texture_w, &i, &i, &i);
    return (0);
}

int    ft_close(void)
{
    exit(0);
    return (0);
}

int     appuyer(int keycode, t_map *tab)
{
    // printf("press : %d\n", keycode);
    if (keycode == 53)
        ft_close();
    if (keycode == 257)
        tab->moove.speed = 0.3;
    if (keycode == 123)
        tab->moove.tourner_d = 1;
    else if (keycode == 124)
        tab->moove.tourner_g = 1;
    else if (keycode == 13)
        tab->moove.avancer = 1;
    else if (keycode == 1)
        tab->moove.reculer = 1;
    else if (keycode == 2)
        tab->moove.droite = 1;
    else if (keycode == 0)
        tab->moove.gauche = 1;
    return (0);
}

int     relacher(int keycode, t_map *tab)
{
    // printf("press : %d\n", keycode);
    if (keycode == 257)
        tab->moove.speed = 0.1;
    if (keycode == 123)
        tab->moove.tourner_d = 0;
    else if (keycode == 124)
        tab->moove.tourner_g = 0;
    else if (keycode == 13)
        tab->moove.avancer = 0;
    else if (keycode == 1)
        tab->moove.reculer = 0;
    else if (keycode == 2)
        tab->moove.droite = 0;
    else if (keycode == 0)
        tab->moove.gauche = 0;

    return (0);
}

int     main(int ac, char **av)
{
    int     fd;
    t_doc   *doc;
    t_map   *tab;
    t_pos   *dist;

    if (ac < 2)
        return (0);
    if (!(doc = (t_doc*)malloc(sizeof(t_doc))))
        return (-1);
    if (!(tab = (t_map*)malloc(sizeof(t_map))))
        return (-1);
    if (!(dist = (t_pos*)malloc(sizeof(t_pos))))
        return (-1);
    tab->doc = doc;
    tab->dist = dist;
    fd = open(av[1], O_RDONLY);
    ft_parse_doc(fd, doc);
    if(!(tab->zbuffer = (double*)malloc(sizeof(double) * tab->doc->res_x))) //OCAOU + 1
        return (-1);
    tab->map = ft_split(tab->doc->map, '.');
    position(tab);
    tab->planeX = cos((tab->angle + 90) * M_PI / 180);// * 0.66;
    tab->planeY = sin((tab->angle + 90) * M_PI / 180);
    // printf("[%f]\n", tab->planeX);
    // printf("[%f]\n", tab->planeY);
    init_image(tab);
    fd = -1;
    tab->doc->sol.total = ft_get_color(tab->doc->sol);
    tab->doc->plafond.total =ft_get_color(tab->doc->plafond);
    while (++fd < 5)
        read_xpm_texture(tab->doc, tab, fd);
    //int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
    ft_get_sprite(tab);
    mlx_hook(tab->mlx.win, 2, 0, appuyer, tab);
	mlx_hook(tab->mlx.win, 3, 0, relacher, tab);
    mlx_hook(tab->mlx.win, 17, 0, ft_close, tab);
    mlx_loop_hook(tab->mlx.ptr, &loop_game, tab);
    mlx_loop(tab->mlx.ptr);
}
/*
    printf("pos_x : %f, pos_y : %f, angle : %f", tab->pos_x, tab->pos_y, tab->angle);
    printf("res_x : %d, res_y : %d\n NO : %s S : %s\nsol.red : %d sol.green : %d, sol.blue : %d\nplafond.red : %d, plafond.green : %d, plafond.blue : %d", tab->doc->res_x, tab->doc->res_y, tab->doc->NO, tab->doc->S, tab->doc->sol.red, tab->doc->sol.green, tab->doc->sol.blue, tab->doc->plafond.red, tab->doc->plafond.green, tab->doc->plafond.blue);
*/