/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:26:49 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 15:10:01 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

float			ft_toradian(float angle)
{
	return ((PI / 180) * angle);
}

float			to_d(float radian)
{
	return (radian * (180 / PI));
}

float			lissage_angle(float angle)
{
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 359)
		angle = angle - 359;
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 359)
		angle = angle - 359;
	return (angle);
}

unsigned int	coloring(char *line, int *check)
{
	size_t			j;
	size_t			i;
	unsigned char	rgb[3];

	i = 0;
	j = 0;
	while (line[i] != 0 && j < 3)
	{
		while (line[i] != 0 && !ft_isdigit(line[i]))
			i++;
		if (ft_isdigit(line[i]))
			rgb[j++] = (unsigned char)ft_atoi(&line[i]);
		while (line[i] != 0 && ft_isdigit(line[i]))
			i++;
	}
	if (j == 3)
		*check += 1;
	else
	{
		*check = -1;
		return (0);
	}
	printf("color F-C: %u\n", rgb[2]);
	return (ft_rgb(rgb[0], rgb[1], rgb[2]));
}
