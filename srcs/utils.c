/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:45:02 by ematon            #+#    #+#             */
/*   Updated: 2025/03/19 13:52:18 by ematon           ###   ########.fr       */
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

time_t	get_time_since_start(t_data *data)
{
	struct timeval	current;
	struct timeval	start;
	time_t			time;

	start = data->start;
	gettimeofday(&current, NULL);
	time = (((current.tv_sec - start.tv_sec) * 1000
				+ (current.tv_usec - start.tv_usec) / 1000));
	return (time);
}

time_t	get_time_since_last_meal(t_philo *philo)
{
	return (get_time_since_start(philo->data) - philo->time_since_last);
}
