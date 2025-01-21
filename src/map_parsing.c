/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:16:57 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/21 08:00:02 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/so_long.h"

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

void	init_map(void *mlx, t_game *game)
{
	int	w;
	int	h;

	game->txr.wall = NULL;
	game->txr.plr = NULL;
	game->txr.item = NULL;
	game->txr.exit = NULL;
	game->txr.empty = NULL;
	game->txr.wall = mlx_xpm_file_to_image(mlx, "txr/wall.xpm", &w, &h);
	game->txr.plr = mlx_xpm_file_to_image(mlx, "txr/player.xpm", &w, &h);
	game->txr.item = mlx_xpm_file_to_image(mlx, "txr/item.xpm", &w, &h);
	game->txr.exit = mlx_xpm_file_to_image(mlx, "txr/exit.xpm", &w, &h);
	game->txr.empty = mlx_xpm_file_to_image(mlx, "txr/empty.xpm", &w, &h);
	if (!game->txr.wall || !game->txr.plr)
	{
		write(2, "Error: Failed to load textures\n", 30);
		close_window(game);
	}
	if (!game->txr.item || !game->txr.exit || !game->txr.empty)
	{
		write(2, "Error: Failed to load textures\n", 30);
		close_window(game);
	}
	render_map(mlx, game->window, game->map, &game->txr);
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

int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x;
	new_y = game->player_y;
	if (keycode == KEY_W || keycode == KEY_UP)
		new_y--;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		new_y++;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		new_x--;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		new_x++;
	if (keycode == KEY_ESC)
		close_window(game);
	if (game->map[new_y][new_x] != '1')
	{
		game->map[game->player_y][game->player_x] = '0';
		game->map[new_y][new_x] = 'P';
		game->player_x = new_x;
		game->player_y = new_y;
		render_map(game->mlx, game->window, game->map, &game->txr);
	}
	return (0);
}

void	init_player_position(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}
