/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:28:36 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 12:51:38 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_init_data(t_data *data)
{
	data->check = 0;
	data->s_max = 0;
	data->fsave = 0;
	data->map = NULL;
	data->vec = NULL;
	data->dda = NULL;
	data->NO = NULL;
	data->SO = NULL;
	data->WE = NULL;
	data->ES = NULL;
	data->S = NULL;
	data->width = 0;
	data->height = 0;
	data->posx = 0;
	data->posy = 0;
	data->mlx_p = NULL;
	data->mlx_wd = NULL;
	data->mlx_img = NULL;
	data->img = NULL;
}

int		main(int ac, char **av)
{
	int			fd;
	t_data		data;
	int			**map;


	if (ac < 2)
		fd = open("./maps/long_map.cub", O_RDONLY);
	else
		fd = open(av[1], O_RDONLY);
	if (ac == 3)
		if (!ft_strncmp(av[2], "-fsave", 6))
			data.fsave = 1;
	ft_init_data(&data);
	if (!(ft_parse_stuff(&data, fd)))
		ft_exit_all(&data); // ????
	printf("%d, %d\n", data.width, data.height);
	for (int i = 0; i < data.height; i++)
	{
		for (int j = 0; j < data.width; j++)
			printf("%d ", data.map[i][j]);
		printf("\n");
 	}
	data.exit_status = 0;
	if (!(ft_game_loop(&data, data.map)))
		ft_iserror(3);
	return (0);
}
