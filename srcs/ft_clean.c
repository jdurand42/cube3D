/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:36:47 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/28 17:52:13 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	free_paths(t_data *data)
{
	printf("%s\n", data->ES);
	if (data->NO)
		free(data->NO);
	if (data->SO)
		free(data->SO);
	if (data->WE)
		free(data->WE);
	if (data->S)
		free(data->S);
	if (data->ES)
		free(data->ES);
}
