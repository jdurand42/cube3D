/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:36:37 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/19 14:29:38 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"


void 	coloring(unsigned int *rgb, char *line, int *check)
{
	size_t	j;
	size_t	i;
	unsigned char rgbt[3];

	i = 0;
	j = 0;
	while (line[i] != 0 && !ft_isdigit(line[i]))
		i++;
	while (line[i] != 0 && j < 3)
	{
		rgbt[j++] = (unsigned char)ft_atoi(&line[++i]);
		while (line[i] != 0 && line[i] != ',')
			i++;
	}
	if (j == 3)
		*check += 1;
	else
		*check = -1;
	*rgb = ft_rgb(rgbt[0], rgbt[1], rgbt[2]);
	printf("color F-C: %u\n", *rgb);
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
		coloring(&data->F, &line[i], &data->check);
	else if (!ft_strncmp(&line[i], "C", 1))
		coloring(&data->C, &line[i], &data->check);
}

int 	ft_parse_aline(t_data *data, int **map, char *line, int count)
{
	int i = 0; int j = 0; int check = 0;

	if (!(map[count] = (int*)malloc(data->width * sizeof(int))))
		return (-1);
	while (line[i] != 0)
	{
		if (!(check < data->width))
			return (-1);
		if (ft_isargvalid(line[i]))
		{
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E')
			{
				data->posx = j;
				data->posy = count;
			}
			map[count][j++] = line[i] - '0';
			check++;
		}
		i++;
	}
	free(line);
	return (1);
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
		if (ft_parse_aline(data, map, (char*)lst->content, count) == -1)
			return (NULL);
		count--;
		lst = lst->next;
	//free line and lst
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
			//free(line);
		}
	}
	data->height = count;
	if (data->check != 8)
		return (NULL);
	free(line);
	line = NULL;
	return (ft_parse_map(lst, count, &data->check, data));
}
