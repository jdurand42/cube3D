/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_DDA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:31:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/23 19:19:34 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_dda(t_data *data, int i)
{
	if (data->vectors[i].rotx > 0) // Look right 270 - 90
	{
		// posx < dirx
		data->dda[i].xsign = 1;
		data->dda[i].dx = (int)(data->vectors[i].x1) + 1 - data->vectors[i].x1;
		if (data->dda[i].dx == (int)data->dda[i].dx)
			data->dda[i].dx = 1;
	}
	else if (data->vectors[i].rotx < 0) // look left 90 - 270
	{
		//posx > dix
		data->dda[i].xsign = -1;
		data->dda[i].dx = data->vectors[i].x1 - (int)(data->vectors[i].x1);
		if (data->dda[i].dx == (int)data->dda[i].dx)
			data->dda[i].dx = 1;
	}
	if (data->vectors[i].roty > 0) // look up 0 - 180
	{
		//posy > diry
		data->dda[i].ysign = -1;
		data->dda[i].dy = data->vectors[i].y1 - (int)data->vectors[i].y1;
		if (data->dda[i].dy == (int)data->dda[i].dy)
			data->dda[i].dy = 1;
	}
	else if (data->vectors[i].roty < 0) // look down 180 - 360
	{
		//posy < diry
		data->dda[i].ysign = 1;
		data->dda[i].dy = (int)data->vectors[i].y1 + 1 - data->vectors[i].y1;
		if (data->dda[i].dy == (int)data->dda[i].dy)
			data->dda[i].dy = 1;
	}
	if (data->dda[i].dx == 0)
	{
		data->dda[i].dx = 1;
		printf("youhou");
	}
//	if (data->dda[i].dy == 0)
//		data->dda[i].dy = 1;
	if (i == data->R[0] / 2 && data->vectors[i].angle == data->angle)
	{
		//printf(GREEN "dx: %lf, dy: %lf\n" RESET, data->dda[i].dx, data->dda[i].dy);
		//printf(GREEN "angle: %lf, cos: %lf, sin %lf\n" RESET, data->angle, data->vectors[i].rotx, data->vectors[i].roty);
	}
	printf("ray : %d, dx : %.15f, dy: %.15f, angle: %f\n", i, data->dda[i].dx, data->dda[i].dy, data->vectors[i].angle);
	ft_inc_rays(data, i);
}

void 	ft_inc_rays(t_data *data, int i)
{
	float	theta;
	float	delta;

	theta = get_theta(data, i);
	if (data->dda[i].dx < data->dda[i].dy) // || roty == 0 ou && rotx != 0
	{
		data->vectors[i].x1 = data->vectors[i].x1 + data->dda[i].dx * data->dda[i].xsign;
		data->vectors[i].y1 = data->vectors[i].y1 + (data->dda[i].dx / tan(ft_toradian(theta)) * data->dda[i].ysign);
	//	delta = (data->dda[i].dx * data->dda[i].dx) +
	//	((data->dda[i].dx * tan(theta)) * (data->dda[i].dx * tan(theta)));
	}
	else
	{
//		delta = (data->dda[i].dy * data->dda[i].dy) +
//		((data->dda[i].dy / tan(theta)) * (data->dda[i].dy / tan(theta)));
		data->vectors[i].x1 = data->vectors[i].x1 + (data->dda[i].dy * tan(ft_toradian(theta)) * data->dda[i].xsign);
		data->vectors[i].y1 = data->vectors[i].y1 + data->dda[i].dy * data->dda[i].ysign;
	}
	if (data->vectors[i].x1 < 0)
		data->vectors[i].x1 = 0;
	if (data->vectors[i].x1 >= data->width)
		data->vectors[i].x1 = data->width - 1;
	if (data->vectors[i].y1 < 0)
		data->vectors[i].y1 = 0;
	if (data->vectors[i].y1 >= data->height)
		data->vectors[i].y1 = data->height - 1;
//	data->vectors[i].x1 += (sqrt(delta) * data->vectors[i].rotx);
//	data->vectors[i].y1 -= (sqrt(delta) * data->vectors[i].roty);
}

float	get_theta(t_data *data, int i)
{
	float theta;

	if (data->vectors[i].angle <= 90 && data->vectors[i].angle > 0)
		theta = data->vectors[i].angle;
	else if (data->vectors[i].angle <= 180 && data->vectors[i].angle > 90) // angle inverse
		theta =  90 - data->vectors[i].angle - 90;
	else if (data->vectors[i].angle <= 270 && data->vectors[i].angle > 180)
		theta = data->vectors[i].angle - 180;
	else if (data->vectors[i].angle <= 360)
		theta = 90 - data->vectors[i].angle - 270;
	printf("%f\n", theta);
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
