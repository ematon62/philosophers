/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:33:45 by ematon            #+#    #+#             */
/*   Updated: 2025/03/19 18:37:31 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_if_continue(t_state *state)
{
	bool	do_i_continue;

	pthread_mutex_lock(&state->end_mutex);
	do_i_continue = state->finished;
	pthread_mutex_unlock(&state->end_mutex);
	return (do_i_continue);
}

bool	sleep_paralysis(long int time, t_state *state)
{
	int	n;

	n = 0;
	while (time > 0)
	{
		if (!check_if_continue(state))
			return (true);
		time -= 20;
		usleep(20000);
	}
	return (false);
}

int	eat_n_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->state->last_time_eaten[philo->id]);
	philo->nb_times_eaten += 1;
	pthread_mutex_unlock(&philo->state->last_time_eaten[philo->id]);
	pthread_mutex_lock(&philo->state->write_perm);
	philo->time_since_last = philo->state->current;
	pthread_mutex_unlock(&philo->state->write_perm);
	event(EAT, philo->state, philo->id);
	if (sleep_paralysis(philo->data->time_eat, philo->state))
	{
		pthread_mutex_unlock(&philo->state->forks_ptr[philo->max_index]);
		pthread_mutex_unlock(&philo->state->forks_ptr[philo->min_index]);
		return (1);
	}
	pthread_mutex_unlock(&philo->state->forks_ptr[philo->max_index]);
	pthread_mutex_unlock(&philo->state->forks_ptr[philo->min_index]);
	if (!check_if_continue(philo->state))
		return (1);
	event(SLEEP, philo->state, philo->id);
	if (sleep_paralysis(philo->data->time_sleep, philo->state))
		return (1);
	return (0);
}

static int	case_one_philo(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->state->forks_ptr[philo->min_index]);
		return (usleep(philo->data->time_die * 1000), 1);
	}
	if (!check_if_continue(philo->state))
	{
		pthread_mutex_unlock(&philo->state->forks_ptr[philo->min_index]);
		return (1);
	}
	return (0);
}

int	think(t_philo *philo)
{
	if (!check_if_continue(philo->state))
		return (1);
	event(THINK, philo->state, philo->id);
	pthread_mutex_lock(&philo->state->forks_ptr[philo->min_index]);
	if (!check_if_continue(philo->state))
	{
		pthread_mutex_unlock(&philo->state->forks_ptr[philo->min_index]);
		return (1);
	}
	event(TAKE, philo->state, philo->id);
	if (case_one_philo(philo))
		return (1);
	pthread_mutex_lock(&philo->state->forks_ptr[philo->max_index]);
	if (!check_if_continue(philo->state))
	{
		pthread_mutex_unlock(&philo->state->forks_ptr[philo->max_index]);
		pthread_mutex_unlock(&philo->state->forks_ptr[philo->min_index]);
		return (1);
	}
	event(TAKE, philo->state, philo->id);
	return (0);
}
