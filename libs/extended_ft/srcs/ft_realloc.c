/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:34:45 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/18 14:30:51 by hlibine          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "extended_ft.h"

void	*ft_realloc(void *in, size_t oldsize, size_t newsize)
{
	void	*out;

	out = galloc(newsize);
	if (!out)
		return (NULL);
	if (!in)
		return (out);
	out = ft_memcpy(out, in, oldsize);
	gfree(in);
	return (out);
}
