/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:45:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/09 23:26:54 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

/*
void 		ft_check_if_hit(t_data *data) // marchera pas dans le dda
{
	int s = 0;
	int i = 0;
	float x, y;

	while (s < data->s_max)
	{
		while (i < data->R[0])
		{
			x = data->posx + (data->tsprite[s].dist * data->vec[i].rotx);
			y = data->posy - (data->tsprite[s].dist * data->vec[i].roty);
			if ((int)y == (int)data->tsprite[s].y && (int)x == (int)data->tsprite[s].x)
			{
				//printf(GREEN "sp n : %d, RAYON: %i, x, y hit: %f, %f\n" RESET, s, i, x, y);
				if (data->tsprite[s].pixel_hit == -1)
				{
					data->tsprite[s].hit |= 1;
					data->tsprite[s].pixel_hit = i;
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
} */
/*
void 	ft_soft_ddax(t_data *data, int i, t_int *x_) // si toucher sprite en x et en y est pas possible
{
	int n;
 	float xsign;

	n = 0;
	if (data->dda[i].xsign == 1)
		xsign = 0.5;
	else
		xsign = -0.5;
	if (!(data->map[(int)x_->y][(int)(x_->x + xsign)] == 2))
		return ;
	while (n < data->s_max)
	{
		if ((int)data->tsprite[n].y == (int)x_->y && (int)data->tsprite[n].x == (int)(x_->x + xsign))
		{
			if (i < data->tsprite[n].ref_pixel)
			{
				data->tsprite[n].ref_pixel = i;
				data->tsprite[n].offset = 0;
			}
		}
		n++;
	}
}*/
/*
void 	ft_soft_dday(t_data *data, int i, t_int *y_)
{
	int n;
	float ysign;

	n = 0;
	if (data->dda[i].ysign == 1)
		ysign = 0.5;
	else
		ysign = -0.5;
	if (!(data->map[(int)(y_->y + ysign)][(int)y_->x] == 2))
		return ;
	while (n < data->s_max)
	{
		if ((int)(data->tsprite[n].y + ysign) == (int)y_->y && (int)data->tsprite[n].x == (int)y_->x)
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
*/
void 	ft_do_dist_sprite(t_data *data)
{
	int		i;
	float	distx;
	float	disty;

	i = 0;
	while (i < data->s_max)
	{
		distx = (data->tsprite[i].x + 0.5) - data->posx;
		disty = (data->tsprite[i].y + 0.5) - data->posy;
		data->tsprite[i].distx = distx;
		data->tsprite[i].disty = disty;
		data->tsprite[i].dist = sqrt((distx * distx) + (disty * disty));
		data->tsprite[i].rotx = distx / data->tsprite[i].dist;
		data->tsprite[i].roty = disty / data->tsprite[i].dist;
		if (distx > 0)
		{
			data->tsprite[i].angle = ft_todegree(acos(ft_abs(data->tsprite[i].rotx)));
			if (disty > 0)
				data->tsprite[i].angle = 360 - data->tsprite[i].angle;
		}
		else
		{
			data->tsprite[i].angle = ft_todegree(acos(ft_abs(data->tsprite[i].rotx)));
			if (disty < 0)
				data->tsprite[i].angle = 90 + (90 - data->tsprite[i].angle);
			else
				data->tsprite[i].angle = 180 + data->tsprite[i].angle;
		}
		i++;
	}
	printf(GREEN "--Presort--\n" RESET);
	//ft_show_tsprite(data->tsprite, data->s_max);
	ft_do_sort_sprite(data);
	printf(GREEN "--Postsort--\n" RESET);
//	ft_show_tsprite(data->tsprite, data->s_max);
}

void 	ft_check_if_visible(t_data *data)
{
	int i;
	int n;
	int	sizex;
	int sizey;
	float pas;

	i = 0;
	pas = 60 / (float)data->R[0];
	printf("%f\n", pas);
	while (i < data->s_max)
	{
		data->tsprite[i].sizey = data->R[1] / data->tsprite[i].dist;
		data->tsprite[i].sizex = data->tsprite[i].sizey / 2;
		data->tsprite[i].angle_f = data->tsprite[i].angle - (pas * (data->tsprite[i].sizex / 2));
		data->tsprite[i].angle_l = data->tsprite[i].angle + (pas * (data->tsprite[i].sizex / 2));
		if ((data->tsprite[i].angle_f >= data->cam.angle - 30 && data->tsprite[i].angle_f <= data->cam.angle + 30) ||
			(data->tsprite[i].angle_l <= data->cam.angle + 30 && data->tsprite[i].angle_l >= data->cam.angle - 30))
		{
			if (data->tsprite[i].angle_l < 0)
				data->tsprite[i].angle_l = 360 + data->tsprite[i].angle_l;
			if (data->tsprite[i].angle_l > 359)
				data->tsprite[i].angle_l = data->tsprite[i].angle_l - 359;
			if (data->tsprite[i].angle_f < 0)
				data->tsprite[i].angle_f = 360 + data->tsprite[i].angle_f;
			if (data->tsprite[i].angle_f > 359)
				data->tsprite[i].angle_f = data->tsprite[i].angle_f - 359;
				printf(GREEN "sizex: %d, _f, _l: %lf, %lf\n" RESET, data->tsprite[i].sizex, data->tsprite[i].angle_f, data->tsprite[i].angle_l);
			ft_zbuffer(data, &data->tsprite[i], pas);
		}
		//if ((float)data->tsprite[i].angle == data->vec[data->R[0] / 2].angle)
		//		printf(GREEN "angle : %lf, j: %d\n" RESET, data->tsprite[i].angle, j);

		i++;
	}
}

void 	ft_zbuffer(t_data *data, t_sprite *sprite, float pas)
{
	printf("---drawing sprite---\n");
	int i;
	float angle_s;
	int size;
	int	pixel;

	i = 0;
	pixel = -1;
	size = 0;
	angle_s = sprite->angle_f;
	while (size <= sprite->sizey)
	{
		while (i < data->R[0] - 1)
		{
			//printf("angle: %f, %f\n", data->vec[i].angle, data->vec[i+1].angle);
			if (angle_s >= data->vec[i].angle && angle_s <= data->vec[i + 1].angle)
			{
				pixel = i;
				break ;
			}
			i++;
		}
		if (pixel != -1)
			break;
		size++;
		angle_s += pas;
		i = 0;
		printf("size:_s :%d\n", sprite->sizex - size);
	}
	ft_draw_sprites(data, pixel, sprite->sizex - size, sprite);
	printf("pixel: %d\n", pixel);
}

void 	ft_show_tsprite(t_sprite *tsprite, int s_max)
{
	int i;

	i = 0;
	while (i < s_max)
	{
		printf("i : %d x, y: %f, %f, pix %d, hit: %d, dist: %f, offset: %f\n angle: cos: %lf, sin: %lf, angle: %lf\n", i,
		tsprite[i].x, tsprite[i].y, tsprite[i].pixel_hit, tsprite[i].hit, tsprite[i].dist,
		tsprite[i].offset, tsprite[i].rotx, tsprite[i].roty, tsprite[i].angle);
		printf("dx, dy: %f, %f\n", tsprite[i].distx, tsprite[i].disty);
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
		tsprite[i].angle = 0;
		tsprite[i].dist = -1;
		tsprite[i].dist = -1;
		tsprite[i].dist = -1;
		i++;
	}
}

void 	ft_draw_sprites(t_data *data, int pixel, int sizex, t_sprite *sprite)
{
	int i = 0;
	int xpixel;
	int xn_pixel;
	int x_pas;

	i = pixel;
	xn_pixel = data->tex[4].w / sprite->sizex;
	xpixel = data->tex[4].w * (sizex / sprite->sizex);
	while (i < data->R[0] && i < sizex + pixel)
	{
		if (sprite->dist < data->vec[i].dist_towall) // draw a collum
			ft_draw_a_colum_sprite(data, i, sprite->sizey, xpixel);
		i++;
		xpixel += (data->tex[4].w / sprite->sizex);
		//		printf("i: %d\nlsat - hit: %d, width: %d\n", i, data->tsprite[n].pixel_last - data->tsprite[n].pixel_hit, w_sprite);
	}
}

void 	ft_draw_a_colum_sprite(t_data *data, int i, int hp, int xpixel)
{
	unsigned long		j = 0;
	int					n_pixel;
	unsigned char		color[3];

	n_pixel = 1;
	if (hp <= data->R[1])
		j = (data->R[1] / 2) - (hp / 2);
	else
	{
		j = 0;
		n_pixel = (hp - data->R[1]) / 2;
	}
	while (j <= (data->R[1] / 2) + (hp / 2) && j <  data->R[1])
	{
		ft_get_tex_ypixel_sprite(data, xpixel, n_pixel, color, hp);
	//	if (color[0] == 0 && color[1] == 0 && color[2] == 0)
	//		break ;
		data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 0] = (char)color[0];
		data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 1] = (char)color[1];
		data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 2] = (char)color[2];
		data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 3] = (char)0;
		j++;
		n_pixel += 1;
	}
}

void 	ft_get_tex_ypixel_sprite(t_data *data, int xpixel, int n_pixel, unsigned char *color, int hp)
{
	int	ypixel;

	ypixel = (int)(data->tex[4].h * n_pixel / hp);
	if (ypixel > data->tex[4].h - 1)
		ypixel = data->tex[4].h - 1;
	if (xpixel > data->tex[4].w - 1)
		xpixel = data->tex[4].w - 1;
	color[0] = data->tex[4].img[ypixel * data->tex[4].sl + (xpixel * 4)];
	color[1] = data->tex[4].img[ypixel * data->tex[4].sl + (xpixel * 4) + 1];
	color[2] = data->tex[4].img[ypixel * data->tex[4].sl + (xpixel * 4) + 2];
}
