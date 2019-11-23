/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_DDA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:31:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/21 17:52:12 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_dda(t_data *data, int i)
{
	double dir;
	double anglex;
	double angley;

	//ft_get_angles(data, &anglex, &angley, i);
	if (data->vectors[i].rotx > 0) // Look right 270 - 90
	{
		// posx < dirx
		data->dda[i].sidex = (int)(data->vectors[i].x1) + 1 - data->vectors[i].x1;
	}
	else if (data->vectors[i].rotx < 0) // look left 90 - 270
	{
		//posx > dix
		data->dda[i].sidex = data->vectors[i].x1 - (int)(data->vectors[i].x1);
	}
	if (data->vectors[i].roty > 0) // look up 0 - 180
	{
		//posy > diry
		data->dda[i].sidey = (int)(data->vectors[i].y1) + 1 - data->vectors[i].y1;
	}
	else if (data->vectors[i].roty < 0) // look down 180 - 360
	{
		//posy < diry
		data->dda[i].sidey = data->vectors[i].y1 - (int)(data->vectors[i].y1);
	}
	if ()
	//if (i == data->R[0] / 2 && data->vectors[i].angle == data->angle)
	//{
	//	printf(GREEN "move : x, y : %lf %lf\n", data->dda[i].movex, data->dda[i].movey);
	//	printf("%lf %lf\n", data->posx, data->posy);
		//printf(GREEN "sidex: %lf, sidey: %lf\n" RESET, data->dda[i].sidex, data->dda[i].sidey);
		//printf(GREEN "angle: %lf, cos: %lf, sin %lf\n" RESET, data->angle, data->vectors[i].rotx, data->vectors[i].roty);
	//}
	return ;
}
/*
void 	ft_get_angles(t_data *data, double *anglex, double *angley, int i)
{
	if (data->vectors[i].angle < 90)
	{
		*angley = data->vectors[i].angle;
		*anglex = 90 - *angley;
	}
	else if (data->vectors[i].angle > 90 && data->vectors[i].angle < 180)
	{
		*angley = data->vectors[i].angle - 90;
		*anglex = 90 - *angley;
	}
	else if (data->vectors[i].angle > 180 && data->vectors[i].angle < 270)
	{
		*angley = data->vectors[i].angle - 180;
		*anglex = 90 - *angley;
	}
	else if (data->vectors[i].angle > 270)
	{
		*angley = data->vectors[i].angle - 270;
		*anglex = 90 - *angley;
	}
	//if (i == data->R[0] / 2)
	//	printf(GREEN "%lf, angle i: %lf %lf\n" RESET, data->angle, *anglex, *angley);
}
*/
