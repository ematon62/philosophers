/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:05:08 by ematon            #+#    #+#             */
/*   Updated: 2025/03/16 19:20:39 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!(argc == 5 || argc == 6))
		return (ft_putstr_fd(NB_ARG_ERROR, STDERR_FILENO), EXIT_FAILURE);
	data = parse(argv);
	if (simulation(data))
		return (1);
	return (0);
}
