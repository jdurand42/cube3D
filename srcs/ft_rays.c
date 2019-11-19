/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:08:39 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/19 19:18:38 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_setup_rays(t_data *data, int **map)
{
	int 	i;
	double pas = 60 / (double)data->R[0];
	double len = 0.01;

	i = 0;
	if (!(data->vectors = (t_vector*)malloc(data->R[0] * sizeof(t_vector))))
		return ;
	data->angle = ft_get_angle(data, map);
	printf("ANGLE: %lf\n", data->angle);
	while (i < data->R[0])
	{
		data->vectors[i].x1 = data->posx + (len * (cos(ft_toradian(data->angle - (60 / 2) + (double)i * pas))));
		data->vectors[i].y1 = data->posy - (len * (sin(ft_toradian(data->angle - (60 / 2) + (double)i * pas))));
		i++;
	}
}

void 	do_rays(t_data *data)
{
	int i = 0;
	double len = 0.1;
	double pas = 60 / (double)data->R[0];
	double distance = -1;


	while (i < data->R[0])
	{
		len = 0.1;
		data->vectors[i] = (t_vector) { data->posx, data->posy };
		while (data->map[(int)data->vectors[i].y1][(int)data->vectors[i].x1] != 1)
		{
			data->vectors[i].angle = data->angle - (60 / 2) + ((double)i * pas);
			data->vectors[i].x1 = data->posx + (len * (cos(ft_toradian(data->vectors[i].angle))));
			data->vectors[i].y1 = data->posy - (len * (sin(ft_toradian(data->vectors[i].angle))));
			len += 0.01;
		}
		if (i == data->R[0] / 2 || i == 0 || i == data->R[0] - 1)
			printf("ray %d: x1: %lf, y1: %lf\nnangle : %lf\n", i, data->vectors[i].x1, data->vectors[i].y1, data->vectors[i].angle);
		i++;
	}

	ft_do_colum(data); // a regler
	mlx_put_image_to_window(data->mlx_p, data->mlx_wd, data->mlx_img, 0, 0);
}

void 	ft_do_colum(t_data *data)
{
	unsigned long int		j = 0;
	int		hp;
//	int 	diff;
	int		i = 0;
	double 	distance;

	while (i < data->R[0])
	{
		//fisheye
		distance = get_dist(data, i);
		if (distance < 1)
			distance = 1;
		hp = data->R[1] / distance;
		j = (data->R[1] / 2 * data->size_line) - (hp / 2 * data->size_line);
			while (j >= (data->R[1] / 2 * data->size_line) - (hp / 2 * data->size_line) && j <= (data->R[1] / 2 * data->size_line) + (hp / 2 * data->size_line))
			{
				data->img[j + (data->R[0] - i) * 4 + 0] = (char)85;
				data->img[j + (data->R[0] - i) * 4 + 1] = (char)85;
				data->img[j + (data->R[0] - i) * 4 + 2] = (char)85;
				data->img[j + (data->R[0] - i) * 4 + 3] = (char)0;
				j += data->size_line;
			}
		i++;
	}
}

double 	get_dist(t_data *data, int i)
{
	double distance;

	distance = sqrt(pow(data->vectors[i].x1 - data->posx, 2) + pow(data->vectors[i].y1 - data->posy, 2));
//	printf("ray: %d, distance: %lf\n", i, distance);
	return (distance);
}
/*
void 	raycast(t_data *data)
{
	int i = 0;
	double len = 0.1;

	while (i < data->r[0])
	{
		data->vectors[i].x0 = data->posx;
		data->vectors[i].y0 = data->posy;
		data->vectors[i].x1 = data->posx + (len * (cos(ft_toradian(data->angle - (60 / 2) + (double)i * pas))));
		data->vectors[i].y1 = data->posy + (len * (sin(ft_toradian(data->angle - (60 / 2) + (double)i * pas))));
	}
}*/
// while (ray != 1)
// touch 120

int 	ft_get_angle(t_data *data, int **map)
{
	double angle;

	if (map[(int)data->posy][(int)data->posx] + '0' == 'N')
		angle = 90;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'E')
		angle = 0;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'S')
	 	angle = 270;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'W')
		angle = 180;
	map[(int)data->posy][(int)data->posx] = 0;
	return (angle);
}
