/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:16:57 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/19 10:26:48 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/so_long.h"

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

void	render_map(void *mlx, void *window, char **map,
	void *wall_img, void *player_img, void *collectible_img,
	void *exit_img, void *empty_img)
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
				mlx_put_image_to_window(mlx, window, wall_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (map[y][x] == 'P')
				mlx_put_image_to_window(mlx, window, player_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (map[y][x] == 'C')
				mlx_put_image_to_window(mlx, window, collectible_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (map[y][x] == 'E')
				mlx_put_image_to_window(mlx, window, exit_img, x * TILE_SIZE, y * TILE_SIZE);
			else
				mlx_put_image_to_window(mlx, window, empty_img, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	init_map(void *mlx, void *window, char **map)
{
	void	*wall_img;
	void	*player_img;
	void	*collectible_img;
	void	*exit_img;
	void	*empty_img;
	int		width;
	int		height;

	wall_img = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &width, &height);
	player_img = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &width, &height);
	collectible_img = mlx_xpm_file_to_image(mlx, "textures/collectible.xpm", &width, &height);
	exit_img = mlx_xpm_file_to_image(mlx, "textures/exit.xpm", &width, &height);
	empty_img = mlx_xpm_file_to_image(mlx, "textures/empty.xpm", &width, &height);
if (!wall_img || !player_img || !collectible_img || !exit_img || !empty_img)
{
	write(2, "Error: Failed to load images\n", 29);
	if (wall_img) mlx_destroy_image(mlx, wall_img);
	if (player_img) mlx_destroy_image(mlx, player_img);
	if (collectible_img) mlx_destroy_image(mlx, collectible_img);
	if (exit_img) mlx_destroy_image(mlx, exit_img);
	if (empty_img) mlx_destroy_image(mlx, empty_img);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	free(mlx);
	return;
}
	render_map(mlx, window, map, wall_img, player_img, collectible_img, exit_img, empty_img);
}

void cleanup(void *mlx, void *window, char **map, void *wall_img, void *player_img,
			void *collectible_img, void *exit_img, void *empty_img)
{
	if (wall_img)
		mlx_destroy_image(mlx, wall_img);
	if (player_img)
		mlx_destroy_image(mlx, player_img);
	if (collectible_img)
		mlx_destroy_image(mlx, collectible_img);
	if (exit_img)
		mlx_destroy_image(mlx, exit_img);
	if (empty_img)
		mlx_destroy_image(mlx, empty_img);
	if (window)
		mlx_destroy_window(mlx, window);
	if (mlx)
	{
		mlx_destroy_display(mlx);
		free(mlx);
	}
	if (map)
		free_lines(map);
}

