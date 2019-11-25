/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_DDA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:31:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/25 18:36:38 by jdurand          ###   ########.fr       */
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
//		if (data->dda[i].dx == (int)data->dda[i].dx)
//			data->dda[i].dx = 1;
	}
	else if (data->vectors[i].rotx < 0) // look left 90 - 270
	{
		//posx > dix
		data->dda[i].xsign = -1;
		data->dda[i].dx = data->vectors[i].x1 - (int)(data->vectors[i].x1);
	//	if (data->dda[i].dx == (int)data->dda[i].dx)
	//		data->dda[i].dx = 1;
	}
	if (data->vectors[i].roty > 0) // look up 0 - 180
	{
		//posy > diry
		data->dda[i].ysign = -1;
		data->dda[i].dy = (int)(data->vectors[i].y1) + 1 - data->vectors[i].y1;

//		if (data->dda[i].dy == (int)data->dda[i].dy)
//			data->dda[i].dy = 1;
	}
	else if (data->vectors[i].roty < 0) // look down 180 - 360
	{
		//posy < diry
		data->dda[i].ysign = 1;
				printf("la\n");
		data->dda[i].dy = data->vectors[i].y1 - (int)(data->vectors[i].y1);
	//	if (data->dda[i].dy == (int)data->dda[i].dy)
	//		data->dda[i].dy = 1;
	}

	printf("ray : %d, dx : %.15f, dy: %.15f, angle: %f\n", i, data->dda[i].dx, data->dda[i].dy, data->vectors[i].angle);
	ft_inc_rays(data, i);
}

void 	ft_inc_rays(t_data *data, int i)
{
	float	theta;
	float	deltax;
	float	deltay;

	theta = get_theta(data, i);
	printf("%lf, %lf\n", data->vectors[i].roty, data->vectors[i].rotx);
	if (theta != 90 && theta != 270)
		deltax = data->dda[i].dx * tan(ft_toradian(theta));
	else
		deltax = data->dda[i].dx;
	if (theta != 90 && theta != 270)
	{
		deltay = data->dda[i].dy / tan(ft_toradian(theta));
		printf(GREEN "%lf, %lf\n" RESET, data->dda[i].dy / tan(ft_toradian(theta)), data->dda[i].dy);
	}
	else
		deltay = data->dda[i].dy;
	printf("%.15lf, %.15lf\n", deltax, deltay);
	if (deltax < deltay && data->dda[i].dx != 0)
	{
		data->vectors[i].x1 = data->vectors[i].x1 + (data->dda[i].dx *  data->dda[i].xsign);
		data->vectors[i].y1 = data->vectors[i].y1 + (deltax * data->dda[i].ysign);
	}
	else
	{
		data->vectors[i].x1 = data->vectors[i].x1 + (deltay * data->dda[i].xsign);
		data->vectors[i].y1 = data->vectors[i].y1 + (data->dda[i].dy * data->dda[i].ysign);
	}
	printf("ray: %d, theta :%f\n", i, theta);
	printf(GREEN "---\n" RESET);
}

float	get_theta(t_data *data, int i)
{
	float theta;

	if (data->vectors[i].angle <= 90 && data->vectors[i].angle > 0)
		theta = data->vectors[i].angle;
	else if (data->vectors[i].angle <= 180 && data->vectors[i].angle > 90)
		theta = 90 - (data->vectors[i].angle - 90);
	else if (data->vectors[i].angle <= 270 && data->vectors[i].angle > 180)
		theta = data->vectors[i].angle - 180;
	else if (data->vectors[i].angle <= 360)
		theta = 90 - (data->vectors[i].angle - 270);
	printf("theta : %f\n", theta);
	return (theta);
}
