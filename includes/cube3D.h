/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:55:14 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/02 14:21:52 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>

# define pi 3.14159265
# define speed 300
# define speed_angle 2
# define speed_div 0.001
# define rayon 0.1
# define epsilon 0.5
# define ABS(n) (n > 0) ? (n) : (-n)

# define GREEN   "\x1b[32m"
# define RESET   "\x1b[0m"

# define W_MAX 2560
# define H_MAX 1440

typedef struct	s_vector
{
	float	x1;
	float	y1;
	float	rotx;
	float	roty;
	float	angle;
	float 	angle_rela;
	int		wall_type;
	float	dist_towall;
}				t_vector;

typedef struct	s_cam
{
	float	angle;
	float	rotx;
	float	roty;
}				t_cam;

typedef	struct	s_int
{
	float	delta;
	float	x;
	float	y;
	float	dist;
}				t_int;

typedef struct	s_dda
{
	float	dx;
	float	dy;
	int		xsign;
	int		ysign;
}				t_dda;

typedef struct	s_data
{
	int					check;
	int 				width;
	int					height;
	int 				exit_status;
	float				posx;
	float				posy;
	float				angle;
	int					R[2];
	char				*NO;
	char				*SO;
	char 				*WE;
	char 				*ES;
	char 				*S;
	char				tex[4];
	unsigned int		F;
	unsigned int		C;
	char				*img;
	void 				*mlx_p;
	void 				*mlx_wd;
	void 				*mlx_img;
	int 				sl;
	int 				endian;
	int 				bpp;
	int 				**map;
	struct s_vector 	*vec;
	struct s_dda		*dda;
	struct s_cam		cam;
}				t_data;

int		ft_iserror(int code);
int		**ft_parse_stuff(t_data *data, int fd);
void 	parse_map(t_data *data, char *line);
void 	parse_color(t_data *data, char *line);
void 	parse_path(t_data *data, char *line);
char	*pathing(char *path, char *line, int *check);
void 	parse_res(t_data *data, char *line);
unsigned int 	coloring(char *line, int *check);

int 	ft_game_loop(t_data *data, int **map);

int 			ft_setup_mlx(t_data *data, int **map);
void 	ft_setup_rays(t_data *data, int **map);
int		ft_main_loop(int keycode, void *params);

unsigned int 	ft_rgb(int r, int g, int b);
float 			ft_toradian(float angle);
int 	ft_isargvalid(char c);
int		ft_search_arg(char *line, char *set);

int 	ft_get_angle(t_data *data, int **map);

void 	do_rays(t_data *data);
void 	ft_setray(t_data *data, int i);
float 	get_dist(t_data *data, int i);
void 	ft_do_colum(t_data *data);

void 	ft_dda(t_data *data, int i);
void 	ft_perform_dda(t_data *data, int i);
float	get_theta(t_data *data, int i);
void 	do_dist(t_data *data, t_int *x_, t_int *y_, int i);

int 	ft_dox(t_data *data, t_int *x_, int i);
int 	ft_doy(t_data *data, t_int *y_, int i);

void 	ft_init_deltas(t_data *data, t_int *x_, t_int *y_, int i);

unsigned int 	ft_choose_color(t_data *data, int i);

int 	ft_keyboard_loop(t_data *data, int keycode);
void	ft_do_colision(t_data *data, int choice);
void 	ft_strife(t_data *data, int id);
void 	ft_advance(t_data *data, float angle, int param);
void 	ft_collision(t_data *data, float angle);
void 	ft_collision_back(t_data *data, float angle);


void 	free_paths(t_data *data);

#endif
