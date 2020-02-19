/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:29:37 by ade-temm          #+#    #+#             */
/*   Updated: 2020/02/16 15:04:01 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	list_to_tab(t_map *tab)
{
	t_sp	*tmp;
	t_sp	*temp;
	int		i;

	i = 0;
	if (!(tab->sprite = (t_sprite*)malloc(sizeof(t_sprite)
	* (tab->len.nb_sp + 1))))
		return ;
	tmp = tab->sp;
	while (tmp)
	{
		tab->sprite[i].indic = 1;
		tab->sprite[i].x = tmp->x;
		tab->sprite[i].y = tmp->y;
		tab->sprite[i].dist = tmp->dist;
		i++;
		temp = tmp->next;
		free(tmp);
		tmp = temp;
	}
	tab->sprite[i].indic = 0;
}

void	list_to_dist(t_map *tab)
{
	int		i;
	t_sp	*tmp;

	tmp = tab->sp;
	i = 0;
	while (i < tab->len.nb_sp)
	{
		tmp->dist = ((tab->pos_x - tmp->x) *
		(tab->pos_x - tmp->x) + (tab->pos_y - tmp->y) *
		(tab->pos_y - tmp->y));
		tmp = tmp->next;
		i++;
	}
	list_to_tab(tab);
}

int		ft_sps_stock(double x, double y, t_map *tab)
{
	tab->new = NULL;
	tab->tmp = NULL;
	if (tab->sp == NULL)
	{
		if (!(tab->sp = (t_sp*)malloc(sizeof(t_sp))))
			return (0);
		tab->sp->x = x + 0.5;
		tab->sp->y = y + 0.5;
		tab->sp->next = NULL;
	}
	else
	{
		if (!(tab->new = (t_sp*)malloc(sizeof(t_sp))))
			return (0);
		tab->tmp = tab->sp;
		while (tab->tmp->next)
			tab->tmp = tab->tmp->next;
		tab->tmp->next = tab->new;
		tab->new->x = x + 0.5;
		tab->new->y = y + 0.5;
		tab->new->next = NULL;
	}
	return (1);
}

void	calc_disp_sp(t_map *tab, int i)
{
	while (i < tab->len.nb_sp)
	{
		calc_dist_sp(tab, i);
		calc_dist_sp_two(tab);
		while (tab->len.stripe < tab->drw_endx)
		{
			tab->len.tex_x = (int)(256 * (tab->len.stripe - (-tab->spwidth
			/ 2 + tab->spscreenx)) * tab->len.texwidth / tab->spwidth)
			/ 256;
			if (tab->trsformy > 0 && tab->len.stripe > 0 && tab->len.stripe
			< tab->len.w && tab->trsformy < tab->len.zbuff[tab->len.stripe])
			{
				display_ray_sp(tab);
			}
			tab->len.stripe++;
		}
		i++;
	}
}

void	sort_sprite(t_map *tab, int i)
{
	i = 0;
	dist_sprite(tab, i);
	while (i < tab->len.nb_sp)
	{
		if (tab->sprite[i].dist < tab->sprite[i + 1].dist
		&& tab->sprite[i + 1].indic)
		{
			swap_sprite(tab, i);
			i = 0;
		}
		i++;
	}
	i = 0;
	calc_disp_sp(tab, i);
}

void	display_sprites(t_map *tab)
{
	tab->len.x_tmp = 0.0;
	tab->len.y_tmp = 0.0;
	tab->len.d_tmp = 0.0;
	if (tab->len.nb_sp > 0)
	{
		sort_sprite(tab, 0);
	}
}

void	dist_sprite(t_map *tab, int i)
{
	while (i < tab->len.nb_sp)
	{
		tab->sprite[i].dist = sqrt((double)((tab->pos_x
		- tab->sprite[i].x) *
		(tab->pos_x - tab->sprite[i].x) + (tab->pos_y
		- tab->sprite[i].y) *
		(tab->pos_y - tab->sprite[i].y)));
		i++;
	}
}

void	swap_sprite(t_map *tab, int i)
{
	tab->len.d_tmp = tab->sprite[i].dist;
	tab->sprite[i].dist = tab->sprite[i + 1].dist;
	tab->sprite[i + 1].dist = tab->len.d_tmp;
	tab->len.x_tmp = tab->sprite[i].x;
	tab->sprite[i].x = tab->sprite[i + 1].x;
	tab->sprite[i + 1].x = tab->len.x_tmp;
	tab->len.y_tmp = tab->sprite[i].y;
	tab->sprite[i].y = tab->sprite[i + 1].y;
	tab->sprite[i + 1].y = tab->len.y_tmp;
}

void	calc_dist_sp(t_map *tab, int i)
{
	tab->spritex = tab->sprite[i].x - tab->pos_x;
	tab->spritey = tab->sprite[i].y - tab->pos_y;
	tab->invdet = 1.0 / (tab->len.planx * sin(tab->angle
	* (M_PI / 180)) - cos(tab->angle * (M_PI / 180)) * tab->len.plany);
	tab->trsformx = tab->invdet * (sin(tab->angle * (M_PI / 180))
	* tab->spritex - cos(tab->angle * (M_PI / 180)) * tab->spritey);
	tab->trsformy = tab->invdet * (-tab->len.plany * tab->spritex
	+ tab->len.planx * tab->spritey);
	tab->vmv_screen = (int)(tab->dst_sp.width2 / tab->trsformy);
	tab->spscreenx = (int)((tab->len.w / 2) * (1 + tab->trsformx
	/ tab->trsformy));
	tab->spheight = abs((int)(tab->len.h / (tab->trsformy))) / 1;
	tab->drw_starty = (-tab->spheight / 2 + tab->len.h / 2) + tab->vmv_screen;
}

void	calc_dist_sp_two(t_map *tab)
{
	if (tab->drw_starty < 0)
		tab->drw_starty = 0;
	tab->drw_endy = (tab->spheight / 2 + tab->len.h / 2) + tab->vmv_screen;
	if (tab->drw_endy >= tab->len.h)
		tab->drw_endy = tab->len.h - 1;
	tab->spwidth = abs((int)(tab->len.h / (tab->trsformy))) / 1;
	tab->drw_startx = -tab->spwidth / 2 + tab->spscreenx;
	if (tab->drw_startx < 0)
		tab->drw_startx = 0;
	tab->drw_endx = tab->spwidth / 2 + tab->spscreenx;
	if (tab->drw_endx >= tab->len.w)
		tab->drw_endx = tab->len.w - 1;
	tab->len.stripe = tab->drw_startx;
	tab->len.texwidth = tab->dst_sp.width2;
}

void	display_ray_sp(t_map *tab)
{
	tab->len.y = tab->drw_starty;
	while (tab->len.y < tab->drw_endy)
	{
		tab->len.d = (tab->len.y - tab->vmv_screen) * 256
		- tab->len.h * 128 + tab->spheight * 128;
		tab->len.tex_y = ((tab->len.d * tab->dst_sp.height2)
		/ tab->spheight) / 256;
		if (tab->dst_sp.pix[tab->len.texwidth * tab->len.tex_y
		+ tab->len.tex_x] != tab->dst_sp.pix[0])
		{
			tab->mlx.var[tab->len.y * tab->res_x + tab->len.stripe] =
			tab->dst_sp.pix[tab->len.texwidth * tab->len.tex_y
			+ tab->len.tex_x];
		}
		tab->len.y++;
	}
}
