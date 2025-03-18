/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:45:02 by ematon            #+#    #+#             */
/*   Updated: 2025/03/18 16:16:02 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	left(int index)
{
	return (index);
}

int	right(int index, int nb_philo)
{
	return ((index + nb_philo - 1) % (nb_philo));
}

time_t	get_time_since_start(t_philo *philo)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - philo->data->start.tv_sec) * 1000);
}

time_t	get_time_since_last_meal(t_philo *philo)
{
	struct timeval	current;
	time_t			time;

	gettimeofday(&current, NULL);
	pthread_mutex_lock(&philo->sim_state->last_time_eaten[philo->id]);
	time = ((current.tv_sec - philo->time_since_last) * 1000);
	pthread_mutex_unlock(&philo->sim_state->last_time_eaten[philo->id]);
	return (time);
}

void	event(char *s, t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_state->write_perm);
	printf(s, get_time_since_start(philo), philo->id + 1);
	pthread_mutex_unlock(&philo->sim_state->write_perm);
}
