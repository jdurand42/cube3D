/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:55:14 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/09 16:56:44 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../libft/libft.h"
# include "minilibX_all.h"
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_data
{
	int					check;
	int 				width;
	int					height;
	int					R[2];
	char				*NO;
	char				*SO;
	char 				*WE;
	char 				*ES;
	char 				*S;
	unsigned char		F[3];
	unsigned char		C[3];
}				t_data;

int		ft_iserror(int code);
int		**ft_parse_stuff(t_data *data, int fd);
int		ft_search_arg(char *line, char *set);
void 	parse_map(t_data *data, char *line);
void 	parse_color(t_data *data, char *line);
void 	parse_path(t_data *data, char *line);
char	*pathing(char *path, char *line, int *check);
void 	parse_res(t_data *data, char *line);

#endif
