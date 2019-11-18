/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:26:07 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/18 15:41:47 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int 	ft_keyboard_loop(int keycode, void *params)
{
	t_data *data;

	data = (t_data*)params;
	printf("keycode %d\n", keycode);
	return (0);
}

int 	ft_game_loop(t_data *data, int **map)
{

	if (!ft_setup_mlx(data, map))
		return (0);
	ft_setup_rays(data, map);

	mlx_key_hook(data->mlx_wd, ft_keyboard_loop, data);
	mlx_loop(data->mlx_p);
	return (1);
}

int 	ft_setup_mlx(t_data *data, int **map)
{
	data->map = map;
	if ((data->mlx_p = mlx_init()))
		printf("succes mlx\n");
	data->mlx_wd = mlx_new_window(data->mlx_p, data->R[0], data->R[1], "Wolf3D");
	if (data->mlx_wd)
		printf("%p\n", data->mlx_wd);
	data->mlx_img = mlx_new_image(data->mlx_p, data->R[0], data->R[1]);
	if (!data->mlx_img)
		return (0);
	data->img = mlx_get_data_addr(data->mlx_img, &(data->bit_p_p), &(data->size_line), &(data->endian));
	printf("bpp: %d, sizeline: %d, endian: %d\n", data->bit_p_p, data->size_line, data->endian);
	return (1);
}
