/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:43:59 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 16:32:48 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct			s_vector
{
	float				x1;
	float				y1;
	float				rotx;
	float				roty;
	float				angle;
	float				angle_rela;
	float				tan_theta;
	int					wall_type;
	float				dist_towall;
	float				id_wallx;
	float				id_wally;
}						t_vector;

typedef struct			s_cam
{
	float				angle;
	float				rotx;
	float				roty;
}						t_cam;

typedef	struct			s_int
{
	float				delta;
	float				x;
	float				y;
	float				dist;
}						t_int;

typedef struct			s_dda
{
	float				dx;
	float				dy;
	int					xsign;
	int					ysign;
}						t_dda;

typedef struct			s_tex
{
	void				*img_p;
	char				*img;
	int					w;
	int					h;
	int					sl;
	int					bpp;
	int					endian;
}						t_tex;

typedef struct			s_color
{
	unsigned char	color[3];
	int				tex_x;
	int				n_pixel;
	int				side;
	int				hp;
}						t_color;

typedef struct			s_sprite
{
	float	x;
	float	y;
	float	dist;
	int		sizex;
	int		sizey;
	float	angle;
	float	angle_f;
	float	angle_l;
	float	rotx;
	float	roty;
}						t_sprite;

typedef struct			s_data
{
	int				check;
	int				save;
	int				width;
	int				height;
	int				exit_status;
	float			posx;
	float			posy;
	float			angle;
	int				r[2];
	char			*no;
	char			*so;
	char			*we;
	char			*es;
	char			*s;
	unsigned int	f;
	unsigned int	c;
	char			*img;
	void			*mlx_p;
	void			*mlx_wd;
	void			*mlx_img;
	int				sl;
	int				endian;
	int				bpp;
	int				**map;
	int				s_max;
	int				move;
	struct s_vector	*vec;
	struct s_dda	*dda;
	struct s_cam	cam;
	struct s_tex	tex[5];
	struct s_sprite	*tsprite;
}						t_data;

#endif
