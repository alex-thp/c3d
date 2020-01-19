/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 11:18:10 by ade-temm          #+#    #+#             */
/*   Updated: 2019/12/11 15:07:09 by alexandre        ###   ########.fr       */
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
	int			blue;
	int			green;
	int			red;
	int			trans;
}				t_color;

typedef struct	s_doc
{
	char		*R;
	char		*NO;
	char		*SO;
	char		*WE;
	char		*EA;
	char		*S;
	char		*F;
	char		*C;
	char		*map;
}				t_doc;

typedef struct	s_key
{
	double		vitMarche;
	double		vitRotation;
	int			avancer;
	int			reculer;
	int			tournerG;
	int			tournerD;
	int			droite;
	int			gauche;
}				t_key;

typedef struct	s_len
{
	double 		planx;
	double 		plany;
	int			x;
	int			w;
	int			h;
	double		heightline;
	int			ray_start;
	int			ray_end;
	double		cameraX;
	double		perpWallDist;
	double		rayDirX;
	double		rayDirY;
	double		deltaDistX;
	double		deltaDistY;
	int 		entier_x;
	int 		entier_y;
	double		stepX;
	double		stepY;
	double		norme;
	int			hit;
	double		sideDistX;
	double		sideDistY;
	int			side;
}				t_len;

typedef struct	s_libx
{
	void	*mlx_ptr;
	void	*win;
	void	*img;
	int		*pix;
}				t_libx;

typedef struct	s_map
{
	int			res_y;
	int			res_x;
	char		**map;
	double		angle;
	double		pos_x;
	double		pos_y;
	int			map_x;
	int			map_y;
	int			premierAffichage;
	t_doc		doc;
	t_key		key;
	t_len		len;
	t_libx		mlx;
	t_color		floor;
	t_color		plafond;
}				t_map;

#endif
