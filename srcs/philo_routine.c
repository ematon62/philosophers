/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:34:10 by ematon            #+#    #+#             */
/*   Updated: 2025/03/18 16:16:51 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	*monitoring(void *input)
// {
// 	while (1)
// 	{
// 	}
// }

void	*routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	while (1)
	{
		event(THINK, philo);
		pthread_mutex_lock(&philo->sim_state->forks_ptr[philo->min_index]);
		event(TAKE, philo);
		pthread_mutex_lock(&philo->sim_state->forks_ptr[philo->max_index]);
		event(TAKE, philo);
		pthread_mutex_lock(&philo->sim_state->last_time_eaten[philo->id]);
		philo->time_since_last += 1;
		pthread_mutex_unlock(&philo->sim_state->last_time_eaten[philo->id]);
		event(EAT, philo);
		usleep(philo->data->time_eat * 1000);
		pthread_mutex_unlock(&philo->sim_state->forks_ptr[philo->max_index]);
		pthread_mutex_unlock(&philo->sim_state->forks_ptr[philo->min_index]);
		event(SLEEP, philo);
		usleep(philo->data->time_sleep * 1000);
	}
}
