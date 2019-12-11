/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 17:33:42 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 21:15:42 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int		ft_iserror(int code)
{
	if (code == 1)
		ft_putstr("Error\nFile opening aborted\n");
	else if (code == 2)
		ft_putstr("Error\nWhile gnl\n");
	else if (code == 3)
		ft_putstr("Error\nIn game loop\n");
	return (1);
}
