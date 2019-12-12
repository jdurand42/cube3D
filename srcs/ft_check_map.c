/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:16:23 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 17:36:35 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int		ft_check_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < data->height)
	{
		while (i < data->width)
		{
			if (j == 0 || i == 0 || i == data->width - 1 ||
				j == data->height - 1)
			{
				if (data->map[j][i] != 1)
					return (ft_iserror_map(data, j));
			}
			if (data->map[j][i] > 2)
				ft_parse_position(data, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	if (data->posx == 0 || data->posy == 0)
		return (ft_iserror_map(data, j));
	return (1);
}

void	ft_parse_position(t_data *data, int i, int j)
{
	data->posy = j;
	data->posx = i;
	data->cam.angle = ft_get_angle(data, data->map);
}

int		ft_parse_aline(t_data *data, int **map, char *line, int count)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	if (!(map[count] = (int*)malloc(data->width * sizeof(int))))
		return (-1);
	while (line[i] != 0)
	{
		if (!(check < data->width))
			return (-1);
		if (ft_isargvalid(line[i]))
		{
			if (line[i] - '0' == 2)
				data->s_max += 1;
			map[count][j++] = line[i] - '0';
			check++;
		}
		i++;
	}
	if (check != data->width)
		return (ft_iserror_map(data, count));
	return (1);
}

int		ft_parse_map(t_list **lst, size_t count, t_data *data)
{
	char	*line;
	t_list	*lst2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	line = (char*)(*lst)->content;
	while (line[i] != 0)
		if (ft_isargvalid(line[i++]))
			data->width += 1;
	i = 0;
	if (!(data->map = (int**)malloc(count * sizeof(int*))))
		return (0);
	count -= 1;
	lst2 = *lst;
	while (count >= 0 && lst2 != NULL)
	{
		if (ft_parse_aline(data, data->map, (char*)lst2->content, count) == -1)
			return (0);
		count--;
		lst2 = lst2->next;
	}
	return (1);
}
