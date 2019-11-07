/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:36:08 by jdurand           #+#    #+#             */
/*   Updated: 2019/10/18 12:36:01 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content)
{
	t_list			*buffer;

	if (!(buffer = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
		content = NULL;
	else
		buffer->content = (void*)content;
	buffer->next = NULL;
	return (buffer);
}
