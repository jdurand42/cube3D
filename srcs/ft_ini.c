/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:36:37 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/09 17:47:00 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"


void 	parse_res(t_data *data, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != 0 && !(ft_isdigit(line[i])))
		i++;
	if (line[i] != 0)
		data->R[0] = ft_atoi(&line[i]);
	while (line[i] != 0 && ft_isdigit(line[i]))
		i++;
	if (line[i] != 0)
		data->R[1] = ft_atoi(&line[i]);
	if (!line[i] || !data->R[0] || !data->R[1])
		data->check = -1;
	else
		data->check += 2;
	printf("res: %d, %d, check: %d\n", data->R[0], data->R[1], data->check);
	return ;
}

char	*pathing(char *path, char *line, int *check)
{
	size_t	i;

	i = 0;
	while (line[i] != 0 && line[i] != '.')
		i++;
	if (!(path = ft_strdup(&line[i])))
	{
		*check = -1;
		return (NULL);
	}
	else
		*check += 1;
	printf("path: %s, check: %d\n", path, *check);
	return (path);
}

void 	parse_path(t_data *data, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != 0 && line[i] == ' ')
		i++;
	if (line[i] != 0)
	{
		if (!ft_strncmp(&line[i], "NO", 2))
			pathing(data->NO, &line[i], &data->check);
		else if (!ft_strncmp(&line[i], "SO", 2))
			pathing(data->SO, &line[i], &data->check);
		else if (!ft_strncmp(&line[i], "WE", 2))
			pathing(data->WE, &line[i], &data->check);
		else if (!ft_strncmp(&line[i], "ES", 2))
			pathing(data->ES, &line[i], &data->check);
		else if (!ft_strncmp(&line[i], "S", 1))
			pathing(data->S, &line[i], &data->check);
	}
}

void 	coloring(unsigned char *rgb, char *line, int *check)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	while (line[i] != 0 && !ft_isdigit(line[i]))
		i++;
	while (line[i] != 0 && j < 3)
	{
		rgb[j++] = (unsigned char)ft_atoi(&line[++i]);
		while (line[i] != 0 && line[i] != ',')
			i++;
	}
	if (j == 3)
		*check += 1;
	else
		*check = -1;
	for (size_t k = 0; k < 3; k++)
		printf("%d\n", rgb[k]);
}

void 	parse_color(t_data *data, char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] != 0 && line[i] == ' ')
		i++;
	if (!ft_strncmp(&line[i], "F", 1))
		coloring(data->F, &line[i], &data->check);
	else if (!ft_strncmp(&line[i], "C", 1))
		coloring(data->C, &line[i], &data->check);
}

int		ft_search_arg(char *line, char *set)
{
	while (*line != 0)
	{
		if (*line == ' ') // whitespace?
			line++;
		else
			while (*set  != 0)
			{
				if (*line == *set)
					return (1);
				set++;
			}
		line++;
	}
	return (0);
}

int 	ft_isargvalid(char c)
{
	if (c == '1' || c == '0' || c == '2' || c == 'N' || c == 'E' || c == 'W' ||
	c == 'S')
		return (1);
	else
		return (0);
}

int		**ft_parse_map(t_list *lst, size_t count, int *check, t_data *data)
{
	int		**map;
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	data->width = 0;
	j = 0;
	line = (char*)lst->content;
	while (line[i] != 0)
		if (ft_isargvalid(line[i++]))
			data->width += 1;
	i = 0;
	if (!(map = (int**)malloc(count * sizeof(int*))))
		return (NULL);
	count -= 1;
	while (count >= 0 && lst != NULL)
	{
		line = (char*)lst->content; // a free
		if (!(map[count] = (int*)malloc(data->width * sizeof(int))))
			return (NULL);
		while (line[i] != 0 && j < (size_t)data->width)
		{
			if (ft_isargvalid(line[i]))
				map[count][j++] = line[i++] - '0';
			else if (line[i++] != ' ' && line[i] != 0)
				return (NULL);
		}
		count--;
		i = 0;
		j = 0;
		lst = lst->next;
	}
	return (map);
}

int		**ft_parse_stuff(t_data *data, int fd)
{
	size_t	i;
	char	*line;
	char	map_str;
	size_t	count;
	t_list	*lst;

	i = 0;
	data->check = 0;
	count = 0;
	lst = NULL;
	while (get_next_line(fd, &line) > 0)
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
				ft_lstadd_front(&lst, ft_lstnew(line));
//				printf("%s\n", (char*)lst->content);
				count++;
			}
		}
	}
	data->height = count;
//	if (data->check != 7)
//		return (NULL);
	free(line);
	line = NULL;
	return (ft_parse_map(lst, count, &data->check, data));
}
