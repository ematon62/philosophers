/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:45:02 by ematon            #+#    #+#             */
/*   Updated: 2025/03/18 09:49:34 by ematon           ###   ########.fr       */
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

time_t	get_current_time(t_philo *philo)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - philo->data->start.tv_sec) * 1000);
}
