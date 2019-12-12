/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:33:42 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 16:30:00 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int		ft_iserror(int code, t_data *data)
{
	if (code == 1)
		ft_putstr("Error\nFile opening aborted\n");
	else if (code == 2)
		ft_putstr("Error\nSome datas are invalid\n");
	else if (code == 3)
		ft_putstr("Error\nIn game loop\n");
	else if (code == 4)
		ft_putstr("Error\nMap invalid\n");
	ft_exit_all(data);
	return (1);
}

int		ft_iserror_map(t_data *data, int j)
{
	ft_putstr("Error\nMap invalid\n");
	ft_free_vec(data);
	ft_free_dda(data);
	ft_free_tsprite(data);
	ft_free_tex(data);
	free_paths(data);
	data->height = j;
	return (0);
}
