/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:46 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 10:52:14 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_copy(char *dest, char *src, int autorised)
{
	int j;

	j = 0;
	while (*dest)
		dest++;
	while (j < autorised)
	{
		*dest = *src;
		dest++;
		src++;
		j++;
	}
	*dest = '\0';
}

size_t				ft_strlcat(char *dest, const char *src, size_t size)
{
	int		autorised;
	int		dest_len;
	char	*copy_dest;
	char	*copy_src;

	copy_dest = dest;
	copy_src = (char*)src;
	dest_len = ft_strlen(dest);
	autorised = size - 1 - dest_len;
	if (autorised < 0)
		return (ft_strlen(copy_src) + size);
	else
	{
		ft_copy(copy_dest, copy_src, autorised);
		return (dest_len + ft_strlen(copy_src));
	}
}
