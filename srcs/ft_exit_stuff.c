/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:14:45 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 16:35:41 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_exit_all(t_data *data)
{
	ft_free_map(data);
	ft_free_vec(data);
	ft_free_dda(data);
	ft_free_tsprite(data);
	ft_free_tex(data);
	free_paths(data);
	if (data->mlx_p && data->mlx_wd)
	{
		mlx_clear_window(data->mlx_p, data->mlx_wd);
		mlx_destroy_window(data->mlx_p, data->mlx_wd);
	}
	if (data->mlx_img)
		mlx_destroy_image(data->mlx_p, data->mlx_img);
	exit(0);
}

int		exit_program(int keycode, void *param)
{
	t_data	*data;

	data = (t_data*)param;
	(void)keycode;
	exit(0);
	return (0);
}

void	ft_free_map(t_data *data)
{
	int	j;

	j = 0;
	if (!data->map)
		return ;
	while (j < data->height)
	{
		if (data->map[j])
			free(data->map[j]);
		j++;
	}
	free(data->map);
}
