/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:38:54 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/18 20:47:44 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

char	*read_map(const char *map)
{
	int		fd;
	ssize_t	bytes_read;
	char		*buffer;

	buffer = malloc(1001);
	if (!buffer)
		return (NULL);
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		free(buffer);
		return (NULL);
	}
	bytes_read = read(fd, buffer, 1000);
	if (bytes_read <= 0)
	{
		free(buffer);
		close(fd);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	close(fd);
	return (buffer);
}

static int	has_valid_characters(char **lines, int *count_p, int *count_c, int *count_e)
{
	int	i;
	int	j;

	*count_p = 0;
	*count_c = 0;
	*count_e = 0;
	i = 0;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == 'P')
				(*count_p)++;
			else if (lines[i][j] == 'C')
				(*count_c)++;
			else if (lines[i][j] == 'E')
				(*count_e)++;
			else if (lines[i][j] != '1' && lines[i][j] != '0')
				return (1);
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
			return (1);
		i++;
	}
	return (0);
}

static int is_surronded_by_walls(char **lines)
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
			return (1);
		i++;
	}
	i = 0;
	while (i < height)
	{
		if (lines[i][0] != '1' || lines[i][width - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_map(char *map)
{
	char	**lines;
	int		count_p = 0;
	int		count_c = 0;
	int		count_e = 0;

	lines = ft_split(map, '\n');
	if (!lines || !lines[0])
		return (1);
	if (is_rectangular(lines))
	{
		write(2, "map is not rectangular\n", 23);
		return (free_lines(lines), 1);
	}
	if (has_valid_characters(lines, &count_p, &count_c, &count_e))
	{
		write(2, "map has invalid characters\n", 27);
		return (free_lines(lines), 1);
	}
	if (is_surronded_by_walls(lines))
	{
		write(2, "map is not surronded by walls\n", 30);
		return (free_lines(lines), 1);
	}
	if (count_p != 1 || count_e != 1 || count_c < 1)
	{
		write(2, "map is not valid\n", 17);
		return (free_lines(lines), 1);
	}
	free_lines(lines);
	return (0);
}
void	free_lines(char **lines)
{
	int	i = 0;

	while (lines[i])
		free(lines[i++]);
	free(lines);
}

