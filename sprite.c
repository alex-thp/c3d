/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:52:58 by ade-temm          #+#    #+#             */
/*   Updated: 2020/02/19 10:20:14 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void        ft_swap_sp(t_sprite *t1, t_sprite *t2)
{
    t_sprite    tmp;

    tmp.pos_x = t1->pos_x;
    tmp.pos_y = t1->pos_y;
    tmp.sp_dist = t1->sp_dist;
    t1->pos_x = t2->pos_x;
    t1->pos_y = t2->pos_y;
    t1->sp_dist = t2->sp_dist;
    t2->pos_x = tmp.pos_x;
    t2->pos_y = tmp.pos_y;
    t2->sp_dist = tmp.sp_dist;
}
                 
void        ft_dist_sprite(t_map *tab)
{
    int     i;

    i = 0;
    while (i < tab->nb_sprite)
    {
        tab->sprite[i].sp_dist = sqrt(((double)(tab->pos_x - tab->sprite[i].pos_x) * (tab->pos_x - tab->sprite[i].pos_x) + (tab->pos_y - tab->sprite[i].pos_y) * (tab->pos_y - tab->sprite[i].pos_y)));
        tab->sprite[i].perp_WD = tab->dist->WallDist;
        i++;
    }
}

void        ft_sort_sprite(t_map *tab)
{
    int     i;
    int     j;

    i = 0;
    ft_dist_sprite(tab);
    while (i < tab->nb_sprite - 1)
    {
        j = i + 1;
        while (j < tab->nb_sprite)
        {
            if (tab->sprite[i].sp_dist < tab->sprite[j].sp_dist)
            {
                ft_swap_sp(&tab->sprite[i], &tab->sprite[j]);
            }
            j++;
        }
        i++;
    }
}

void        ft_create_tab_sprite(t_map *tab, int count)
{
    t_sprite    *tab2;
    int         i;
    int         j;
    int         z;

    if (!(tab2 = (t_sprite*)malloc(sizeof(t_sprite) * (count + 1))))
        return ;
    i = 0;
    z = 0;
    while (tab->map[i])
    {
        j = 0;
        while (tab->map[i][j])
        {
            if (tab->map[i][j] == 2)
            {
                tab2[z].pos_x = i + 0.5;
                tab2[z].pos_y = j + 0.5;
                z++;
            }
            j++;
        }
        i++;
    }
    tab->sprite = &tab2[0];
    tab->nb_sprite = count;
}

void        ft_get_sprite(t_map *tab)
{
    int     i;
    int     j;
    int     count;

    i = 0;
    count = 0;
    while (tab->map[i])
    {
        j = 0;
        while (tab->map[i][j])
        {
            if (tab->map[i][j] == '2')
                count++;
            j++;
        }
        i++;
    }
    ft_create_tab_sprite(tab, count);
}
