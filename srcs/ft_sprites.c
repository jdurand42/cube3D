/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:45:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/07 22:30:03 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"


void 		ft_check_if_hit(t_data *data) // marchera pas dans le dda
{
	int s = 0;
	int i = 0;
	float x, y;

	while (s < data->s_max)
	{
		while (i < data->R[0])
		{
		//		theta = data->vec[i].angle_rela;
		//		if (theta > 30)
		//		 	theta = theta - 30;
		//		else if (theta < 30)
		//			theta = 30 - theta;
		//		tan_theta = tan(ft_toradian(theta));
		//		delta = data->tsprite[s].dist * tan_theta;
		//		dist_r = sqrt(delta * delta + data->tsprite[s].dist * data->tsprite[s].dist);
			///	printf("%f\n", dist_r);
				x = data->posx + (data->tsprite[s].dist * data->vec[i].rotx);
				y = data->posy - (data->tsprite[s].dist * data->vec[i].roty);
			if ((int)y == (int)data->tsprite[s].y && (int)x == (int)data->tsprite[s].x)
			{
				//printf(GREEN "sp n : %d, RAYON: %i, x, y hit: %f, %f\n" RESET, s, i, x, y);
				if (data->tsprite[s].pixel_hit == -1)
				{
					data->tsprite[s].hit |= 1;
					data->tsprite[s].pixel_hit = i;
					if (data->tsprite[s].offset == 0)
						data->tsprite[s].offset = x - (int)x;
					else if (data->tsprite[s].offset == 1)
						data->tsprite[s].offset = y - (int)y;
					printf(GREEN "x, y : %f, %f, ref: %d\noffset: %f\n" RESET, x, y, data->tsprite[s].ref_pixel, data->tsprite[s].offset);
					break ;
				}

			}
			i++;
		}
		printf("--------------------\n");
		i = 0;
		s++;
	}
}

void 	ft_soft_ddax(t_data *data, int i, t_int *x_) // si toucher sprite en x et en y est pas possible
{
	int n;
	int xsign;

	n = 0;
	if (data->dda[i].xsign == 1)
		xsign = 0;
	else
		xsign = data->dda[i].xsign;
	if (!(data->map[(int)x_->y][(int)x_->x + xsign] == 2))
		return ;
	while (n < data->s_max)
	{
		if ((int)data->tsprite[n].y == (int)x_->y && (int)data->tsprite[n].x == (int)x_->x + xsign)
		{
			if (i < data->tsprite[n].ref_pixel)
			{
				data->tsprite[n].ref_pixel = i;
				data->tsprite[n].offset = 0;
			}
		}
		n++;
	}
}

void 	ft_soft_dday(t_data *data, int i, t_int *y_)
{
	int n;
	int ysign;

	n = 0;
	if (data->dda[i].ysign == 1)
		ysign = 0;
	else
		ysign = data->dda[i].ysign;
	if (!(data->map[(int)y_->y + ysign][(int)y_->x] == 2))
		return ;
	while (n < data->s_max)
	{
		if ((int)data->tsprite[n].y + ysign == (int)y_->y && (int)data->tsprite[n].x == (int)y_->x)
		{
			if (i < data->tsprite[n].ref_pixel)
			{
				data->tsprite[n].ref_pixel = i;
				data->tsprite[n].offset = 1;
			}
		}
		n++;
	}
}

void 	ft_do_dist_sprite(t_data *data)
{
	int		i;
	float	distx;
	float	disty;

	i = 0;
	while (i < data->s_max)
	{
		distx = data->posx - (data->tsprite[i].x + 0.5);
		disty = data->posy - (data->tsprite[i].y +  0.5);
		data->tsprite[i].distx = distx;
		data->tsprite[i].disty = disty;
		data->tsprite[i].dist = sqrt((distx * distx) + (disty * disty));
		data->tsprite[i].sizey = (int)(data->R[1] / data->tsprite[i].dist);
		data->tsprite[i].sizex = (int)(data->tsprite[i].sizey / 2);
		i++;
	}
	printf(GREEN "--Presort--\n" RESET);
	//ft_show_tsprite(data->tsprite, data->s_max);
	ft_do_sort_sprite(data);
	printf(GREEN "--Postsort--\n" RESET);
	ft_show_tsprite(data->tsprite, data->s_max);
}

void 	ft_show_tsprite(t_sprite *tsprite, int s_max)
{
	int i;

	i = 0;
	while (i < s_max)
	{
		printf("i : %d x, y: %f, %f, pix %d, hit: %d, dist: %f, offset: %f\nsizexy: %d, %d\n", i,
		tsprite[i].x, tsprite[i].y, tsprite[i].pixel_hit, tsprite[i].hit, tsprite[i].dist,
		tsprite[i].offset, tsprite[i].sizex, tsprite[i].sizey);
		i++;
	}
}

void		ft_do_tsprite(t_data *data)
{
	int x;
	int y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	if (!(data->tsprite = (t_sprite*)malloc(data->s_max * sizeof(t_sprite))))
		exit(0);
	while (y < data->height)
	{
		while (x < data->width)
		{
			if (data->map[y][x] == 2)
			{
				printf("%d, %d\n", x, y);
				data->tsprite[i].x = x;
				data->tsprite[i].y = y;
				i++;
			}
			x++;
		}
		x = 0;
		y++;
	}
	ft_reset_tsprite(data->tsprite, data->s_max, data);
}

void 	ft_reset_tsprite(t_sprite *tsprite, int s_max, t_data *data)
{
	int i = 0;

	while (i < s_max)
	{
		tsprite[i].pixel_hit = -1;
		tsprite[i].hit = 0;
		tsprite[i].offset = -1;
		tsprite[i].ref_pixel = data->R[0];
		tsprite[i].dist = -1;
		tsprite[i].dist = -1;
		tsprite[i].dist = -1;
		tsprite[i].sizex = 0;
		tsprite[i].sizey = 0;
		i++;
	}
}

void 	ft_draw_sprites(t_data *data)
{
	int i = 0; int j = 0; int n = 0; int hp; int w_sprite;

	while (n < data->s_max)
	{
		if (data->tsprite[n].hit == 1)
		{
			hp = data->R[1] / data->tsprite[n].dist;
			if (data->tsprite[n].offset < 0)
				data->tsprite[n].offset = 1;
			w_sprite = (hp / 2) * data->tsprite[n].offset;
			i = data->tsprite[n].pixel_hit;
				while (i < data->R[0] && i < data->tsprite[n].pixel_hit + w_sprite)
				{
					if (data->tsprite[n].dist < data->vec[i].dist_towall) // draw a collum
							ft_draw_a_colum_sprite(data, i, hp);
					i++;
				}
		//		printf("i: %d\nlsat - hit: %d, width: %d\n", i, data->tsprite[n].pixel_last - data->tsprite[n].pixel_hit, w_sprite);
			}
		n++;
	}
}

void 	ft_draw_a_colum_sprite(t_data *data, int i, int hp)
{
	unsigned long		j = 0;

	if (hp <= data->R[1])
		j = (data->R[1] / 2) - (hp / 2);
	else
	{
		j = 0;
	}
		while (j <= (data->R[1] / 2) + (hp / 2) && j <  data->R[1])
		{
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 0] = (char)0;
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 1] = (char)0;
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 2] = (char)255;
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 3] = (char)0;
			j++;
		}
}

void 	ft_draw_a_colum_sprite_rev(t_data *data, int i, int hp)
{
	unsigned long		j = 0;

	if (hp <= data->R[1])
		j = (data->R[1] / 2) - (hp / 2);
	else
	{
		j = 0;
	}
		while (j <= (data->R[1] / 2) + (hp / 2) && j <  data->R[1])
		{
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 0] = (char)0;
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 1] = (char)0;
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 2] = (char)255;
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 3] = (char)0;
			j++;
		}
}
