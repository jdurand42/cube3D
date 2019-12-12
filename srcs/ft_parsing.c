/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:36:37 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 13:22:39 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

unsigned int	coloring(char *line, int *check)
{
	size_t			j;
	size_t			i;
	unsigned char	rgb[3];

	i = 0;
	j = 0;
	while (line[i] != 0 && j < 3)
	{
		while (line[i] != 0 && !ft_isdigit(line[i]))
			i++;
		if (ft_isdigit(line[i]))
			rgb[j++] = (unsigned char)ft_atoi(&line[i]);
		while (line[i] != 0 && ft_isdigit(line[i]))
			i++;
	}
	if (j == 3)
		*check += 1;
	else
	{
		*check = -1;
		return (0);
	}
	printf("color F-C: %u\n", rgb[2]);
	return (ft_rgb(rgb[0], rgb[1], rgb[2]));
}

void			parse_color(t_data *data, char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] != 0 && line[i] == ' ')
		i++;
	if (!ft_strncmp(&line[i], "F", 1))
		data->F = coloring(&line[i], &data->check);
	else if (!ft_strncmp(&line[i], "C", 1))
		data->C = coloring(&line[i], &data->check);
}

int				ft_parse_aline(t_data *data, int **map, char *line, int count)
{
	int i;
	int j;
	int check;

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
		return (-1);
	return (1);
}

int				ft_parse_map(t_list **lst, size_t count, t_data *data)
{
	char	*line;
	t_list  *lst2;
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

int				ft_parse_stuff(t_data *data, int fd)
{
	size_t	i;
	char	*line;
	size_t	count;
	t_list	*lst;

	i = 0;
	count = 0;
	lst = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		ft_parse_stuff2(data, line, &lst, &count);
		free(line);
	}
	free(line);
	line = NULL;
	data->height = count;
	if (data->check != 9)
		return (0);
	if (!ft_parse_map(&lst, count, data))
		return (0);
	if (!ft_check_map(data, data->map))
		return (0);
	ft_lst_free(&lst);
	return (1);
}

int		ft_check_map(t_data *data, int **map)
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
					return (ft_iserror(4));
			}
			if (data->map[j][i] > 2)
				ft_parse_position(data, i, j);
			i++;
		}
		i = 0;
		j++;
	}
	if (data->posx == 0 || data->posy == 0)
		return (ft_iserror(4));
	return (1);
}

void 	ft_parse_position(t_data *data, int i, int j)
{
	data->posy = j;
	data->posx = i;
	data->cam.angle = ft_get_angle(data, data->map);
}

void	ft_parse_stuff2(t_data *data, char *line, t_list **lst, size_t *count)
{
	if (*line != 0)
	{
		if (ft_search_arg(line, "R"))
			parse_res(data, line);
		else if (ft_search_arg(line, "NSWE"))
			parse_path(data, line);
		else if (ft_search_arg(line, "FC"))
			parse_color(data, line);
		else if (ft_search_arg(line, "1"))
		{
			ft_lstadd_front(lst, ft_lstnew(ft_strdup(line)));
			*count += 1;
		}
	}
}
