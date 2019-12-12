/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:31:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 17:30:10 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_dda(t_data *data, int i)
{
	if (data->vec[i].rotx > 0)
	{
		data->dda[i].xsign = 1;
		data->dda[i].dx = (int)(data->vec[i].x1) + 1 - data->vec[i].x1;
	}
	else if (data->vec[i].rotx < 0)
	{
		data->dda[i].xsign = -1;
		data->dda[i].dx = data->vec[i].x1 - (int)(data->vec[i].x1);
	}
	if (data->vec[i].roty > 0)
	{
		data->dda[i].ysign = -1;
		data->dda[i].dy = data->vec[i].y1 - (int)(data->vec[i].y1);
	}
	else if (data->vec[i].roty < 0)
	{
		data->dda[i].ysign = 1;
		data->dda[i].dy = (int)(data->vec[i].y1) + 1 - data->vec[i].y1;
	}
	ft_perform_dda(data, i);
}

void	ft_perform_dda(t_data *data, int i)
{
	int		ret;
	t_int	x_;
	t_int	y_;

	ft_init_perform_dda(data, i, &x_, &y_);
	ret = 0;
	if (data->vec[i].rotx > 0)
	{
		while (y_.x < data->width - 1 && y_.x > 0 && ret == 0)
			ret = ft_doy(data, &y_, i);
	}
	else
		while (y_.x > 0 && y_.x < data->width - 1 && ret == 0)
			ret = ft_doy(data, &y_, i);
	ret = 0;
	if (data->vec[i].roty < 0)
		while (x_.y < data->height - 1 && x_.y > 0 && ret == 0)
			ret = ft_dox(data, &x_, i);
	else if (data->vec[i].roty > 0 && data->vec[i].angle != 270)
	{
		while (x_.y > 0 && x_.y < data->height - 1 && ret == 0)
			ret = ft_dox(data, &x_, i);
	}
	do_dist(data, &x_, &y_, i);
}

int		ft_dox(t_data *data, t_int *x_, int i)
{
	if (data->vec[i].rotx < 0)
	{
		if (data->map[(int)x_->y][(int)x_->x + data->dda[i].xsign] == 1)
		{
			x_->dist = sqrt(((x_->x - data->vec[i].x1) *
			(x_->x - data->vec[i].x1)) +
			((x_->y - data->vec[i].y1) * (x_->y - data->vec[i].y1)));
			data->vec[i].id_wallx = x_->y - (int)x_->y;
			return (1);
		}
	}
	else if (x_->y < data->height - 1)
	{
		if (data->map[(int)x_->y][(int)x_->x] == 1)
		{
			x_->dist = sqrt(((x_->x - data->vec[i].x1) *
			(x_->x - data->vec[i].x1)) +
			((x_->y - data->vec[i].y1) * (x_->y - data->vec[i].y1)));
			data->vec[i].id_wallx = x_->y - (int)x_->y;
			return (1);
		}
	}
	x_->x += data->dda[i].xsign;
	x_->y += x_->delta;
	return (0);
}

int		ft_doy(t_data *data, t_int *y_, int i)
{
	if (data->vec[i].roty > 0)
	{
		if (data->map[(int)y_->y + data->dda[i].ysign][(int)y_->x] == 1)
		{
			y_->dist = sqrt(((y_->x - data->vec[i].x1) *
			(y_->x - data->vec[i].x1)) +
			((y_->y - data->vec[i].y1) * (y_->y - data->vec[i].y1)));
			data->vec[i].id_wally = y_->x - (int)y_->x;
			return (1);
		}
	}
	else
	{
		if (data->map[(int)y_->y][(int)y_->x] == 1)
		{
			y_->dist = sqrt(((y_->x - data->vec[i].x1) *
			(y_->x - data->vec[i].x1)) +
			((y_->y - data->vec[i].y1) * (y_->y - data->vec[i].y1)));
			data->vec[i].id_wally = y_->x - (int)y_->x;
			return (1);
		}
	}
	y_->y += data->dda[i].ysign;
	y_->x += y_->delta;
	return (0);
}

void	do_dist(t_data *data, t_int *x_, t_int *y_, int i)
{
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
