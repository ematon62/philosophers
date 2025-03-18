/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:21:14 by ematon            #+#    #+#             */
/*   Updated: 2025/03/18 09:21:28 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
- Destroys mutex int the forks array until end index
*/
int	destroy_forks(pthread_mutex_t *forks, int end)
{
	int	i;

	i = 0;
	while (i <= end)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	return (0);
}

pthread_mutex_t	*init_forks(int nb_philos)
{
	pthread_mutex_t		*forks;
	int					i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * nb_philos);
	if (!forks)
		return (ft_putstr_fd(MALLOC, STDERR_FILENO), NULL);
	while (i < nb_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
			return (ft_putstr_fd(MUTEX_INIT, STDERR_FILENO),
				destroy_forks(forks, i - 1),
				free(forks), NULL);
		i++;
	}
	return (forks);
}
