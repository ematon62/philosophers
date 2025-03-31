/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:21:14 by ematon            #+#    #+#             */
/*   Updated: 2025/03/31 19:43:40 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
- Destroys mutex int the forks array until end index
*/
static int	destroy_mutexes(pthread_mutex_t *forks, int end)
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

static pthread_mutex_t	*init_mutexes(int nb_philos)
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
				destroy_mutexes(forks, i - 1),
				free(forks), NULL);
		i++;
	}
	return (forks);
}

int	destroy_simulation(t_state *state, t_data data)
{
	destroy_mutexes(state->forks_ptr, data.nb_philo - 1);
	destroy_mutexes(state->last_time_eaten, data.nb_philo - 1);
	pthread_mutex_destroy(&state->write_perm);
	pthread_mutex_destroy(&state->end_mutex);
	return (0);
}

t_state	init_simulation(t_data data)
{
	t_state	state;

	state.finished = true;
	state.initialized = false;
	state.forks_ptr = init_mutexes(data.nb_philo);
	if (!state.forks_ptr)
		return (state);
	state.last_time_eaten = init_mutexes(data.nb_philo);
	if (!state.last_time_eaten)
		return (destroy_mutexes(state.forks_ptr, data.nb_philo - 1),
			state);
	if (pthread_mutex_init(&state.write_perm, NULL))
		return (ft_putstr_fd(MUTEX_INIT, 2),
			destroy_mutexes(state.forks_ptr, data.nb_philo - 1),
			destroy_mutexes(state.last_time_eaten, data.nb_philo - 1), state);
	if (pthread_mutex_init(&state.end_mutex, NULL))
		return (ft_putstr_fd(MUTEX_INIT, 2),
			pthread_mutex_destroy(&state.write_perm),
			destroy_mutexes(state.forks_ptr, data.nb_philo - 1),
			destroy_mutexes(state.last_time_eaten, data.nb_philo - 1), state);
	state.initialized = true;
	return (state);
}
