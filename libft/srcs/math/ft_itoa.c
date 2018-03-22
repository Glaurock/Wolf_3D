/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:34 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/10 12:43:02 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_calc_size(int cpy, int n)
{
	int len;

	len = 0;
	while (cpy)
	{
		len++;
		cpy /= 10;
	}
	if (n < 0 || !n)
		len++;
	return (len);
}

char			*ft_itoa(int n)
{
	int		len;
	int		cpy;
	char	*str;
	int		i;

	cpy = n < 0 ? n : -n;
	len = ft_calc_size(cpy, n);
	if ((str = (char*)malloc(len + 1)) == NULL)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[i++] = '-';
		len--;
	}
	cpy = n < 0 ? n : -n;
	while (len--)
	{
		str[i++] = -(cpy / ft_recursive_power(10, len)) + '0';
		cpy %= ft_recursive_power(10, len);
	}
	str[i] = '\0';
	return (str);
}
