/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:28:36 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/13 21:53:15 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int		main(int ac, char **av)
{
	char		*file;
	int			fd;
	t_data		data;
	int			**map;

	file = NULL;
//	if (ac < 2)
//		return (ft_iserror(1));
	fd = open("./maps/test.cub", O_RDONLY);
	printf("%d\n", fd);
	if (!(map = ft_parse_stuff(&data, fd)))
		return (ft_iserror(2));
	printf("%d, %d\n", data.width, data.height);
	for (int i = 0; i < data.height; i++)
	{
		for (int j = 0; j < data.width; j++)
			printf("%d ", map[i][j]);
		printf("\n");
 	}
	ft_do_graphism(map, &data);
	//ft_putstr();
	return (0);
}
