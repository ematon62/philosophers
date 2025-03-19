/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:20:24 by ematon            #+#    #+#             */
/*   Updated: 2025/03/19 15:58:15 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_threads(t_data *data, t_state *simstate,
	pthread_t *philosophers)
{
	int				i;
	t_philo			**philo_data;
	pthread_t		monitor;

	i = 0;
	philo_data = init_philo(data, simstate);
	if (!philo_data)
		return (ft_putstr_fd(MALLOC, STDERR_FILENO), 1);
	simstate->philos = philo_data;
	pthread_create(&monitor, NULL, &monitor_routine, simstate);
	while (i < data->nb_philo)
	{
		pthread_create(&philosophers[i], NULL, &routine, philo_data[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (ft_free_toodee((void **)philo_data), 0);
}

int	simulation(t_data data)
{
	t_state			state;
	pthread_t		*philosophers;
	int				exit_status;

	if (gettimeofday(&data.start, NULL))
		return (1);
	state = init_simulation(data);
	if (!state.initialized)
		return (1);
	state.data = &data;
	state.current = 0;
	philosophers = malloc(sizeof(pthread_t) * data.nb_philo);
	if (!philosophers)
		return (ft_putstr_fd(MALLOC, STDERR_FILENO),
			destroy_simulation(&state, data), 1);
	exit_status = start_threads(&data, &state, philosophers);
	destroy_simulation(&state, data);
	free(philosophers);
	return (exit_status);
}
