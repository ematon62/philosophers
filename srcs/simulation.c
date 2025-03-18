/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ematon <ematon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:20:24 by ematon            #+#    #+#             */
/*   Updated: 2025/03/18 11:06:12 by ematon           ###   ########.fr       */
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

void	*routine(void *input)
{
	t_philo	*philo;

	philo = (t_philo *)input;
	while (1)
	{
		printf(THINK, get_current_time(philo), philo->id + 1);
		pthread_mutex_lock(&philo->forks_ptr[philo->min_index]);
		printf(TAKE, get_current_time(philo), philo->id + 1);
		pthread_mutex_lock(&philo->forks_ptr[philo->max_index]);
		printf(TAKE, get_current_time(philo), philo->id + 1);
		printf(EAT, get_current_time(philo), philo->id + 1);
		usleep(EAT_DURATION);
		pthread_mutex_unlock(&philo->forks_ptr[philo->max_index]);
		pthread_mutex_unlock(&philo->forks_ptr[philo->min_index]);
		printf(SLEEP, get_current_time(philo), philo->id + 1);
		usleep(SLEEP_DURATION);
	}
}

int	start_threads(t_data *data, pthread_mutex_t *forks,
	pthread_t *philosophers)
{
	int			i;
	t_philo		**philo_data;

	i = 0;
	philo_data = init_philo(data, &forks);
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
	pthread_mutex_t		*forks;
	pthread_t			*philosophers;
	int					exit_status;

	if (gettimeofday(&data.start, NULL))
		return (1);
	forks = init_forks(data.nb_philo);
	if (!forks)
		return (1);
	philosophers = malloc(sizeof(pthread_t) * data.nb_philo);
	if (!philosophers)
		return (ft_putstr_fd(MALLOC, STDERR_FILENO), 1);
	exit_status = start_threads(&data, forks, philosophers);
	destroy_forks(forks, data.nb_philo - 1);
	free(philosophers);
	return (exit_status);
}
