/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:14:45 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/10 16:54:55 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_exit_all(t_data *data)
{
	free_paths(data);
	ft_free_map(data);
	ft_free_vec(data);
	ft_free_dda(data);
	ft_free_tsprite(data);
	if (data->mlx_img)
		mlx_destroy_image(data->mlx_p, data->mlx_img);
	ft_free_tex(data);
	mlx_destroy_window(data->mlx_p, data->mlx_wd);
	exit(0);
}

void 	ft_free_map(t_data *data)
{
	int j;

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

void 	ft_free_vec(t_data *data)
{
	if (!data->vec)
		return ;
	free (data->vec);
}

void 	ft_free_dda(t_data *data)
{
	if (!data->dda)
		return ;
	free(data->dda);
}

void ft_free_tex(t_data *data)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (data->tex[i].img_p)
			mlx_destroy_image(data->mlx_p, data->tex[i].img_p);
		i++;
	}
}

void 	ft_free_tsprite(t_data *data)
{
	if (!data->tsprite)
		return ;
	free(data->tsprite);
}
