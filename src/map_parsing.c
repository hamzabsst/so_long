/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 08:16:57 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/22 09:18:06 by hbousset         ###   ########.fr       */
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

void	render_map(void *m, void *w, char **map, t_game *g)
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
				mlx_put_image_to_window(m, w, g->txr.wall, x * SIZE, y * SIZE);
			else if (map[y][x] == 'P' && g->last_was_exit)
				mlx_put_image_to_window(m, w, g->txr.p_e, x * SIZE, y * SIZE);
			else if (map[y][x] == 'P')
				mlx_put_image_to_window(m, w, g->txr.plr, x * SIZE, y * SIZE);
			else if (map[y][x] == 'C')
				mlx_put_image_to_window(m, w, g->txr.item, x * SIZE, y * SIZE);
			else if (map[y][x] == 'E')
				mlx_put_image_to_window(m, w, g->txr.exit, x * SIZE, y * SIZE);
			else if (map[y][x] == 'B')
				mlx_put_image_to_window(m, w, g->txr.boss, x * SIZE, y * SIZE);
			else
				mlx_put_image_to_window(m, w, g->txr.empty, x * SIZE, y * SIZE);
			x++;
		}
		y++;
	}
}

static void	player_on_e(t_game *game)
{
	if (game->map[game->player_y][game->player_x] == 'P')
	{
		if (game->last_was_exit)
			game->map[game->player_y][game->player_x] = 'E';
		else
			game->map[game->player_y][game->player_x] = '0';
	}
}

static int	status(t_game *game, int x, int y)
{
	char	next_pos;

	next_pos = game->map[y][x];
	if (next_pos == 'C')
		game->collected++;
	else if (next_pos == 'B')
	{
		ft_printf("Game Over! The boss defeated you!\n");
		close_window(game);
	}
	else if (next_pos == 'E')
	{
		if (game->collected == game->collectibles)
		{
			ft_printf("Congratulations! You won!\n");
			close_window(game);
		}
		else
			ft_printf("Collect all items first! (%d/%d)\n",
				game->collected, game->collectibles);
	}
	player_on_e(game);
	game->map[y][x] = 'P';
	game->player_x = x;
	game->player_y = y;
	game->last_was_exit = (next_pos == 'E');
	game->moves++;
	return (0);
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
		status(game, new_x, new_y);
		render_map(game->mlx, game->window, game->map, game);
		display_moves(game);
	}
	return (0);
}
