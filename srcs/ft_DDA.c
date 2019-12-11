/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_DDA.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:31:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 18:34:26 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_dda(t_data *data, int i)
{
	if (data->vec[i].rotx > 0) // Look right 270 - 90
	{
		data->dda[i].xsign = 1;
		data->dda[i].dx = (int)(data->vec[i].x1) + 1 - data->vec[i].x1;
	}
	else if (data->vec[i].rotx < 0) // look left 90 - 270
	{
		data->dda[i].xsign = -1;
		data->dda[i].dx = data->vec[i].x1 - (int)(data->vec[i].x1);
	}
	if (data->vec[i].roty > 0) // look up 0 - 180
	{
		data->dda[i].ysign = -1;
		data->dda[i].dy = data->vec[i].y1 - (int)(data->vec[i].y1);
	}
	else if (data->vec[i].roty < 0) // look down 180 - 360
	{
		data->dda[i].ysign = 1;
		data->dda[i].dy = (int)(data->vec[i].y1) + 1 - data->vec[i].y1;
	}
//	printf("ray : %d, dx : %.15f, dy: %.15f, angle: %f\n", i, data->dda[i].dx, data->dda[i].dy, data->vec[i].angle);
	ft_perform_dda(data, i);
}

void 	ft_perform_dda(t_data *data, int i)
{
	int 		ret;
	t_int 		*x_;
	t_int		*y_;

	x_ = &data->x_[i];
	y_ = &data->y_[i];
	ft_init_perform_dda(data, i, x_, y_);
	ret = 0;
	if (data->vec[i].roty > 0)
	{
		while (x_->y > 1 && ret == 0)
			ret = ft_dox(data, x_, i);
	}
	else
		while (x_->y < data->height - 2 && ret == 0)
			ret = ft_dox(data, x_, i);
	ret = 0;
	if (data->vec[i].rotx > 0)
	{
		while (y_->x < data->width - 2 && ret == 0)
			ret = ft_doy(data, y_, i);
	}
	else
		while (y_->x > 1 && ret == 0)
			ret = ft_doy(data, y_, i);
	do_dist(data, x_, y_, i);
}

int 	ft_dox(t_data *data, t_int *x_, int i)
{
	printf("deltax : %lf\ntan: %lf, theta: %lf\n, x_, x_y: %lf %lf, angle: %lf\n", x_->delta, data->vec[i].tan_theta, get_theta(data, i), x_->x, x_->y, data->vec[i].angle);
	if (data->vec[i].rotx < 0 && x_->y < data->height - 1)
	{
		if (data->map[(int)x_->y][(int)x_->x + data->dda[i].xsign] == 1)
		{
			x_->dist = sqrt(((x_->x - data->vec[i].x1) * (x_->x - data->vec[i].x1)) +
			((x_->y - data->vec[i].y1) * (x_->y - data->vec[i].y1)));
			data->vec[i].id_wallx = x_->y - (int)x_->y;
			return (1);
		}
	}
	else if (x_->y < data->height - 1)
	{
		if (data->map[(int)x_->y][(int)x_->x] == 1)
		{
			x_->dist = sqrt(((x_->x - data->vec[i].x1) * (x_->x - data->vec[i].x1)) +
			((x_->y - data->vec[i].y1) * (x_->y - data->vec[i].y1)));
			data->vec[i].id_wallx = x_->y - (int)x_->y;
			return (1);
		}
	}
	x_->x += data->dda[i].xsign;
	x_->y += x_->delta;
	return (0);
}

int 	ft_doy(t_data *data, t_int *y_, int i)
{
	if (data->vec[i].roty > 0)
	{
		if (data->map[(int)y_->y + data->dda[i].ysign][(int)y_->x] == 1)
		{
			y_->dist = sqrt(((y_->x - data->vec[i].x1) * (y_->x - data->vec[i].x1)) +
			((y_->y - data->vec[i].y1) * (y_->y - data->vec[i].y1)));
			data->vec[i].id_wally = y_->x - (int)y_->x;
			return (1);
		}
	}
	else
	{
		if (data->map[(int)y_->y][(int)y_->x] == 1)
		{
			y_->dist = sqrt(((y_->x - data->vec[i].x1) * (y_->x - data->vec[i].x1)) +
			((y_->y - data->vec[i].y1) * (y_->y - data->vec[i].y1)));
			data->vec[i].id_wally = y_->x - (int)y_->x;
			return (1);
		}
	}
	y_->y += data->dda[i].ysign;
	y_->x += y_->delta;
	return (0);
}


void 	do_dist(t_data *data, t_int *x_, t_int *y_, int i)
{
	float	dist_x;
	float	dist_y;

	if ((x_->dist < y_->dist && x_->dist >= 0) || !(y_->dist >= 0))
	{
		data->vec[i].wall_type = 0;
		data->vec[i].dist_towall = x_->dist;
		data->vec[i].id_wally = -1;
	}
	else
	{
		data->vec[i].wall_type = 1;
		data->vec[i].dist_towall = y_->dist;
		data->vec[i].id_wallx = -1;
	}
}
