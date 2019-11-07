/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:55:14 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/07 17:49:20 by jdurand          ###   ########.fr       */
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

typedef struct	s_data
{
	int					Rx;
	int 				Ry;
	char				*NO;
	char				*SO;
	char 				*WE;
	char 				*ES;
	char 				*S;
	unsigned char		F[3];
	unsigned char		C[3];
}				t_data;

int		ft_iserror(int code);
char	**ft_parse_map(int fd);

#endif
