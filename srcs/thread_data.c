/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:23:25 by ematon            #+#    #+#             */
/*   Updated: 2025/03/18 16:15:01 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*get_thread_data(int i, t_data *data, t_sim_state *simstate)
{
	t_philo	*philo;
	int		left_index;
	int		right_index;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i;
	philo->data = data;
	left_index = left(i);
	right_index = right(i, data->nb_philo);
	if (left_index < right_index)
	{
		philo->max_index = right_index;
		philo->min_index = left_index;
	}
	else
	{
		philo->max_index = left_index;
		philo->min_index = right_index;
	}
	philo->sim_state = simstate;
	return (philo);
}

t_philo	**init_philo(t_data *data, t_sim_state *simstate)
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
