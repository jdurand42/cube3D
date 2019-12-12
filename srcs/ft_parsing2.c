/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:16:00 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 17:35:20 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	parse_res(t_data *data, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != 0 && !(ft_isdigit(line[i])))
		i++;
	if (line[i] != 0)
		data->r[0] = ft_atoi(&line[i]);
	while (line[i] != 0 && ft_isdigit(line[i]))
		i++;
	if (line[i] != 0)
		data->r[1] = ft_atoi(&line[i]);
	if (!line[i] || data->r[0] < 0 || data->r[1] < 0)
		data->check = -1;
	else
		data->check += 2;
	if (data->r[0] > W_MAX)
		data->r[0] = 2560;
	if (data->r[1] > H_MAX)
		data->r[1] = 1440;
	if (data->r[0] < 10)
		data->r[0] = 600;
	if (data->r[1] < 10)
		data->r[1] = 450;
	return ;
}

char	*pathing(char *line, int *check)
{
	size_t	i;
	char	*path;

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
	return (path);
}

void	parse_path(t_data *data, char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != 0 && line[i] == ' ')
		i++;
	if (line[i] != 0)
	{
		if (!ft_strncmp(&line[i], "NO", 2))
			data->no = pathing(&line[i], &data->check);
		else if (!ft_strncmp(&line[i], "SO", 2))
			data->so = pathing(&line[i], &data->check);
		else if (!ft_strncmp(&line[i], "WE", 2))
			data->we = pathing(&line[i], &data->check);
		else if (!ft_strncmp(&line[i], "ES", 2))
			data->es = pathing(&line[i], &data->check);
		else if (!ft_strncmp(&line[i], "S", 1))
			data->s = pathing(&line[i], &data->check);
	}
}
