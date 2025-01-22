/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_txr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:13:44 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/22 11:24:18 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/so_long.h"

static void	init_txr(void *mlx, t_game *game)
{
	int	w;
	int	h;

	game->txr.wall = NULL;
	game->txr.plr = NULL;
	game->txr.item = NULL;
	game->txr.exit = NULL;
	game->txr.empty = NULL;
	game->txr.p_e = NULL;
	game->txr.boss = NULL;
	game->txr.wall = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &w, &h);
	game->txr.plr = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &w, &h);
	game->txr.item = mlx_xpm_file_to_image(mlx, "textures/item.xpm", &w, &h);
	game->txr.exit = mlx_xpm_file_to_image(mlx, "textures/exit.xpm", &w, &h);
	game->txr.empty = mlx_xpm_file_to_image(mlx, "textures/empty.xpm", &w, &h);
	game->txr.p_e = mlx_xpm_file_to_image(mlx, "textures/p_e.xpm", &w, &h);
	game->txr.boss = mlx_xpm_file_to_image(mlx, "textures/boss.xpm", &w, &h);
	game->pframes[0] = mlx_xpm_file_to_image(mlx, "textures/plr1.xpm", &w, &h);
	game->pframes[1] = mlx_xpm_file_to_image(mlx, "textures/plr2.xpm", &w, &h);
	game->pframes[2] = mlx_xpm_file_to_image(mlx, "textures/plr3.xpm", &w, &h);
	game->iframes[0] = mlx_xpm_file_to_image(mlx, "textures/egg0.xpm", &w, &h);
	game->iframes[1] = mlx_xpm_file_to_image(mlx, "textures/egg1.xpm", &w, &h);
	game->iframes[2] = mlx_xpm_file_to_image(mlx, "textures/item.xpm", &w, &h);
}

void	load_txr(void *mlx, t_game *game)
{
	init_txr(mlx, game);
	if (!game->txr.wall || !game->txr.plr || !game->txr.p_e || !game->txr.boss)
	{
		write(2, "Error: Failed to load textures\n", 30);
		close_window(game);
	}
	if (!game->txr.item || !game->txr.exit || !game->txr.empty)
	{
		write(2, "Error: Failed to load textures\n", 30);
		close_window(game);
	}
	render_map(mlx, game->window, game->map, game);
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

void	display_moves(t_game *game)
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
