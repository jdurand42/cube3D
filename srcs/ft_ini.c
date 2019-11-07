/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:36:37 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/07 19:01:07 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

char	**ft_parse_map(t_data *data, char *file)
{
	size_t	i;
	char	*buffer;

	i = 0;
	while (get_next_line_file(file, &buffer));
	{
		while (*buffer != 0)
		{
			while (*buffer == 32)
				buffer++;
			ft_do_arg(buffer);
		}
	}
}
