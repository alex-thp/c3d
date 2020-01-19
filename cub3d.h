/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:18:10 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/18 20:03:52 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include "minilibx/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct	s_doc
{
	int			res_x;
	int			res_y;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
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
	double		deltaDistX;
	double		deltaDistY;
	double		sideDistX;
	double		sideDistY;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	double		WallDist;
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
}				t_moove;


typedef struct	s_map
{
	t_doc		*doc;
	t_pos		*dist;
	t_set		mlx;
	t_moove		moove;
	char		**map;
	double		pos_x;
	double		pos_y;
	int			map_x;
	int			map_y;
	double		angle;
	int			first_round;
}				t_map;

#endif