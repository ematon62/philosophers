/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:17:33 by ematon            #+#    #+#             */
/*   Updated: 2025/04/04 13:52:27 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	have_all_eaten_enough(t_state *state)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (i < state->data->nb_philo)
	{
		pthread_mutex_lock(&state->last_time_eaten[i]);
		if (state->philos[i]->nb_times_eaten >= state->data->nb_must_eat)
			n++;
		pthread_mutex_unlock(&state->last_time_eaten[i]);
		i++;
	}
	return (n == state->data->nb_philo);
}

static bool	are_still_alive(t_state *state)
{
	int		i;
	time_t	time_since_last_meal;

	i = 0;
	while (i < state->data->nb_philo)
	{
		pthread_mutex_lock(&state->write_perm);
		time_since_last_meal = get_time_since_last_meal(state->philos[i]);
		pthread_mutex_unlock(&state->write_perm);
		if (time_since_last_meal > state->data->time_die)
			return (event(DIE, state, i), false);
		i++;
	}
	return (true);
}

int	event(char *s, t_state *state, int id)
{
	pthread_mutex_lock(&state->write_perm);
	printf(s, state->current, id + 1);
	pthread_mutex_unlock(&state->write_perm);
	return (0);
}

void	*monitor_routine(void *input)
{
	t_state		*state;

	state = (t_state *)input;
	while (1)
	{
		pthread_mutex_lock(&state->write_perm);
		state->current = get_time_since_start(state->data);
		pthread_mutex_unlock(&state->write_perm);
		if (have_all_eaten_enough(state)
			|| !are_still_alive(state))
		{
			pthread_mutex_lock(&state->end_mutex);
			state->finished = false;
			pthread_mutex_unlock(&state->end_mutex);
			break ;
		}
	}
	return (NULL);
}
