/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:26:07 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/13 20:54:31 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

#define H 712
#define W 930

unsigned int 	ft_rgb(unsigned int *color, int r, int g, int b)
{
	*color = 0;
	*color |= (b << 0);
	*color |= (g << 8);
	*color |= (r << 16);
	return (*color);
}

int ft_get_d_90(t_data *data, int **map)
{
	double rayx, rayy;
	double dirx, diry;

	rayx = (double)data->posx; rayy = 7.00000;
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
	printf("%lf\n", rayy);
	printf("%lf\n", rayy - data->posy);
	return (sqrt(pow(rayx - data->posx, 2) + pow(rayy - data->posy, 2)));
}

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
	double d_eucli;
	printf("deucli: %lf\n", d_eucli = ft_get_d_90(data, map));
	int taille_mur = H / d_eucli;

	while (j < H)
	{
	 if (j > H / 2 - (taille_mur / 2) && j < H / 2 + (taille_mur / 2))
	 	while (i < W)
	 		mlx_pixel_put(mlx_p, mlx_wd, i++, j, ft_rgb(&color, 255, 0, 0));
		j++;
		i = 0;
	}
	printf("out of d90\n");
	mlx_loop(mlx_p);
}





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
