/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:36:47 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 15:48:40 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	free_paths(t_data *data)
{
	if (data->no)
		free(data->no);
	data->no = NULL;
	if (data->so)
		free(data->so);
	data->so = NULL;
	if (data->we)
		free(data->we);
	data->we = NULL;
	if (data->s)
		free(data->s);
	data->s = NULL;
	if (data->es)
		free(data->es);
	data->es = NULL;
}

void	ft_free_vec(t_data *data)
{
	if (!data->vec)
		return ;
	free(data->vec);
}

void	ft_free_dda(t_data *data)
{
	if (!data->dda)
		return ;
	free(data->dda);
}

void	ft_free_tex(t_data *data)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if (data->tex[i].img_p)
			mlx_destroy_image(data->mlx_p, data->tex[i].img_p);
		i++;
	}
}

void	ft_free_tsprite(t_data *data)
{
	if (!data->tsprite)
		return ;
	free(data->tsprite);
}
