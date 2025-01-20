/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:16:57 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/20 08:53:51 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/so_long.h"

char	*read_map(const char *map)
{
	int		fd;
	ssize_t	bytes_read;
	char	*buffer;

	buffer = malloc(1000);
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

void	render_map(void *mlx, void *w, char **map, t_txr *txr)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				mlx_put_image_to_window(mlx, w, txr->wall, x * SIZE, y * SIZE);
			else if (map[y][x] == 'P')
				mlx_put_image_to_window(mlx, w, txr->plr, x * SIZE, y * SIZE);
			else if (map[y][x] == 'C')
				mlx_put_image_to_window(mlx, w, txr->item, x * SIZE, y * SIZE);
			else if (map[y][x] == 'E')
				mlx_put_image_to_window(mlx, w, txr->exit, x * SIZE, y * SIZE);
			else
				mlx_put_image_to_window(mlx, w, txr->empty, x * SIZE, y * SIZE);
			x++;
		}
		y++;
	}
}

void init_map(void *mlx, void *window, char **map)
{
	t_txr	txr;
	int		width;
	int		height;

	txr.wall = mlx_xpm_file_to_image(mlx, "txr/wall.xpm", &width, &height);
	txr.plr = mlx_xpm_file_to_image(mlx, "txr/player.xpm", &width, &height);
	txr.item = mlx_xpm_file_to_image(mlx, "txr/item.xpm", &width, &height);
	txr.exit = mlx_xpm_file_to_image(mlx, "txr/exit.xpm", &width, &height);
	txr.empty = mlx_xpm_file_to_image(mlx, "txr/empty.xpm", &width, &height);
	if (!txr.wall || !txr.plr || !txr.item || !txr.exit || !txr.empty)
	{
		write(2, "Error: Failed to load textures\n", 30);
		if (txr.wall) mlx_destroy_image(mlx, txr.wall);
		if (txr.plr) mlx_destroy_image(mlx, txr.plr);
		if (txr.item) mlx_destroy_image(mlx, txr.item);
		if (txr.exit) mlx_destroy_image(mlx, txr.exit);
		if (txr.empty) mlx_destroy_image(mlx, txr.empty);
		return ;
	}
	render_map(mlx, window, map, &txr);
	mlx_destroy_image(mlx, txr.wall);
	mlx_destroy_image(mlx, txr.plr);
	mlx_destroy_image(mlx, txr.item);
	mlx_destroy_image(mlx, txr.exit);
	mlx_destroy_image(mlx, txr.empty);
}
