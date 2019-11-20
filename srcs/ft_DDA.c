/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_DDA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:31:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/20 19:50:39 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_dda(t_data *data, int i)
{
	double dir;
	double sidex;
	double sidey;

	if (data->vectors[i].rotx > 0) // Look right 270 - 90
	{
		// posx < dirx
		sidex = (int)data->vectors[i].x1 + 1 - data->vectors[i].x1;
	}
	else if (data->vectors[i].rotx < 0) // look left 90 - 270
	{
		//posx > dix
		sidex = data->vectors[i].x1 - (int)data->vectors[i].x1 ;
	}
	if (data->vectors[i].roty > 0) // look up 0 - 180
	{
		//posy > diry
		sidey = data->vectors[i].y1 - (int)data->vectors[i].y1;
	}
	else if (data->vectors[i].roty < 0) // look down 180 - 360
	{
		//posy < diry
		sidey = (int)data->vectors[i].y1 + 1 - data->vectors[i].y1;
	}
	if (i == data->R[0] / 2 && data->vectors[i].angle == data->angle)
		printf(GREEN "sidex: %lf, sidey: %lf\n" RESET, sidex, sidey);
}
