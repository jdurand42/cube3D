/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:16:00 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 21:23:07 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	parse_res(t_data *data, char *line)
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
	if (data->R[0] > W_MAX)
		data->R[0] = 2560;
	if (data->R[1] > H_MAX)
		data->R[1] = 1440;
	printf("res: %d, %d, check: %d\n", data->R[0], data->R[1], data->check);
	return ;
}

char	*pathing(char *pathe, char *line, int *check)
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
	printf("path: %s, check: %d\n", path, *check);
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
			data->NO = pathing(data->NO, &line[i], &data->check);
		else if (!ft_strncmp(&line[i], "SO", 2))
			data->SO = pathing(data->SO, &line[i], &data->check);
		else if (!ft_strncmp(&line[i], "WE", 2))
			data->WE = pathing(data->WE, &line[i], &data->check);
		else if (!ft_strncmp(&line[i], "ES", 2))
			data->ES = pathing(data->ES, &line[i], &data->check);
		else if (!ft_strncmp(&line[i], "S", 1))
			data->S = pathing(data->S, &line[i], &data->check);
	}
}
