/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:36:47 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 21:05:21 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	free_paths(t_data *data)
{
	if (data->NO)
		free(data->NO);
	data->NO = NULL;
	if (data->SO)
		free(data->SO);
	data->SO = NULL;
	if (data->WE)
		free(data->WE);
	data->WE = NULL;
	if (data->S)
		free(data->S);
	data->S = NULL;
	if (data->ES)
		free(data->ES);
	data->ES = NULL;
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
