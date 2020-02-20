/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:52:58 by ade-temm          #+#    #+#             */
/*   Updated: 2020/02/20 14:29:08 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void        ft_swap_sp(t_sprite *t1, t_sprite *t2)
{
    t_sprite    tmp;

    tmp.pos_x = t1->pos_x;
    tmp.pos_y = t1->pos_y;
    tmp.dist = t1->dist;
    t1->pos_x = t2->pos_x;
    t1->pos_y = t2->pos_y;
    t1->dist = t2->dist;
    t2->pos_x = tmp.pos_x;
    t2->pos_y = tmp.pos_y;
    t2->dist = tmp.dist;
}
                 
void        ft_dist_sprite(t_map *tab)
{
    int     i;

    i = 0;
    while (i < tab->nb_sprite)
    {
        tab->sprite[i].dist = sqrt(((double)(tab->pos_x - tab->sprite[i].pos_x) * (tab->pos_x - tab->sprite[i].pos_x) + (tab->pos_y - tab->sprite[i].pos_y) * (tab->pos_y - tab->sprite[i].pos_y)));
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
            if (tab->sprite[i].dist < tab->sprite[j].dist)
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
    int         i;
    int         j;
    int         z;

    if (!(tab->sprite = (t_sprite*)malloc(sizeof(t_sprite) * (count + 1))))
        return ;
    i = 0;
    z = 0;
    while (tab->map[i])
    {
        j = 0;
        while (tab->map[i][j])
        {
            if (tab->map[i][j] == '2')
            {
                tab->sprite[z].pos_x = i + 0.5;
                tab->sprite[z].pos_y = j + 0.5;
                z++;
            }
            j++;
        }
        i++;
    }
    // tab->sprite = &tab2[0];
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

void    ft_calc_var_sprite(t_map *tab, int i)
{
    tab->spriteX = (tab->sprite[i].pos_x - tab->pos_x);
    tab->spriteY = (tab->sprite[i].pos_y - tab->pos_y);
    //printf("[%d] [%d]\n", i, tab->nb_sprite);
    // printf("SPRITE x : [%f] [%f] [%f]\n", tab->spriteX, tab->sprite[i].pos_x, tab->pos_x);
	// printf("SPRITE y : [%f] [%f] [%f]\n", tab->spriteY, tab->sprite[i].pos_y, tab->pos_y);
    tab->invDet = 1.0 / (tab->planeX * sin(tab->angle * (M_PI / 180)) - cos(tab->angle * (M_PI * 180)) * tab->planeY);
    tab->transformX = tab->invDet * (sin(tab->angle * (M_PI / 180)) * tab->spriteX - cos(tab->angle * (M_PI / 180)) * tab->spriteY);
    tab->transformY = tab->invDet * (-tab->planeY * tab->spriteX + tab->planeX * tab->spriteY);
    // printf("tab->transformY[%f], tab->invDet [%f], tab->planeY [%f], tab->planeX [%f], tab->spriteX [%f], tab->spriteY [%f]\n", tab->transformY, tab->invDet, tab->planeY, tab->planeX, tab->spriteX, tab->spriteY);
    tab->vmv = (int)((float)(*tab->texture[4].width) / tab->transformY); //Attention ici
    tab->screenX = (int)((tab->doc->res_x / 2) * (1 + tab->transformX / tab->transformY));
    tab->height_sprite_percue = 1.5 * (abs((int)(tab->doc->res_y / tab->transformY)) / 1); //taille des sprites ici
    tab->sprite_drawStartY = (-tab->height_sprite_percue / 2 + tab->doc->res_y / 2) + tab->vmv;
    tab->sprite_drawEndY = (tab->height_sprite_percue / 2 + tab->doc->res_y / 2) + tab->vmv;
    if (tab->sprite_drawStartY < 0)
        tab->sprite_drawStartY = 0;
    if (tab->sprite_drawEndY >= tab->doc->res_y)
        tab->sprite_drawEndY = tab->doc->res_y - 1;
    tab->sprite_width_percue = abs((int)(tab->doc->res_y / tab->transformY));
    //printf("tab->doc->res_y [%d], tab->transformY [%f]\n", tab->doc->res_y, tab->transformY);
    tab->sprite_drawStartX = -(*tab->texture[4].width / 2) + tab->screenX;
    tab->sprite_drawEndX = tab->sprite_width_percue / 2 + tab->screenX;
    //printf("tab->sprite_drawEndX [%d], tab->sprite_width_percue[%f], tab->screenX [%d]\n", tab->sprite_drawEndX, tab->sprite_width_percue, tab->screenX);
    if (tab->sprite_drawStartX < 0)
        tab->sprite_drawStartX = 0;
    if (tab->sprite_drawEndX >= tab->doc->res_x)
        tab->sprite_drawEndX = tab->doc->res_x - 1;
    //printf("tab->sprite_drawStartX %d\n", tab->sprite_drawStartX);
    tab->startX = tab->sprite_drawStartX;
}

void    ft_print_sprite(t_map *tab, int i)
{
    ft_calc_var_sprite(tab, i);
    while (tab->startX < tab->sprite_drawEndX)
    {
        tab->texX = (int)(256 * (tab->startX - (-tab->height_sprite_percue / 2 + tab->screenX)) * (((float)*tab->texture[4].width / tab->height_sprite_percue))) / 256;
        //printf("tab->transformY [%f], tab->startX [%d], tab->zbuffer[tab->startX][%f]\n", tab->transformY, tab->startX, tab->zbuffer[tab->startX]);
        //printf("tab->transformY %f, tab->startX %d, tab->zbuffer[tab->startX] %f\n", tab->transformY, tab->startX, tab->zbuffer[tab->startX]);
        if (tab->transformY > 0 && tab->startX > 0 && tab->startX < tab->doc->res_x && tab->transformY < tab->zbuffer[tab->startX])
        {
            tab->startY = tab->sprite_drawStartY;
            while (tab->startY < tab->sprite_drawEndY)
            {
                tab->sprite_d = (tab->startY - tab->vmv) * 256 - tab->doc->res_y * 128 + tab->height_sprite_percue * 128;
                tab->texY = tab->sprite_d * *tab->texture[4].height / tab->height_sprite_percue / 256;
                if (tab->texture[4].img[*tab->texture[4].width * tab->texY + tab->texX] != tab->texture[4].img[1])
                    tab->mlx.var[tab->startY * tab->doc->res_x + tab->startX] = tab->texture[4].img[*tab->texture[4].width * tab->texY + tab->texX];
                tab->startY++;
            }
        }
        tab->startX++;
    }
}
