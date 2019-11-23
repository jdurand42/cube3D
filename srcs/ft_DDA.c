/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_DDA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:31:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/23 16:24:07 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_dda(t_data *data, int i)
{
	float dir;

	if (data->vectors[i].rotx > 0) // Look right 270 - 90
	{
		// posx < dirx
		data->dda[i].xsign = 1;
		data->dda[i].dx = (int)(data->vectors[i].x1) + 1 - data->vectors[i].x1;
	}
	else if (data->vectors[i].rotx < 0) // look left 90 - 270
	{
		//posx > dix
		data->dda[i].xsign = -1;
		data->dda[i].dx = data->vectors[i].x1 - (int)(data->vectors[i].x1);
	}
	if (data->vectors[i].roty > 0) // look up 0 - 180
	{
		//posy > diry
		data->dda[i].ysign = -1 // inverse je crois
		data->dda[i].dy = data->vectors[i].y1 - (int)(data->vectors[i].y1);
	}
	else if (data->vectors[i].roty < 0) // look down 180 - 360
	{
		//posy < diry
		data->dda[i].ysign = 1;
		data->dda[i].dy = (int)(data->vectors[i].y1) + 1 - data->vectors[i].y1;
	}
	if (i == data->R[0] / 2 && data->vectors[i].angle == data->angle)
	{
		//printf(GREEN "dx: %lf, dy: %lf\n" RESET, data->dda[i].dx, data->dda[i].dy);
		//printf(GREEN "angle: %lf, cos: %lf, sin %lf\n" RESET, data->angle, data->vectors[i].rotx, data->vectors[i].roty);
	}

}

void 	ft_inc_rays(t_data *data, int i)
{
	float	theta;

	theta = get_theta(data, i);
	if (data->dda[i].dx > data->dda[i].dy)
	{
		data->vectors[i].x1 = data->vectors[i].x1 + data->dda[i].dx * data->dda[i].xsign;
		data->vectors[i].y1 = data->vectors[i].y1 + (data->dda[i].dy / tan(ft_toradian(theta)) * data->dda[i].ysign;
	}
	else
	{
		data->vectors[i].x1 = data->vectors[i].x1 + (data->dda[i].dx * tan(ft_toradian(theta)) * data->dda[i].xsign);
		data->vectors[i].y1 = data->vectors[i].y1 + data->dda[i].dy * data->dda[i].ysign;
	}
}

float	get_theta(t_data *data, int i)
{
	if (data->vectors[i].angle < 90 && data->vectors[i].angle > 0)
		theta = data->vectors[i].angle;
	else if (data->vectors[i].angle < 180 && data->vectors[i].angle > 90)
		theta = data->vectors[i].angle - 90;
	else if (data->vectors[i].angle < 270 && data->vectors[i].angle > 180)
		theta = data->vectors[i].angle - 180;
	else if (data->vectors[i].angle < 360)
		theta = data->vectors[i].angle - 270;
	return (theta);
}

/*
if (dx < dy)
{
	vectors[i].x1 = vectors[i].x1 + data->dda[i].dx * xsign;
	vectors[i].y1 = vectors[i].y1 + data->dda[i].dy / tan(theta) * ysign;
}
else
{
	vectors[i].x1 = vectors[i].x1 + data->dda[i].dx * tan(theta) * xsign;
	vectors[i].y1 = vectors[i].y1 + data->dda[i].dy * ysign;
}
// vec.angle = vec.angle - (90)(180)(270)
*/
