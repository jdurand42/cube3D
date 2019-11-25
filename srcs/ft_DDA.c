/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_DDA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:31:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/25 20:58:36 by jdurand          ###   ########.fr       */
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
	float		theta;
	t_intercept	x_;
	t_intercept	y_;

	theta = get_theta(data, i);

	x_.delta = data->dda[i].dx * tan(ft_toradian(theta));
	y_.delta = data->dda[i].dy / tan(ft_toradian(theta));
	x_.x = data->vectors[i].x1 + (data->dda[i].dx * data->dda[i].xsign);
	x_.y = data->vectors[i].y1 + (x_.delta * data->dda[i].ysign);
	y_.x = data->vectors[i].x1 + (y_.delta * data->dda[i].xsign);
	y_.y = data->vectors[i].y1 + (data->dda[i].dy * data->dda[i].ysign);
	x_.delta = tan(ft_toradian(theta)) * data->dda[i].ysign;
	y_.delta = 1 / (tan(ft_toradian(theta))) * data->dda[i].xsign;

		printf("x_x: %lf, x_y : %lf\n", x_.x, x_.y);
	while (data->map[(int)x_.y][(int)x_.x] == 0)
	{
		x_.x += data->dda[i].xsign;
		x_.y += x_.delta;
		printf("x_x: %lf, x_y : %lf\n", x_.x, x_.y);

	}
	printf("y_x: %lf, y_y : %lf\n", y_.x, y_.y);
	while (data->map[(int)y_.y][(int)y_.x] == 0)
	{
		y_.y += data->dda[i].ysign;
		y_.x += y_.delta;
		printf("y_x: %lf, y_y : %lf\n", y_.x, y_.y);
	}
	printf("ray: %d, theta :%f\n", i, theta);
	do_dist(data, &x_, &y_, i);
	printf(GREEN "---\n" RESET);
}

void 	do_dist(t_data *data, t_intercept *x_, t_intercept *y_, int i)
{
	float	dist_x;
	float	dist_y;

	dist_x = sqrt(((x_->x - data->vectors[i].x1) * (x_->x - data->vectors[i].x1)) +
				((x_->y - data->vectors[i].y1) * (x_->y - data->vectors[i].y1)));
	dist_y = sqrt(((y_->x - data->vectors[i].x1) * (y_->x - data->vectors[i].x1)) +
				((y_->y - data->vectors[i].y1) * (y_->y - data->vectors[i].y1)));
	if (dist_x < dist_y)
	{
		data->vectors[i].wall_type = 1;
		data->vectors[i].dist_towall = dist_x;
	}
	else
	{
		data->vectors[i].wall_type = 0;
		data->vectors[i].dist_towall = dist_y;
	}
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
