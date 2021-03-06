/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:30:46 by mkotytsk          #+#    #+#             */
/*   Updated: 2018/10/31 17:31:28 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *p, size_t n)
{
	size_t	i;
	char	*t;

	i = 0;
	t = p;
	while (i < n)
	{
		t[i++] = 0;
	}
}
