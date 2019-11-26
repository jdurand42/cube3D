/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:08:39 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/26 16:21:55 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_setup_rays(t_data *data, int **map)
{
	int 	i;
	float pas = 60 / (double)data->R[0];
	float len = 0.001;

	i = 0;
	if (!(data->vec = (t_vector*)malloc(data->R[0] * sizeof(t_vector))))
		return ;
	if (!(data->dda = (t_dda*)malloc(data->R[0] * sizeof(t_dda))))
		return ;
	data->cam.angle = ft_get_angle(data, map);
	while (i < data->R[0])
	{
		data->vec[i].angle_rela = (float)i * pas;
	//	printf("1: %lf ", data->vec[i].angle_rela);
		i++;
	}
}
void 	do_rays(t_data *data)
{
	int i = 0;
	double len = 0.01;

	while (i < data->R[0])
	{
//		len = 0.1;

		ft_setray(data, i);
		while (data->vec[i].wall_type == -1)
		{
			//printf("%lf, %lf\n", data->vec[i].rotx, data->vec[i].roty);
	//		ft_dda(data, data->R[0] / 2);
//			printf("x: %f\n", data->vec[i].x1);
//			printf("y : %f\n", data->vec[i].y1);
			ft_dda(data, i);

	//		if (data->map[(int)])
			//data->vec[i].y1 = data->posy - (len * data->vec[i].roty)
//			len += 0.01;
		}
		i++;
	}
	printf(GREEN "---------------\n" RESET);
	ft_do_colum(data); // a regler
	mlx_put_image_to_window(data->mlx_p, data->mlx_wd, data->mlx_img, 0, 0);
}

void 	ft_setray(t_data *data, int i)
{
	float pas;

	pas = 60 / (float)data->R[0];
	data->vec[i].x1 = data->posx;
	data->vec[i].y1 = data->posy;
	data->vec[i].angle = data->cam.angle - (60 / 2) + ((float)i * pas);
	if (data->vec[i].angle > 360)
		data->vec[i].angle = 0;
	else if (data->vec[i].angle < 0)
		data->vec[i].angle = 360;
	data->vec[i].rotx = cos(ft_toradian(data->vec[i].angle));
	data->vec[i].roty = sin(ft_toradian(data->vec[i].angle));
	data->vec[i].wall_type = -1;

//	if (i == data->R[0] / 2) //|| i == 0 || i == data->R[0] - 1)
	//	printf(GREEN "ray %d: x1: %lf, y1: %lf\nangle : %lf\n, rotx : %lf, roty: %lf\n"
//		RESET, i, data->vec[i].x1, data->vec[i].y1, data->vec[i].angle,
//		data->vec[i].rotx, data->vec[i].roty);
}

void 	ft_do_colum(t_data *data)
{
	unsigned long int		j = 0;
	int		hp;
	int		i = 0;
	float 	distance;
	unsigned int 			color;

	while (i < data->R[0])
	{
		if (i < data->R[0])
			distance = data->vec[i].dist_towall * cos(ft_toradian(30 - data->vec[i].angle_rela));
		else if (i > data->R[0])
			distance = data->vec[i].dist_towall * cos(ft_toradian(data->vec[i].angle_rela - 30));
//		if (distance < 1)
//			distance = 1;
		hp = data->R[1] / distance;
	//		printf("%d, %lf\n", i, data->vec[i].angle_rela);
		color = ft_choose_color(data, i);
		j = (data->R[1] / 2 * data->size_line) - (hp / 2 * data->size_line);
			while (j >= (data->R[1] / 2 * data->size_line) - (hp / 2 * data->size_line) && j <= (data->R[1] / 2 * data->size_line) + (hp / 2 * data->size_line))
			{
				data->img[j + (data->R[0] - i) * 4 + 0] = (char)(color >> 0);
				data->img[j + (data->R[0] - i) * 4 + 1] = (char)(color >> 8);
				data->img[j + (data->R[0] - i) * 4 + 2] = (char)(color >> 16);
				data->img[j + (data->R[0] - i) * 4 + 3] = (char)0;
				j += data->size_line;
			}
		i++;
	}
}

/*
** wall_type 0 > x > E ou W
** wall_type 1 > y > N ou S
** roty	> 0    >   > S ou E Ou W
** roty < 0    >   > N ou E ou W
** rotx > 0    >   > W ou N ou S
** rotx < 0    >   > E ou N ou S
** if wall_type 1
**	-> roty > 0 -> S
**  -> roty < 0 -> N
** if wall_type 0
**	-> rotx > 0 -> W
**  -> rotx < 0 -> E
**
*/

unsigned int 	ft_choose_color(t_data *data, int i)
{
	if (data->vec[i].wall_type == 1)
	{
		if (data->vec[i].roty > 0)
			return (ft_rgb(255, 0, 0));
		else
			return (ft_rgb(0, 255, 0));
	}
	else
	{
		if (data->vec[i].rotx < 0)
			return (ft_rgb(0, 0, 112));
		else
			return (ft_rgb(0, 0, 255));
	}
}
