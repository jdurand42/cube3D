/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:28:36 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 22:00:39 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int		main(int ac, char **av)
{
	int			fd;
	t_data		data;
	int			**map;

	data.check = 0;
	data.s_max = 0;
	data.fsave = 0;
	if (ac < 2)
		fd = open("./maps/long_map.cub", O_RDONLY);
	else
		fd = open(av[1], O_RDONLY);
	if (ac == 3)
		if (!ft_strncmp(av[2], "-fsave", 6))
			data.fsave = 1;
	if (!(map = ft_parse_stuff(&data, fd)))
		ft_exit_all(&data); // ????
	printf("%d, %d\n", data.width, data.height);
	for (int i = 0; i < data.height; i++)
	{
		for (int j = 0; j < data.width; j++)
			printf("%d ", map[i][j]);
		printf("\n");
 	}
	data.exit_status = 0;
	if (!(ft_game_loop(&data, map)))
		ft_iserror(3);
	return (0);
}
