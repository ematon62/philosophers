/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:34:10 by ematon            #+#    #+#             */
/*   Updated: 2025/03/26 16:56:31 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		if (!check_if_continue(philo->state))
			break ;
		if (!check_if_continue(philo->state) || think(philo))
			break ;
		if (!check_if_continue(philo->state) || eat_n_sleep(philo))
			break ;
		if (!check_if_continue(philo->state))
			break ;
	}
	return (NULL);
}
