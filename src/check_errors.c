/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:54 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/20 08:38:50 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static int	has_valid_characters(char **lines, int *p, int *c, int *e)
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
			if (lines[i][j] == 'P')
				(*p)++;
			else if (lines[i][j] == 'C')
				(*c)++;
			else if (lines[i][j] == 'E')
				(*e)++;
			else if (lines[i][j] != '1' && lines[i][j] != '0')
				return (write(2, "map has invalid characters\n", 27));
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_rectangular(char **lines)
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

static int	is_surronded_by_walls(char **lines)
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

int	check_map(char *map)
{
	char	**lines;
	int		count_p;
	int		count_c;
	int		count_e;

	count_p = 0;
	count_c = 0;
	count_e = 0;
	lines = ft_split(map, '\n');
	if (!lines || !lines[0])
		return (1);
	if (is_rectangular(lines))
		return (free_split(lines), 1);
	if (has_valid_characters(lines, &count_p, &count_c, &count_e))
		return (free_split(lines), 1);
	if (is_surronded_by_walls(lines))
		return (free_split(lines), 1);
	if (count_p != 1 || count_e != 1 || count_c < 1)
	{
		write(2, "map is not valid\n", 17);
		return (free_split(lines), 1);
	}
	free_split(lines);
	return (0);
}

void	free_split(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}
