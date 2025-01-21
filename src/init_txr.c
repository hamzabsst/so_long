/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_txr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:13:44 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/21 14:51:35 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/so_long.h"

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

void	init_collectibles(t_game *game)
{
	int	x;
	int	y;

	game->collected = 0;
	game->collectibles = 0;
	game->won = 0;
	game->moves = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'C')
				game->collectibles++;
			x++;
		}
		y++;
	}
}

void display_moves(t_game *game)
{
	char	*moves;
	char	*tmp;

	tmp = ft_itoa(game->moves);
	moves = ft_strjoin("Moves: ", tmp);
	free(tmp);
	mlx_put_image_to_window(game->mlx, game->window, game->black_bg, 1, 1);
	mlx_string_put(game->mlx, game->window, 10, 20, 0xFFFFFF, moves);
	free(moves);
}
