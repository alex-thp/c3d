/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:31:31 by ade-temm          #+#    #+#             */
/*   Updated: 2020/03/03 14:45:03 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char    *ft_do_file_header(t_map *tab)
{
    unsigned char   *header;
    int             file_size;

    header = malloc(14);
    file_size = 54 + (4 * tab->doc->res_x) * tab->doc->res_y;
    ft_bzero(header, 14);
    header[0] = (unsigned char)'B';
    header[1] = (unsigned char)'M';
    header[2] = (unsigned char)(file_size);
    header[3] = (unsigned char)(file_size >> 8);
    header[4] = (unsigned char)(file_size >> 16);
    header[5] = (unsigned char)(file_size >> 24);
    header[10] = (unsigned char)(54);
    return (header);
}

unsigned char    *ft_do_img_header(t_map *tab)
{
    unsigned char   *header;
    int             img_size;

    img_size = 54 + (tab->doc->res_x * tab->doc->res_y * 4);
    header = malloc(40);
    ft_bzero(header, 40);
    header[0] = (unsigned char)(40);
    header[4] = (unsigned char)(tab->doc->res_x);
    header[5] = (unsigned char)(tab->doc->res_x >> 8);
    header[6] = (unsigned char)(tab->doc->res_x >> 16);
    header[7] = (unsigned char)(tab->doc->res_x >> 24);
    header[8] = (unsigned char)(tab->doc->res_y);
    header[9] = (unsigned char)(tab->doc->res_y >> 8);
    header[10] = (unsigned char)(tab->doc->res_y >> 16);
    header[11] = (unsigned char)(tab->doc->res_y >> 24);
    header[12] = (unsigned char)(1);
    header[14] = (unsigned char)(3 * 8);
    return (header);
}

void        ft_do_img(t_map *tab)
{
    char    *res;
    int     i;
    int     j;

    res = malloc(3);
    i = 0;
    while (i < tab->doc->res_y - 1)
    {
        j = 0;
        while (j < tab->doc->res_x)
        {
            res[0] = tab->mlx.var[(tab->doc->res_y - 1 - i) * tab->doc->res_x + j];
            res[1] = tab->mlx.var[(tab->doc->res_y - 1 - i) * tab->doc->res_x + j] >> 8;
            res[2] = tab->mlx.var[(tab->doc->res_y - 1 - i) * tab->doc->res_x + j] >> 16;
            write(tab->screenshot.fd, res, 3);
            j++;
        }
        i++;
    }
    free(res);
}

void    ft_make_screenshot(t_map *tab)
{
    unsigned char       *res;

    loop_game(tab);
    tab->screenshot.fd = open("screenshot.bmp", O_CREAT | O_WRONLY, 0666);
    res = ft_do_file_header(tab);
    write(tab->screenshot.fd, res, 14);
    free(res);
    res = ft_do_img_header(tab);
    write(tab->screenshot.fd, res, 40);
    free(res);
    ft_do_img(tab);
    exit(0);
}
