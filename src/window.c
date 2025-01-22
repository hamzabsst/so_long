/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:38:45 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/22 18:43:29 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	init_variables(t_game *game)
{
	game->mlx = mlx_init();
	game->last_was_exit = 0;
	game->anim_frame = 0;
	game->anim_timer = 0;
	game->frame_count = 0;
	game->frames_per_update = 10000;
	game->boss_direction = 1;
	game->bosses = NULL;
}

void	init_window(t_game *game)
{
	int	bpp;
	int	size_line;
	int	endian;
	int	*data;
	int	i;

	i = 0;
	init_variables(game);
	game->width = ft_strlen(game->map[0]);
	while (game->map[i])
		i++;
	game->height = i;
	i = 0;
	game->window = mlx_new_window(game->mlx, game->width * SIZE,
			game->height * SIZE, "so_long");
	game->black_bg = mlx_new_image(game->mlx, 70, 30);
	data = (int *)mlx_get_data_addr(game->black_bg, &bpp, &size_line, &endian);
	while (i < 70 * 30)
	{
		data[i] = 0x000000;
		i++;
	}
	game->moves = 0;
}

static void	close_txr(t_game *game)
{
	if (game->black_bg)
		mlx_destroy_image(game->mlx, game->black_bg);
	if (game->txr.wall)
		mlx_destroy_image(game->mlx, game->txr.wall);
	if (game->txr.plr)
		mlx_destroy_image(game->mlx, game->txr.plr);
	if (game->txr.item)
		mlx_destroy_image(game->mlx, game->txr.item);
	if (game->txr.exit)
		mlx_destroy_image(game->mlx, game->txr.exit);
	if (game->txr.empty)
		mlx_destroy_image(game->mlx, game->txr.empty);
	if (game->txr.p_e)
		mlx_destroy_image(game->mlx, game->txr.p_e);
	if (game->txr.boss)
		mlx_destroy_image(game->mlx, game->txr.boss);
	if (game->bosses)
		free(game->bosses);
}

int	close_window(t_game *game)
{
	int	i;

	i = 0;
	close_txr(game);
	while (i < 3)
	{
		if (game->pframes[i])
			mlx_destroy_image(game->mlx, game->pframes[i]);
		if (game->iframes[i])
			mlx_destroy_image(game->mlx, game->iframes[i]);
		i++;
	}
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free_split(game->map);
	free(game->mlx);
	exit(EXIT_SUCCESS);
}

int	update_animation(t_game *game)
{
	game->frame_count++;
	if (game->frame_count >= game->frames_per_update)
	{
		game->anim_frame = (game->anim_frame + 1) % 3;
		game->frame_count = 0;
		move_boss(game);
		render_map(game->mlx, game->window, game->map, game);
	}
	display_moves(game);
	return (0);
}
