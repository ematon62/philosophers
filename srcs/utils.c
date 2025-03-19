/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:45:02 by ematon            #+#    #+#             */
/*   Updated: 2025/03/19 04:45:53 by ematon           ###   ########.fr       */
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
	time_t			time;

	gettimeofday(&current, NULL);
	time = ((current.tv_usec - philo->data->start.tv_usec));
	return (time);
}

time_t	get_time_since_last_meal(t_philo *philo)
{
	struct timeval	current;
	time_t			time;

	gettimeofday(&current, NULL);
	time = ((current.tv_usec - philo->time_since_last) / 1000);
	return (time);
}
