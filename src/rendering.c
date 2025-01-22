/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:28:24 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/22 11:30:03 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/so_long.h"

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

static void	player_pos(t_game *game, char next_pos)
{
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
}

static int	status(t_game *game, int x, int y)
{
	char	next_pos;

	next_pos = game->map[y][x];
	player_pos(game, next_pos);
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
	}
	return (0);
}
