/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:27:01 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/22 08:46:44 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/so_long.h"

int	main(int ac, char **av)
{
	t_game	game;
	char	*map;

	if (ac != 2)
		return (write(2, "Error: invalid number of arguments\n", 35));
	map = read_map(av[1]);
	if (!map)
		return (write(2, "Error: failed to read map\n", 26));
	if (check_map(map))
		return (free(map), 1);
	game.map = ft_split(map, '\n');
	free(map);
	init_window(&game);
	load_txr(game.mlx, &game);
	init_player_position(&game);
	init_collectibles(&game);
	mlx_hook(game.window, 2, 1L, handle_keypress, &game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}
