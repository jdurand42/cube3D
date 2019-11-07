/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:28:36 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/07 18:13:41 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int		main(int ac, char **av)
{
	char	*file;
	int		fd;
	t_data	data;
	int		**map;

	file = NULL;
	if (ac < 2)
		return (ft_iserror(1));
	fd = open("./maps/test.cub", O_RDONLY);
	if (!(file = ft_file_str(fd)))
		return (ft_iserror(1));
	if (!(map = ft_parse_map(&data, file);
	ft_putstr(file);
	return (0);
}
