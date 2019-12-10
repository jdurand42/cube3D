/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:36:47 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/10 18:00:33 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	free_paths(t_data *data)
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
