/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:20:24 by ematon            #+#    #+#             */
/*   Updated: 2025/03/19 04:48:26 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	have_all_eaten_enough(bool *array, t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < data->nb_philo)
	{
		n += array[i];
		i++;
	}
	return (n == data->nb_philo);
}

bool	are_still_alive(t_state *state)
{
	int		i;
	time_t	time;

	i = 0;
	while (i < state->data->nb_philo)
	{
		pthread_mutex_lock(&state->last_time_eaten[i]);
		time = get_time_since_last_meal(state->philos[i]);
		pthread_mutex_unlock(&state->last_time_eaten[i]);
		if (time >= state->data->time_die)
			return (false);
		i++;
	}
	return (true);
}

void	*monitor_routine(void *input)
{
	t_state		*state;

	state = (t_state *)input;
	while (1)
	{
		if (have_all_eaten_enough(state->satiated_philos, state->data)
			|| !are_still_alive(state))
		{
			pthread_mutex_lock(&state->satiat);
			state->all_alive = false;
			pthread_mutex_unlock(&state->satiat);
			break ;
		}
	}
	return (NULL);
}

int	start_threads(t_data *data, t_state *simstate,
	pthread_t *philosophers)
{
	int				i;
	t_philo			**philo_data;
	pthread_t		monitor;

	i = 0;
	(void)monitor;
	(void)philosophers;
	philo_data = init_philo(data, simstate);
	if (!philo_data)
		return (ft_putstr_fd(MALLOC, STDERR_FILENO), 1);
	usleep(1000000);
	printf("%ld\n", data->start.tv_usec);
	// simstate->philos = philo_data;
	// pthread_create(&monitor, NULL, &monitor_routine, simstate);
	// while (i < data->nb_philo)
	// {
	// 	pthread_create(&philosophers[i], NULL, &routine, philo_data[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i < data->nb_philo)
	// {
	// 	pthread_join(philosophers[i], NULL);
	// 	i++;
	// }
	// pthread_join(monitor, NULL);
	return (ft_free_toodee((void **)philo_data), 0);
}

int	simulation(t_data data)
{
	t_state			state;
	pthread_t			*philosophers;
	int					exit_status;

	if (gettimeofday(&data.start, NULL))
		return (1);
	state = init_simulation(data);
	if (!state.initialized)
		return (1);
	philosophers = malloc(sizeof(pthread_t) * data.nb_philo);
	if (!philosophers)
		return (ft_putstr_fd(MALLOC, STDERR_FILENO),
			destroy_simulation(state, data), 1);
	exit_status = start_threads(&data, &state, philosophers);
	destroy_simulation(state, data);
	free(philosophers);
	return (exit_status);
}
