/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:28:36 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 16:40:04 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void 	ft_init_data(t_data *data)
{
	int i;

	i = -1;
	data->check = 0;
	data->s_max = 0;
	data->save = 0;
	data->map = NULL;
	data->vec = NULL;
	data->dda = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->es = NULL;
	data->s = NULL;
	data->width = 0;
	data->height = 0;
	data->posx = 0;
	data->posy = 0;
	data->mlx_p = NULL;
	data->mlx_wd = NULL;
	data->mlx_img = NULL;
	data->img = NULL;
	while (i++ < 5)
		data->tex[i].img_p = NULL;
}

int		ft_fd_nul(void)
{
	ft_putstr("Error\nFile incorrect\n");
	return (0);
}

int		main(int ac, char **av)
{
	int			fd;
	t_data		data;

	if (ac < 2)
		fd = open("./maps/long_map.cub", O_RDONLY);
	else
		fd = open(av[1], O_RDONLY);
	printf("fd: %d\n", fd);
	if (fd < 0)
		return (ft_fd_nul());
	ft_init_data(&data);
	if (ac == 3)
		if (!ft_strncmp(av[2], "-save", 6))
			data.save = 1;
	if (!(ft_parse_stuff(&data, fd)))
		ft_iserror(2, &data); // ????
	data.exit_status = 0;
	if (!(ft_game_loop(&data, data.map)))
		ft_iserror(2, &data);
	return (0);
}
