/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_DDA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:31:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/28 19:09:33 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_dda(t_data *data, int i)
{
	if (data->vec[i].rotx > 0) // Look right 270 - 90
	{
		// posx < dirx
		data->dda[i].xsign = 1;
		data->dda[i].dx = (int)(data->vec[i].x1) + 1 - data->vec[i].x1;
//		if (data->dda[i].dx == (int)data->dda[i].dx)
//			data->dda[i].dx = 1;
	}
	else if (data->vec[i].rotx < 0) // look left 90 - 270
	{
		//posx > dix
		data->dda[i].xsign = -1;
		data->dda[i].dx = data->vec[i].x1 - (int)(data->vec[i].x1);
	//	if (data->dda[i].dx == (int)data->dda[i].dx)
	//		data->dda[i].dx = 1;
	}
	if (data->vec[i].roty > 0) // look up 0 - 180
	{
		//posy > diry
		data->dda[i].ysign = -1;
		data->dda[i].dy = data->vec[i].y1 - (int)(data->vec[i].y1);
//		if (data->dda[i].dy == (int)data->dda[i].dy)
//			data->dda[i].dy = 1;
	}
	else if (data->vec[i].roty < 0) // look down 180 - 360
	{
		//posy < diry
		data->dda[i].ysign = 1;
		data->dda[i].dy = (int)(data->vec[i].y1) + 1 - data->vec[i].y1;
	//	if (data->dda[i].dy == (int)data->dda[i].dy)
	//		data->dda[i].dy = 1;
	}

//	printf("ray : %d, dx : %.15f, dy: %.15f, angle: %f\n", i, data->dda[i].dx, data->dda[i].dy, data->vec[i].angle);
	ft_perform_dda(data, i);
}

void 	ft_perform_dda(t_data *data, int i)
{
	float		tan_theta;
	int 		ret;
	t_intercept	x_;
	t_intercept	y_;

	tan_theta = tan(ft_toradian(get_theta(data, i)));
	x_.delta = data->dda[i].dx * tan_theta;
	y_.delta = data->dda[i].dy / tan_theta;
	ft_init_deltas(data, &x_, &y_, i);
	x_.delta = tan_theta * data->dda[i].ysign;
	y_.delta = 1 / tan_theta * data->dda[i].xsign;
	ret = 0;

//	printf("x_x: %lf, x_y : %lf\n", x_.x, x_.y);
//	printf("y_x, y_y, %lf, %lf\n",y_.x, y_.y);
//	printf("roty: %lf\n", data->vec[i].roty);
	if (data->vec[i].roty > 0 && data->vec[i].roty != 1)
	{
		while (x_.y > 0 && ret == 0)
			ret = ft_dox(data, &x_, i);
	}
	else if (data->vec[i].roty != -1)
		while (x_.y < data->height - 1 && ret == 0)
			ret = ft_dox(data, &x_, i);
	ret = 0;
	if (data->vec[i].rotx > 0)
	{
		while (y_.x < data->width - 1 && ret == 0)
			ret = ft_doy(data, &y_, i);
	}
	else
		while (y_.x > 0 && ret == 0)
			ret = ft_doy(data, &y_, i);
//	printf("ray: %d, theta :%f\n", i, theta);
	do_dist(data, &x_, &y_, i);
	//printf(GREEN "---\n" RESET);
}

int 	ft_dox(t_data *data, t_intercept *x_, int i)
{
	//printf("deltax : %lf\nx, y : %lf %lf\n, x_, x_y: %lf %lf\n", x_->delta, data->posx, data->posy, x_->x, x_->y);
	if (data->vec[i].rotx < 0)
	{
		if (data->map[(int)x_->y][(int)x_->x + data->dda[i].xsign] > 0)
		{
			x_->dist = sqrt(((x_->x - data->vec[i].x1) * (x_->x - data->vec[i].x1)) +
			((x_->y - data->vec[i].y1) * (x_->y - data->vec[i].y1)));
			return (1);
		}
	}
	else
	{
	if (data->map[(int)x_->y][(int)x_->x] > 0)
	{
			x_->dist = sqrt(((x_->x - data->vec[i].x1) * (x_->x - data->vec[i].x1)) +
			((x_->y - data->vec[i].y1) * (x_->y - data->vec[i].y1)));
			return (1);
	}
	}
	x_->x += data->dda[i].xsign;
	x_->y += x_->delta;
//	printf("x_x: %lf, x_y : %lf\n", x_->x, x_->y);
	return (0);
}

int 	ft_doy(t_data *data, t_intercept *y_, int i)
{
	if (data->vec[i].roty > 0)
	{
	if (data->map[(int)y_->y + data->dda[i].ysign][(int)y_->x] > 0)
	{
		y_->dist = sqrt(((y_->x - data->vec[i].x1) * (y_->x - data->vec[i].x1)) +
		((y_->y - data->vec[i].y1) * (y_->y - data->vec[i].y1)));
		return (1);
	}
	}
	else
	{
		if (data->map[(int)y_->y][(int)y_->x] > 0)
		{
			y_->dist = sqrt(((y_->x - data->vec[i].x1) * (y_->x - data->vec[i].x1)) +
			((y_->y - data->vec[i].y1) * (y_->y - data->vec[i].y1)));
			return (1);
		}
	}
	y_->y += data->dda[i].ysign;
	y_->x += y_->delta;
//	printf("y_x: %lf, y_y : %lf\n", y_->x, y_->y);
	return (0);
}


void 	do_dist(t_data *data, t_intercept *x_, t_intercept *y_, int i)
{
	float	dist_x;
	float	dist_y;

//	printf("%lf, %lf\n", x_->dist, y_->dist);
	if ((x_->dist < y_->dist && x_->dist >= 0) || !(y_->dist >= 0))
	{
		data->vec[i].wall_type = 0;
		data->vec[i].dist_towall = x_->dist;
	}
	else
	{
		data->vec[i].wall_type = 1;
		data->vec[i].dist_towall = y_->dist;
	}
}

float	get_theta(t_data *data, int i)
{
	if (data->vec[i].angle <= 90 && data->vec[i].angle > 0)
		return(data->vec[i].angle);
	else if (data->vec[i].angle <= 180 && data->vec[i].angle > 90)
		return(90 - (data->vec[i].angle - 90));
	else if (data->vec[i].angle <= 270 && data->vec[i].angle > 180)
		return(data->vec[i].angle - 180);
	else if (data->vec[i].angle <= 360)
		return(90 - (data->vec[i].angle - 270));
	return (0);
}

void 	ft_init_deltas(t_data *data, t_intercept *x_, t_intercept *y_, int i)
{
	x_->x = data->vec[i].x1 + (data->dda[i].dx * data->dda[i].xsign);
	x_->y = data->vec[i].y1 + (x_->delta * data->dda[i].ysign);
	y_->x = data->vec[i].x1 + (y_->delta * data->dda[i].xsign);
	y_->y = data->vec[i].y1 + (data->dda[i].dy * data->dda[i].ysign);
	x_->dist = -1;
	y_->dist = -1;
}
