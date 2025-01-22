/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:54 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/22 11:44:02 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	check_character(char c, int *p, int *c_count, int *e)
{
	if (c == 'P')
		(*p)++;
	else if (c == 'C')
		(*c_count)++;
	else if (c == 'E')
		(*e)++;
	else if (c != '1' && c != '0' && c != 'B')
		return (write(2, "map has invalid characters\n", 27));
	return (0);
}

int	has_valid_characters(char **lines, int *p, int *c, int *e)
{
	int	i;
	int	j;

	*p = 0;
	*c = 0;
	*e = 0;
	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (check_character(lines[i][j], p, c, e))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_rectangular(char **lines)
{
	size_t	size;
	int		i;

	if (!lines || !(lines[0]))
		return (1);
	size = ft_strlen(lines[0]);
	i = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) != size)
			return (write(2, "map is not rectangular\n", 23));
		i++;
	}
	return (0);
}

int	is_surronded_by_walls(char **lines)
{
	int		i;
	int		width;
	int		height;

	if (!lines || !lines[0])
		return (1);
	width = ft_strlen(lines[0]);
	height = 0;
	while (lines[height])
		height++;
	i = 0;
	while (i < width)
	{
		if (lines[0][i] != '1' || lines[height - 1][i] != '1')
			return (write(2, "map is not surronded by walls\n", 30));
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (lines[i][0] != '1' || lines[i][width - 1] != '1')
			return (write(2, "map is not surronded by walls\n", 30));
		i++;
	}
	return (0);
}

int	check_sprites(int count_p, int count_e, int count_c)
{
	if (count_p != 1)
		return (write(2, "Error: no player is found\n", 26));
	if (count_e != 1)
		return (write(2, "Error: no exit is found\n", 24));
	if (count_c < 1)
		return (write(2, "Error: no collecitble is found\n", 31));
	return (0);
}
