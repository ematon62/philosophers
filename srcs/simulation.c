/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:20:24 by ematon            #+#    #+#             */
/*   Updated: 2025/03/18 15:23:53 by ematon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
Algorithme possible:
- Numéroter les fourchettes de 1 à N, du 1er philosophe jusqu'au N-ième
- Lancer les threads (philosophes) du 1er jusqu'au dernier, dans cet ordre
- Pour chaque philosophe:
	1. Penser jusqu'à ce que la plus petite fourchette soit dispo
	2. Penser jusqu'à ce que la plus grande fourchette soit dispo
	3. Manger pendant [time_to_eat] ms
	4. Dormir pendant [time_to_sleep] ms
	5. Reposer les 2 fourchettes l'une après l'autre
	6. Revenir à l'étape 1
- Si pendant les 2 étapes de penser et dormir, le temps passé depuis la dernière
bouffe est atteint, le philosophe meurt
*/

/*
Choses à gérer en plus:
- Créer des variables d'état qui arretent tous les threads
dés qu'un philosophe meurt
- Comment tuer un philosophe au moment exact ou il est censé mourrir?
*/

int	start_threads(t_data *data, t_sim_state *simstate,
	pthread_t *philosophers)
{
	int				i;
	t_philo			**philo_data;

	i = 0;
	philo_data = init_philo(data, simstate);
	if (!philo_data)
		return (ft_putstr_fd(MALLOC, STDERR_FILENO), 1);
	while (i < data->nb_philo)
	{
		pthread_create(&philosophers[i], NULL, &routine, philo_data[i]);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
	return (ft_free_toodee((void **)philo_data), 0);
}

int	simulation(t_data data)
{
	t_sim_state			sim_state;
	pthread_t			*philosophers;
	int					exit_status;

	if (gettimeofday(&data.start, NULL))
		return (1);
	sim_state = init_simulation(data);
	if (!sim_state.initialized)
		return (1);
	philosophers = malloc(sizeof(pthread_t) * data.nb_philo);
	if (!philosophers)
		return (ft_putstr_fd(MALLOC, STDERR_FILENO),
			destroy_simulation(sim_state, data), 1);
	exit_status = start_threads(&data, &sim_state, philosophers);
	destroy_simulation(sim_state, data);
	free(philosophers);
	return (exit_status);
}
