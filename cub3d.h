/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-temm <ade-temm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:18:10 by ade-temm          #+#    #+#             */
/*   Updated: 2020/03/03 15:10:07 by ade-temm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <mlx.h>

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
	int			total;
}				t_color;

typedef struct	s_doc
{
	int			res_x;
	int			res_y;
	int			res;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
	char		*texture;
	t_color		sol;
	t_color		plafond;
	char		*map;
}				t_doc;

typedef struct	s_pos
{
	int			res_x;
	int			res_y;
	double		camera;
	double		rayDirX;
	double		rayDirY;
	double		dirX;
	double		dirY;
	double		oldDirX;
	double		deltaDistX;
	double		deltaDistY;
	double		sideDistX;
	double		sideDistY;
	double		planX;
	double		planY;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	double		WallDist;
	double		WallDistNoFish;
	double		hauteur_line;
	int			draw_start;
	int			draw_end;
	int			x;
}				t_pos;

typedef struct	s_set
{
	void		*ptr;
	void		*win;
	void		*img;
	int			*var;
}				t_set;

typedef struct	s_moove
{
	int			avancer;
	int			reculer;
	int			gauche;
	int			droite;
	int			tourner_g;
	int			tourner_d;
	double		speed;
}				t_moove;

typedef struct 	s_text
{
	void		*texture_w;
	int			*img;
	int			*width;
	int			*height;
	double		column;
	int			line;

}				t_text;

typedef struct	s_sprite
{
	float		x;
	float		y;
	float		dist;
	float		perp_WD;
	float		pos_x;
	float		pos_y;
	int			height;
	int			width;
	int			indic;
	struct s_sprite *next;
}				t_sprite;

typedef struct	h_sprite
{
	t_sprite	*sprite;
}				v_sprite;

typedef struct	s_screenshot
{
	int				fd;
}				t_screenshot;

typedef struct		s_map
{
	t_doc			*doc;
	t_pos			*dist;
	t_sprite		*sprite;
	t_sprite		*new;
	t_set			mlx;
	t_moove			moove;
	t_text			texture[5];
	t_screenshot	screenshot;
	char			**map;
	double			*zbuffer;
	int				sprite_d;
	int				sprite_drawStartY;
	int				sprite_drawStartX;
	int				sprite_drawEndX;
	int				sprite_drawEndY;
	int				texX;
	int				texY;
	int				screenX;
	float			spriteX;
	float			spriteY;
	float			height_sprite_percue;
	float			sprite_width_percue;
	int				startX;
	int				startY;
	int				num;
	int				nb_sprite;
	float			planeX;
	float			planeY;
	float			oldPlaneX;
	float			oldPlaneY;
	float			invDet;
	float			transformX;
	float			transformY;
	float			pos_x;
	float			pos_y;
	int				map_x;
	int				map_y;
	float			angle;
	int				first_round;
	int				vmv;
	int				check_pos;
}					t_map;

void    ft_get_sprite(t_map *tab);
void    ft_sort_sprite(t_map *tab);
void    ft_calc_var_sprite(t_map *tab, int i);
void    ft_print_sprite(t_map *tab, int i);
void    init_dir(t_map *tab);
void    ft_make_screenshot(t_map *tab);
int     loop_game(t_map *tab);
void    check_doc(char *str, t_map *tab);
void    ft_error(int i);
int     ft_is_num(char c);
int    ft_get_color(t_color stuff);
#endif