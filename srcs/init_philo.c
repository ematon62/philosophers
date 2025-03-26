/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:23:25 by ematon            #+#    #+#             */
/*   Updated: 2025/03/26 19:31:22 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*get_thread_data(int i, t_data *data, t_state *simstate)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i;
	philo->data = data;
	if (philo->id % 2)
	{
		philo->left_index = right(i, philo->data->nb_philo);
		philo->right_index = left(i);
	}
	else
	{
		philo->left_index = left(i);
		philo->right_index = right(i, philo->data->nb_philo);
	}
	philo->state = simstate;
	philo->time_since_last = 0;
	philo->nb_times_eaten = 0;
	return (philo);
}

t_philo	**init_philo(t_data *data, t_state *simstate)
{
	t_philo	**philo_data;
	int		i;

	philo_data = malloc(sizeof(t_philo *) * (data->nb_philo + 1));
	if (!philo_data)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		philo_data[i] = get_thread_data(i, data, simstate);
		if (!philo_data[i])
			return (ft_free_toodee((void **)philo_data), NULL);
		i++;
	}
	philo_data[i] = NULL;
	return (philo_data);
}
