/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:50:07 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/20 14:36:53 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static t_point	find_player(char **map)
{
	t_point	pos;
	int		y;
	int		x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'P')
			{
				pos.x = x;
				pos.y = y;
				return (pos);
			}
			x++;
		}
		y++;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

static void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

static int	check_path(char **map_copy)
{
	int	y;
	int	x;

	y = 0;
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] == 'C' || map_copy[y][x] == 'E')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static char	**copy_map(char **map)
{
	char	**copy;
	int		i;
	int		height;

	height = 0;
	while (map[height])
		height++;
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (free_split(copy), NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	is_valid_path(char **map)
{
	char	**map_copy;
	t_point	player;
	int		result;

	map_copy = copy_map(map);
	if (!map_copy)
		return (1);
	player = find_player(map_copy);
	if (player.x == -1 || player.y == -1)
		return (free_split(map_copy), 1);
	flood_fill(map_copy, player.x, player.y);
	result = check_path(map_copy);
	free_split(map_copy);
	if (result)
		return (write(2, "Error: No valid path exists\n", 27));
	return (0);
}
