/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:15:57 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 15:10:01 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_do_sort_sprite(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->s_max - 1)
	{
		if (data->tsprite[i].dist < data->tsprite[i + 1].dist)
		{
			ft_swap_sprite(&data->tsprite[i], &data->tsprite[i + 1]);
			i = 0;
		}
		else
			i++;
	}
}

void	ft_swap_sprite(t_sprite *a, t_sprite *b)
{
	float	f_b;
	float	lf_b;
	int		i_b;

	i_b = a->x;
	a->x = b->x;
	b->x = i_b;
	i_b = a->y;
	a->y = b->y;
	b->y = i_b;
	f_b = a->dist;
	a->dist = b->dist;
	b->dist = f_b;
	lf_b = a->rotx;
	a->rotx = b->rotx;
	b->rotx = lf_b;
	lf_b = a->roty;
	a->roty = b->roty;
	b->roty = lf_b;
	lf_b = a->angle;
	a->angle = b->angle;
	b->angle = lf_b;
	ft_swap_sprite2(a, b);
}

void	ft_swap_sprite2(t_sprite *a, t_sprite *b)
{
	int	i_b;

	i_b = a->sizex;
	a->sizex = b->sizex;
	b->sizex = i_b;
	i_b = a->sizey;
	a->sizey = b->sizey;
	b->sizey = i_b;
}

void	ft_lst_free(t_list **lst)
{
	t_list	*b;
	t_list	*b_n;

	b = *lst;
	if (b == NULL)
		return ;
	while (b != NULL)
	{
		b_n = b->next;
		free(b->content);
		b->content = NULL;
		free(b);
		b = NULL;
		b = b_n;
	}
}
