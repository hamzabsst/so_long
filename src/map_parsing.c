/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:16:57 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/22 11:41:22 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/so_long.h"

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
	if (check_sprites(count_p, count_e, count_c))
		return (free_split(lines), 1);
	if (is_valid_path(lines))
		return (free_split(lines), 1);
	free_split(lines);
	return (0);
}

char	*read_map(const char *map)
{
	int		fd;
	ssize_t	bytes_read;
	char	*buffer;

	buffer = malloc(MAP_BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		free(buffer);
		return (NULL);
	}
	bytes_read = read(fd, buffer, MAP_BUFFER_SIZE);
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

static void	render_tile(t_render *r, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(r->m, r->w, r->g->txr.wall, x * SIZE, y * SIZE);
	else if (c == 'P' && r->g->last_was_exit)
		mlx_put_image_to_window(r->m, r->w, r->g->txr.p_e, x * SIZE, y * SIZE);
	else if (c == 'P')
		mlx_put_image_to_window(r->m, r->w,
			r->g->pframes[r->g->anim_frame], x * SIZE, y * SIZE);
	else if (c == 'C')
		mlx_put_image_to_window(r->m, r->w,
			r->g->iframes[r->g->anim_frame], x * SIZE, y * SIZE);
	else if (c == 'E')
		mlx_put_image_to_window(r->m, r->w, r->g->txr.exit, x * SIZE, y * SIZE);
	else if (c == 'B')
		mlx_put_image_to_window(r->m, r->w, r->g->txr.boss, x * SIZE, y * SIZE);
	else
		mlx_put_image_to_window(r->m, r->w,
			r->g->txr.empty, x * SIZE, y * SIZE);
}

void	render_map(void *m, void *w, char **map, t_game *g)
{
	t_render	r;
	int			x;
	int			y;

	r.m = m;
	r.w = w;
	r.g = g;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			render_tile(&r, map[y][x], x, y);
			x++;
		}
		y++;
	}
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
