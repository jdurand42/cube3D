/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_DDA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:31:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/21 14:55:47 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_dda(t_data *data, int i)
{
	double dir;

	if (data->vectors[i].rotx > 0) // Look right 270 - 90
	{
		// posx < dirx
		// double xsign = 1
		data->dda[i].sidex = (int)(data->vectors[i].x1) + 1 - data->vectors[i].x1;
	}
	else if (data->vectors[i].rotx < 0) // look left 90 - 270
	{
		//posx > dix
		// double xsign = -1
		data->dda[i].sidex = data->vectors[i].x1 - (int)(data->vectors[i].x1);
	}
	if (data->vectors[i].roty > 0) // look up 0 - 180
	{
		//posy > diry
		// double ysign = -1
		data->dda[i].sidey = (int)(data->vectors[i].y1) + 1 - data->vectors[i].y1; // inverse je crois
	}
	else if (data->vectors[i].roty < 0) // look down 180 - 360
	{
		//posy < diry
		// double ysign = 1;
		data->dda[i].sidey = data->vectors[i].y1 - (int)(data->vectors[i].y1);
	}
	if (i == data->R[0] / 2 && data->vectors[i].angle == data->angle)
	{
		//printf(GREEN "sidex: %lf, sidey: %lf\n" RESET, data->dda[i].sidex, data->dda[i].sidey);
		//printf(GREEN "angle: %lf, cos: %lf, sin %lf\n" RESET, data->angle, data->vectors[i].rotx, data->vectors[i].roty);
	}
	return ;
}


/*
if (dx < dy)
{
	vectors[i].x1 = vectors[i].x1 + data->dda[i].sidex * xsign;
	vectors[i].y1 = vectors[i].y1 + data->dda[i].sidey / tan(theta) * ysign;
}
else
{
	vectors[i].x1 = vectors[i].x1 + data->dda[i].sidex * tan(theta) * xsign;
	vectors[i].y1 = vectors[i].y1 + data->dda[i].sidey * ysign;
}
// vec.angle = vec.angle - (90)(180)(270)
*/
