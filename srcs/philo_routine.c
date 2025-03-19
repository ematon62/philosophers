/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:34:10 by ematon            #+#    #+#             */
/*   Updated: 2025/03/19 04:25:33 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_if_continue(t_state *state)
{
	bool	do_i_continue;

	pthread_mutex_lock(&state->satiat);
	do_i_continue = state->all_alive;
	pthread_mutex_unlock(&state->satiat);
	return (do_i_continue);
}

bool	sleep_paralysis(long int time, t_state *state)
{
	int	n;

	n = 0;
	if (!check_if_continue(state))
		return (true);
	while (n < time)
	{
		if (!check_if_continue(state))
			return (true);
		usleep(100);
		n += 100;
	}
	if (!check_if_continue(state))
		return (true);
	return (false);
}

int	event(char *s, t_philo *philo)
{
	pthread_mutex_lock(&philo->state->write_perm);
	printf(s, get_time_since_start(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->state->write_perm);
	return (true);
}


void	*routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	while (1)
	{
		event(THINK, philo);
		pthread_mutex_lock(&philo->state->forks_ptr[philo->min_index]);
		event(TAKE, philo);
		pthread_mutex_lock(&philo->state->forks_ptr[philo->max_index]);
		event(TAKE, philo);
		pthread_mutex_lock(&philo->state->last_time_eaten[philo->id]);
		philo->nb_times_eaten += 1;
		philo->time_since_last = get_time_since_last_meal(philo);
		pthread_mutex_unlock(&philo->state->last_time_eaten[philo->id]);
		event(EAT, philo);
		if (sleep_paralysis(philo->data->time_eat * 1000, philo->state))
		{
			pthread_mutex_unlock(&philo->state->forks_ptr[philo->max_index]);
			pthread_mutex_unlock(&philo->state->forks_ptr[philo->min_index]);
			break ;
		}
		pthread_mutex_unlock(&philo->state->forks_ptr[philo->max_index]);
		pthread_mutex_unlock(&philo->state->forks_ptr[philo->min_index]);
		event(SLEEP, philo);
		if (sleep_paralysis(philo->data->time_sleep * 1000, philo->state))
			break ;
	}
	event(DIE, philo);
	return (NULL);
}
