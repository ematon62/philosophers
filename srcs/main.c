/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:05:08 by ematon            #+#    #+#             */
/*   Updated: 2025/03/17 14:58:39 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!(argc == 5 || argc == 6))
		return (ft_putstr_fd(NUMBER_OF_ARGS, STDERR_FILENO), EXIT_FAILURE);
	data = parse(argv);
	if (!data.initialized)
		return (EXIT_FAILURE);
	if (simulation(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
