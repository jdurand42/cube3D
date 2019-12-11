/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 20:47:23 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 21:10:25 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	ft_strafe(t_data *data, int id)
{
	float	strafe_angle;

	strafe_angle = data->cam.angle + (90 * id);
	if (strafe_angle > 359)
		strafe_angle = strafe_angle - 360;
	else if (strafe_angle < 0)
		strafe_angle = 360 + strafe_angle;
	ft_collision(data, strafe_angle);
}

void	ft_advance(t_data *data, float angle, int param)
{
	if (param == 1)
	{
		data->posy -= (sin(ft_toradian(angle)) * SPEED * SPEED_DIV);
		data->posx += (cos(ft_toradian(angle)) * SPEED * SPEED_DIV);
	}
	else if (param == 2)
	{
		data->posy += (sin(ft_toradian(angle)) * SPEED * SPEED_DIV);
		data->posx -= (cos(ft_toradian(angle)) * SPEED * SPEED_DIV);
	}
}
