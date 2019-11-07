/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_str_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:57:08 by jdurand           #+#    #+#             */
/*   Updated: 2019/10/31 12:07:50 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char	*ft_file_str(int fd)
{
	int		ret;
	char	*line;
	char	*b_line;
	char	buffer[1000001];

	while ((ret = read(fd, buffer, 1000000)) > 0)
	{
		buffer[ret] = 0;
		b_line = line;
		line = ft_strjoin(line, buffer);
		free(b_line);
		b_line = NULL;
	}
	return (line);
}
