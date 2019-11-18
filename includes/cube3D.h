/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:55:14 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/18 15:41:10 by jdurand          ###   ########.fr       */
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

typedef struct	s_vector
{
	double	x0;
	double	y0;
	double	x1;
	double	y1;
}				t_vector;

typedef struct	s_data
{
	int					check;
	int 				width;
	int					height;
	double				posx;
	double				posy;
	double				angle;
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
	int 				size_line;
	int 				endian;
	int 				bit_p_p;
	int 				**map;
	struct s_vector 	*vectors;
}				t_data;

int		ft_iserror(int code);
int		**ft_parse_stuff(t_data *data, int fd);
void 	parse_map(t_data *data, char *line);
void 	parse_color(t_data *data, char *line);
void 	parse_path(t_data *data, char *line);
char	*pathing(char *path, char *line, int *check);
void 	parse_res(t_data *data, char *line);
void 	coloring(unsigned int *rgb, char *line, int *check);

int 	ft_game_loop(t_data *data, int **map);

int 			ft_setup_mlx(t_data *data, int **map);
void 	ft_setup_rays(t_data *data, int **map);
int 	ft_keyboard_loop(int keycode, void *params);

unsigned int 	ft_rgb(int r, int g, int b);
double 			ft_toradian(double angle);
int 	ft_isargvalid(char c);
int		ft_search_arg(char *line, char *set);

int 	ft_get_angle(t_data *data, int **map);

#endif
