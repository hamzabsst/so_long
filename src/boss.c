/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:47:11 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/22 19:48:43 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	initialize_bosses(t_game *game)
{
	int	i;
	int	j;
	int	boss_index;

	boss_index = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'B')
			{
				game->bosses[boss_index].x = j;
				game->bosses[boss_index].y = i;
				game->bosses[boss_index].direction = 1;
				game->bosses[boss_index].previous_tile = '0';
				boss_index++;
			}
			j++;
		}
		i++;
	}
}

void	init_bosses(t_game *game)
{
	int	i;
	int	j;

	game->boss_count = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'B')
				game->boss_count++;
			j++;
		}
		i++;
	}
	game->bosses = malloc(sizeof(t_boss) * game->boss_count);
	if (!game->bosses)
		return ;
	initialize_bosses(game);
}

static int	move_boss_direction(t_game *game, int i)
{
	int		new_x;

	if (game->bosses[i].direction == 1)
		new_x = game->bosses[i].x + 1;
	else
		new_x = game->bosses[i].x - 1;
	return (new_x);
}

static void	update_boss_on_map(t_game *game, int i, int new_x, char next_tile)
{
	if (next_tile == '1')
	{
		game->bosses[i].direction *= -1;
		return ;
	}
	if (next_tile == 'P')
	{
		ft_printf("Game Over! A boss defeated you!\n");
		close_window(game);
		return ;
	}
	game->map[game->bosses[i].y][game->bosses[i].x]
		= game->bosses[i].previous_tile;
	if (next_tile == 'C')
		game->bosses[i].previous_tile = 'C';
	else if (next_tile == 'E')
		game->bosses[i].previous_tile = 'E';
	else
		game->bosses[i].previous_tile = '0';
	game->map[game->bosses[i].y][new_x] = 'B';
	game->bosses[i].x = new_x;
}

void	move_boss(t_game *game)
{
	int		i;
	int		new_x;
	char	next_tile;

	i = 0;
	while (i < game->boss_count)
	{
		new_x = move_boss_direction(game, i);
		next_tile = game->map[game->bosses[i].y][new_x];
		update_boss_on_map(game, i, new_x, next_tile);
		i++;
	}
}
