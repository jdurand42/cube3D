/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:36:37 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 16:37:53 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	parse_color(t_data *data, char *line)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] != 0 && line[i] == ' ')
		i++;
	if (!ft_strncmp(&line[i], "F", 1))
		data->f = coloring(&line[i], &data->check);
	else if (!ft_strncmp(&line[i], "C", 1))
		data->c = coloring(&line[i], &data->check);
}

int		ft_parse_stuff(t_data *data, int fd)
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
	printf("check in stuff: %d\n", data->check);
	if (data->check != 9 || lst == NULL)
		return (0);
	if (!ft_parse_map(&lst, count, data))
		return (0);
	if (!ft_check_map(data))
		return (0);
	ft_lst_free(&lst);
	return (1);
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
