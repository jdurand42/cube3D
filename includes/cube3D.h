/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:55:14 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 17:28:04 by jdurand          ###   ########.fr       */
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
# include "us_i.h"
# include "struct.h"

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

# define GREEN "\x1b[32m"
# define RESET "\x1b[0m"

# define W_MAX 2560
# define H_MAX 1440

void	ft_parse_stuff2(t_data *data, char *line, t_list **lst, size_t *count);
int		ft_iserror(int code, t_data *data);
int		ft_parse_stuff(t_data *data, int fd);
int		ft_parse_map(t_list **lst, size_t count, t_data *data);
int		ft_parse_aline(t_data *data, int **map, char *line, int count);
int		ft_check_map(t_data *data);
void	ft_parse_position(t_data *data, int i, int j);
void	parse_color(t_data *data, char *line);
void	parse_path(t_data *data, char *line);
char	*pathing(char *line, int *check);
void	parse_res(t_data *data, char *line);
int		ft_game_loop(t_data *data, int **map);
int		ft_setup_mlx(t_data *data, int **map);
void	ft_setup_rays(t_data *data);
int		ft_main_loop(int keycode, void *param);
float	ft_toradian(float angle);
int		ft_isargvalid(char c);
int		ft_search_arg(char *line, char *set);
float	ft_get_angle(t_data *data, int **map);
void	ft_coloriage(t_data *data, int i, int j, unsigned int color);
void	ft_setbackground(t_data *data);
void	do_rays(t_data *data);
void	ft_setray(t_data *data, int i);
float	get_dist(t_data *data, int i);
void	ft_do_colum(t_data *data);
void	ft_dda(t_data *data, int i);
void	ft_perform_dda(t_data *data, int i);
void	ft_init_perform_dda(t_data *data, int i, t_int *x_, t_int *y_);
float	get_theta(t_data *data, int i);
void	do_dist(t_data *data, t_int *x_, t_int *y_, int i);
int		ft_dox(t_data *data, t_int *x_, int i);
int		ft_doy(t_data *data, t_int *y_, int i);
void	ft_init_deltas(t_data *data, t_int *x_, t_int *y_, int i);
int		ft_choose_color(t_data *data, int i);
int		ft_keyboard_loop(t_data *data);
void	ft_do_colision(t_data *data, int choice);
int		ft_collision2(t_data *data, float ad_x, float ad_y);
void	ft_strafe(t_data *data, int id);
void	ft_advance(t_data *data, float angle, int param);
void	ft_collision(t_data *data, float angle);
void	ft_collision_back(t_data *data, float angle);
int		ft_collision_back2(t_data *data, float ad_x, float ad_y);
int		ft_get_dist_info(t_data *data, int i);
void	free_paths(t_data *data);
int		ft_setup_tex(t_data *data);
void	ft_get_info_tex(t_tex *tex);
int		ft_get_tex_xpixel(t_data *data, t_color *color, int i);
void	ft_get_tex_ypixel(t_data *data, t_color *color);
void	ft_init_t_color(t_data *data, t_color *color, int i, int *j);
void	ft_do_tsprite(t_data *data);
void	ft_check_if_hit(t_data *data);
void	ft_reset_tsprite(t_sprite *tsprite, int s_max, t_data *data);
void	ft_do_dist_sprite(t_data *data);
void	ft_init_dist_tsprite(t_data *data, float *distx, float *disty, int i);
void	ft_draw_sprites(t_data *data, int pixel, int sizex, t_sprite *sprite);
void	ft_draw_a_colum_sprite(t_data *data, int i, int hp, int xpixel);
void	ft_init_draw_sprite(t_data *data, int *j, int *n_pixel, int hp);
void	ft_check_if_visible(t_data *data);
float	ft_abs(float n);
void	ft_zbuffer(t_data *data, t_sprite *sprite, float pas);
int		ft_raying_sprite(t_data *data, float angle_s);
void	ft_get_tex_ypixel_sprite(t_data *data, int *tab, unsigned char *color);
void	ft_do_sort_sprite(t_data *data);
void	ft_swap_sprite(t_sprite *a, t_sprite *b);
void	ft_swap_sprite2(t_sprite *a, t_sprite *b);
float	to_d(float radian);
float	lissage_angle(float angle);
int		ft_comp_sprite_angle(float angle_f, float angle_l, t_data *data);
void	ft_do_looping(t_data *data);
int		keypress(int keycode, void *param);
int		keyrelease(int keycode, void *param);
void	ft_clear_list(void *content);
void	ft_freemap(t_data *data);
void	ft_exit_all(t_data *data);
void	ft_free_map(t_data *data);
void	ft_free_vec(t_data *data);
void	ft_free_dda(t_data *data);
void	ft_free_tsprite(t_data *data);
void	ft_free_tex(t_data *data);
void	ft_lst_free(t_list **lst);
int		exit_program(int keycode, void *param);
void	ft_sparadrap(t_data *data, int i);
int		ft_iserror_map(t_data *data, int j);
int		ft_fd_nul(int fd);
int		ft_parse_stuff3(t_data *data, t_list **lst, size_t count);

#endif
