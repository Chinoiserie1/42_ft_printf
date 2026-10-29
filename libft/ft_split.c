/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 17:30:55 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/16 15:57:03 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	occurence_of_char(char const *s, char c)
{
	size_t	counter;

	counter = 0;
	while (*s != '\0')
	{
		if (*s == c && *(s + 1) != c && *(s + 1) != '\0')
			counter++;
		s++;
	}
	return (counter);
}

static char	**free_split(char **split, size_t i)
{
	while (i > 0)
	{
		i--;
		free(split[i]);
	}
	free(split);
	return (NULL);
}

static char	**fill_split(char **split, char *strim, char c)
{
	size_t	counter;
	size_t	i;
	size_t	start_place;
	size_t	len;

	counter = 0;
	i = 0;
	start_place = 0;
	len = ft_strlen(strim);
	while (counter <= len)
	{
		if (counter > 0 && strim[counter - 1] != c
			&& (strim[counter] == c || strim[counter] == '\0'))
		{
			split[i] = ft_substr(strim, start_place, counter - start_place);
			if (split[i] == NULL)
				return (free_split(split, i));
			i++;
		}
		if (counter < len && strim[counter] == c && strim[counter + 1] != c)
			start_place = counter + 1;
		counter++;
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	*strim;
	char	trimset[2];

	if (s == NULL)
		return (NULL);
	trimset[0] = c;
	trimset[1] = '\0';
	strim = ft_strtrim(s, trimset);
	if (strim == NULL)
		return (NULL);
	split = malloc((occurence_of_char(strim, c) + 2) * sizeof(char *));
	if (split == NULL)
	{
		free(strim);
		return (NULL);
	}
	split = fill_split(split, strim, c);
	free(strim);
	return (split);
}
