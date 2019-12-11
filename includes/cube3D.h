/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:55:14 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 17:12:59 by jdurand          ###   ########.fr       */
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
# include "../nmp/includes/libbmp.h"

# define PI 3.14159265
# define SPEED 150
# define SPEED_ANGLE 2
# define SPEED_DIV 0.001
# define RAYON 0.1
# define UPWARD 1
# define BACKWARD 2
# define STRAFE_L 4
# define STRAFE_R 8
# define LEFT 16
# define RIGHT 32
# define EXIT 64

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
	float	tan_theta;
	int		wall_type;
	float	dist_towall;
	float	id_wallx;
	float	id_wally;
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

typedef struct	s_tex
{
	void 	*img_p;
	char	*img;
	int		w;
	int 	h;
	int		sl;
	int		bpp;
	int		endian;
}				t_tex;

typedef struct s_color
{
	unsigned char 	color[3];
	int 			tex_x;
	int 			n_pixel;
	int 			side;
	int 			hp;
}				t_color;

typedef struct s_sprite
{
	float	x;
	float	y;
	float	dist;
	int 	sizex;
	int 	sizey;
	float	angle;
	float	angle_f;
	float 	angle_l;
	float	rotx;
	float	roty;
}				t_sprite;

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
	int					s_max;
	int					move;
	struct s_vector 	*vec;
	struct s_dda		*dda;
	struct s_cam		cam;
	struct s_tex		tex[5];
	struct s_sprite		*tsprite;
}				t_data;

int		ft_iserror(int code);
int		**ft_parse_stuff(t_data *data, int fd);
int		**ft_parse_map(t_list **lst, size_t count, int *check, t_data *data);
int 	ft_parse_aline(t_data *data, int **map, char *line, int count);
void 	parse_color(t_data *data, char *line);
void 	parse_path(t_data *data, char *line);
char	*pathing(char *path, char *line, int *check);
void 	parse_res(t_data *data, char *line);
unsigned int 	coloring(char *line, int *check);

int 	ft_game_loop(t_data *data, int **map);

int 			ft_setup_mlx(t_data *data, int **map);
void 	ft_setup_rays(t_data *data, int **map);
int		ft_main_loop(t_data *data);

unsigned int 	ft_rgb(int r, int g, int b);
float 			ft_toradian(float angle);
int 	ft_isargvalid(char c);
int		ft_search_arg(char *line, char *set);

int 	ft_get_angle(t_data *data, int **map);

void 	ft_coloriage(t_data *data, int i, int j, unsigned int color);
void 	ft_setbackground(t_data *data);

void 	do_rays(t_data *data);
void 	ft_setray(t_data *data, int i);
float 	get_dist(t_data *data, int i);
void 	ft_do_colum(t_data *data);

void 	ft_dda(t_data *data, int i);
void 	ft_perform_dda(t_data *data, int i);
void 	ft_init_perform_dda(t_data *data, int i, t_int *x_, t_int *y_);
float	get_theta(t_data *data, int i);
void 	do_dist(t_data *data, t_int *x_, t_int *y_, int i);

int 	ft_dox(t_data *data, t_int *x_, int i);
int 	ft_doy(t_data *data, t_int *y_, int i);

void 	ft_init_deltas(t_data *data, t_int *x_, t_int *y_, int i);

unsigned int 	ft_choose_color(t_data *data, int i);

int 	ft_keyboard_loop(t_data *data);
void	ft_do_colision(t_data *data, int choice);
void 	ft_strafe(t_data *data, int id);
void 	ft_advance(t_data *data, float angle, int param);
void 	ft_collision(t_data *data, float angle);
void 	ft_collision_back(t_data *data, float angle);
int 	ft_get_dist_info(t_data *data, int i);

void 	free_paths(t_data *data);

int	ft_setup_tex(t_data *data);
void 	ft_get_info_tex(t_tex *tex);
unsigned int 	ft_get_tex_xpixel(t_data *data, t_color *color, int i);
void 	ft_get_tex_ypixel(t_data *data, t_color *color);
void 	ft_init_t_color(t_data *data, t_color *color, int i, int *j);

void ft_do_tsprite(t_data * data);
void 		ft_check_if_hit(t_data *data);
void 	ft_reset_tsprite(t_sprite *tsprite, int s_max, t_data *data);
void 	ft_do_dist_sprite(t_data *data);
void 	ft_init_dist_tsprite(t_data *data, float *distx, float *disty, int i);
void 	ft_draw_sprites(t_data *data, int pixel, int sizex, t_sprite *sprite);
void 	ft_draw_a_colum_sprite(t_data *data, int i, int hp, int xpixel);
void 	ft_init_draw_sprite(t_data *data, int *j, int *n_pixel, int hp);
void 	ft_check_if_visible(t_data *data);
float ft_abs(float n);

void 	ft_zbuffer(t_data *data, t_sprite *sprite, float pas);
int 	ft_raying_sprite(t_data *data, float angle_s);
void 	ft_get_tex_ypixel_sprite(t_data *data, int *tab, unsigned char *color);
void 	ft_do_sort_sprite(t_data *data);
void 	ft_swap_sprite(t_sprite *a, t_sprite *b);
void 	ft_swap_sprite2(t_sprite *a, t_sprite *b);
float	to_d(float radian);
float	lissage_angle(float angle);
int	ft_comp_sprite_angle(float angle_f, float angle_l, t_data *data);

void    ft_do_looping(t_data *data);
int		keypress(int keycode, void *param);
int 	keyrelease(int keycode, void *param);

void ft_clear_list(void *content);
void 	ft_freemap(t_data *data);



void 	ft_exit_all(t_data *data);
void 	ft_free_map(t_data *data);
void 	ft_free_vec(t_data *data);
void 	ft_free_dda(t_data *data);
void 	ft_free_tsprite(t_data *data);
void 	ft_free_tex(t_data *data);
void 	ft_lst_free(t_list **lst);
int		exit_program(int keycode, void *param);


#endif
