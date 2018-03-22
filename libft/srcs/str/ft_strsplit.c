/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmonnier <gmonnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 07:57:48 by gmonnier          #+#    #+#             */
/*   Updated: 2017/11/09 10:52:51 by gmonnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_size_word(char const *str, char c)
{
	int i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static int		ft_count_words(char const *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
			i++;
		if (str[i - 1] != c)
			count++;
	}
	return (count);
}

static char		*ft_print_word(char **ptr, char c)
{
	int		j;
	char	*word;
	int		size;

	j = 0;
	size = ft_size_word(*ptr, c);
	if ((word = (char*)malloc(sizeof(*word) * (size + 1))) == NULL)
		return (NULL);
	while (j < size)
	{
		word[j] = **ptr;
		(*ptr)++;
		j++;
	}
	word[j] = '\0';
	return (word);
}

char			**ft_strsplit(char const *str, char c)
{
	char	**tab_words;
	int		i;
	int		nb_words;
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = (char*)str;
	nb_words = ft_count_words(str, c);
	if ((tab_words = (char**)malloc(sizeof(*tab_words) * (nb_words + 1)))
	== NULL)
		return (NULL);
	i = 0;
	while (i < nb_words)
	{
		while (*ptr == c)
			ptr++;
		tab_words[i] = ft_print_word(&ptr, c);
		i++;
	}
	tab_words[i] = 0;
	return (tab_words);
}
