/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbousset < hbousset@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:27:01 by hbousset          #+#    #+#             */
/*   Updated: 2025/01/20 07:59:14 by hbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/so_long.h"

int	main(int ac, char **av)
{
	char	*map;
	void	*mlx;
	void	*window;

	if (ac != 2)
		return (write(2, "Error: invalid number of arguments\n", 35));
	map = read_map("maps/test.ber");
	if (!map)
	{
		free(map);
		return(write(2, "Error: failed to read map\n", 26));
	}
	if(check_map(map) == 1)
	{
		free(map);
		exit(EXIT_FAILURE);
	}
	mlx = mlx_init();
	if (!mlx)
		return (1);
	window = mlx_new_window(mlx, 800, 600, "so_long");
	if (!window)
		return (1);
	char **map_2d = ft_split(map, '\n');
	init_map(mlx, window, map_2d);
	mlx_loop(mlx);
	free_lines(map_2d);
	if(!av)
		return (1);
}
