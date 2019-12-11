/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_DDA2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:14:37 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 18:38:00 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_init_perform_dda(t_data *data, int i, t_int *x_, t_int *y_)
{
	if (get_theta(data, i) != 90)
		data->vec[i].tan_theta = tan(ft_toradian(get_theta(data, i)));
	x_->delta = data->dda[i].dx * data->vec[i].tan_theta;
	y_->delta = data->dda[i].dy / data->vec[i].tan_theta;
	ft_init_deltas(data, x_, y_, i);
	x_->delta = data->vec[i].tan_theta * data->dda[i].ysign;
	y_->delta = 1 / data->vec[i].tan_theta * data->dda[i].xsign;
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

void 	ft_init_deltas(t_data *data, t_int *x_, t_int *y_, int i)
{
	x_->x = data->vec[i].x1 + (data->dda[i].dx * data->dda[i].xsign);
	x_->y = data->vec[i].y1 + (x_->delta * data->dda[i].ysign);
	y_->x = data->vec[i].x1 + (y_->delta * data->dda[i].xsign);
	y_->y = data->vec[i].y1 + (data->dda[i].dy * data->dda[i].ysign);
	x_->dist = -1;
	y_->dist = -1;
}
