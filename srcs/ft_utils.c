/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:14:40 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/23 16:25:09 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int 	ft_isargvalid(char c)
{
	if (c == '1' || c == '0' || c == '2' || c == 'N' || c == 'E' || c == 'W' ||
	c == 'S')
		return (1);
	else
		return (0);
}

int		ft_search_arg(char *line, char *set)
{
	while (*line != 0)
	{
		if (*line == ' ') // whitespace?
			line++;
		else
			while (*set  != 0)
			{
				if (*line == *set)
					return (1);
				set++;
			}
		line++;
	}
	return (0);
}

float 			ft_toradian(float angle)
{
	return ((pi / 180) * angle);
}

unsigned int 	ft_rgb(int r, int g, int b)
{
	unsigned int color;

	color = 0;
	color |= (b << 0);
	color |= (g << 8);
	color |= (r << 16);
	return (color);
}

int 	ft_get_angle(t_data *data, int **map)
{
	float angle;

	if (map[(int)data->posy][(int)data->posx] + '0' == 'N')
		angle = 90;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'E')
		angle = 0;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'S')
	 	angle = 270;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'W')
		angle = 180;
	map[(int)data->posy][(int)data->posx] = 0;
	return (angle);
}
