/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:34:10 by ematon            #+#    #+#             */
/*   Updated: 2025/03/31 19:43:42 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	case_one_philo(t_philo *philo)
{
	event(TAKE, philo->state, 0);
	usleep(philo->data->time_die * 1000);
	return (0);
}

void	*routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	if (philo->data->nb_philo == 1)
		return (case_one_philo(philo), NULL);
	if (philo->id % 2)
		usleep(500);
	while (1)
	{
		if (think (philo) || eat(philo) || sleepers(philo))
			break ;
	}
	return (NULL);
}
