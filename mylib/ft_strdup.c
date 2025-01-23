/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:27:05 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/16 18:02:24 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myLib.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	size;
	char	*results;

	size = ft_strlen(s);
	results = (char *) malloc((size + 1) * sizeof(char));
	if (!results)
		return (NULL);
	i = 0;
	while (s[i])
	{
		results[i] = s[i];
		i++;
	}
	results[i] = '\0';
	return (results);
}
