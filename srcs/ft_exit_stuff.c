/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:14:45 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/10 16:29:46 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_exit_all(t_data *data)
{
	free_paths(data);
	ft_free_map(data);
	ft_free_vec(data);
	ft_free_dda(data);
	ft_free_tsprite(data);
	exit(0);
}

void 	ft_free_map(t_data *data)
{
	int j;

	j = 0;
	if (!data->map)
		return ;
	while (j < data->height)
	{
		if (data->map[j])
			free(data->map[j]);
		j++;
	}
	free(data->map);
}

void 	ft_free_vec(t_data *data)
{
	if (!data->vec)
		return ;
	free (data->vec);
}

void 	ft_free_dda(t_data *data)
{
	if (!data->dda)
		return ;
	free(data->dda);
}

void 	ft_free_tsprite(t_data *data)
{
	if (!data->tsprite)
		return ;
	free(data->tsprite);
}
