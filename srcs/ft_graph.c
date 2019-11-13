/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:26:07 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/13 23:39:09 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

#define H 600
#define W 400

unsigned int 	ft_rgb(unsigned int *color, int r, int g, int b)
{
	*color = 0;
	*color |= (b << 0);
	*color |= (g << 8);
	*color |= (r << 16);
	return (*color);
}

double ft_get_d_90(t_data *data, int **map)
{
	double rayx, rayy;
	double dirx, diry;

	rayx = data->posx; rayy = data->posy;
	dirx = data->posx; diry = 0;
	printf("in d90\n");
	printf("dir: %d\n", map[(int)rayy][(int)rayx]);
	while (map[(int)rayy][(int)rayx] != 1)
	{
		if (rayx != dirx)
			rayx += 0.1;
		if (rayy != diry)
			rayy -= 0.1;
		printf("rayx: %lf || rayy: %lf\n", rayx, rayy);
	}
	return (sqrt(pow(rayx - data->posx, 2.0) + pow(rayy - data->posy, 2.0)));
}


void 	ft_do_graphism(int **map, t_data *data)
{
	void 	*mlx_p;
	void 	*mlx_wd;
	void 	*mlx_img;
	int bit_p_p;
	int size_line;
	int endian;
	char buffer[2];
	int i = 0; int j = 0;
	unsigned int color = 0;


	if ((mlx_p = mlx_init()))
		printf("succes mlx\n");
	mlx_wd = mlx_new_window(mlx_p, W, H, "onanisme");
	if (mlx_wd)
		printf("%p\n", mlx_wd);
	mlx_img = mlx_new_image(mlx_p, W, H);
	if (!mlx_img)
		return ;
	char *img = mlx_get_data_addr(mlx_img, &bit_p_p, &size_line, &endian);
	printf("bpp: %d, sizeline: %d, endian: %d\n", bit_p_p, size_line, endian);
	printf("%s\n", img);

	while (i < size_line * H)
	{
		img[i] = -1;
		img[i + 1] = 0;
		img[i + 2] = 0;
		i += 4;
	}
	mlx_put_image_to_window(mlx_p, mlx_wd, mlx_img, 0, 0);
	i = 0; j = 0;


	printf("x: %lf, y: %lf\n", data->posx, data->posy);

	int taille_mur; double d_eucli;
	while (map[(int)data->posy][(int)data->posx] != 1)
	{
		printf("%.25lf\n", d_eucli = ft_get_d_90(data, map));
		taille_mur = H / d_eucli;
		while (i < H * size_line)
		{
			if (i > ((size_line * H / 2) - (taille_mur * size_line / 2))
			&& i < (H * size_line / 2) + (taille_mur * size_line / 2))
			{
				img[i] = 120;
				img[i + 1] = 12;
				img[i + 2] = 12;
			//	printf("coloring\n");
			}
			i += 4;
		}
		i = 0;
		mlx_put_image_to_window(mlx_p, mlx_wd, mlx_img, 0, 0);
		if (get)
		data->posy -= 0.21;
	printf("out\n");
	}
	mlx_loop(mlx_p);
}

/*
H * size_line = nombre de bits dans img

*/
/*
void 	ft_do_graphism(int **map, t_data *data)
{
	void 	*mlx_p;
	void 	*mlx_wd;
	int i = 0; int j = 0;
	unsigned int color = 0;

	if ((mlx_p = mlx_init()))
		printf("succes mlx\n");
	mlx_wd = mlx_new_window(mlx_p, W, H, "onanisme");
	if (mlx_wd)
		printf("%p\n", mlx_wd);

	while (j < H)
		{
			while (i < W)
				mlx_pixel_put(mlx_p, mlx_wd, i++, j, ft_rgb(&color, 0, 0, 0));
			i = 0;
			j++;
		}
	i = 0; j = 0;

	printf("x: %lf, y: %lf\n", data->posx, data->posy);

	int taille_mur; double d_eucli;

	while (map[(int)data->posy][(int)data->posx] != 1)
	{
		printf("%.25lf\n", d_eucli = ft_get_d_90(data, map));
		taille_mur = H / d_eucli;
		while (j < H)
		{
	 	if (j > H / 2 - (taille_mur / 2) && j < H / 2 + (taille_mur / 2))
	 		while (i < W)
	 			mlx_pixel_put(mlx_p, mlx_wd, i++, j, ft_rgb(&color, 255, 255, 0));
			j++;
			i = 0;
		}
		j = 0;
		data->posy -= 0.21;
	}
	mlx_loop(mlx_p);
}*/





/*	while (j < H)
	{
		while (i < W)
			mlx_pixel_put(mlx_p, mlx_wd, i++, j, color);
		i = 0;
		j++;
	}
	ft_rgb_code(&color, 147, 112, 219);
	j = H / 4; i = W / 4;
	while (j < (H - H / 4))
	{
		while (i < W - W / 4)
			mlx_pixel_put(mlx_p, mlx_wd, i++, j, color);
		i = W / 4; j++;
	}*/
