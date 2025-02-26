/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldantas <aldantas@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:00:52 by aldantas          #+#    #+#             */
/*   Updated: 2024/06/04 23:21:44 by aldantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	philos_inits(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = data->philo_nbr;
	while (--i >= 0)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (-1);
		philo->id = i;
		philo->is_full = false;
		philo->nbr_eats = 0;
		philo->last_eat = 0;
		philo->thread = 0;
		philo->left_fork = &data->array_forks[i];
		philo->right_fork = &data->array_forks[((i + 1) % data->philo_nbr)];
		philo->table = data;
		data->array_philos[i] = philo;
	}
	return (0);
}

static int	init_forks(t_data *data)
{
	int		i;
	t_fork	*array_forks;

	array_forks = data->array_forks;
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&array_forks[i].fork, NULL))
			return (-1);
		array_forks[i].fork_id = i + 1;
		i++;
	}
	data->array_forks = array_forks;
	return (0);
}

static int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_simulation = get_time();
	while (++i < data->philo_nbr)
	{
		if (pthread_create(&data->array_philos[i]->thread,
				NULL, routine, data->array_philos[i]))
			return (1);
	}
	return (0);
}

int	run_threads(t_data *data)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < data->philo_nbr)
	{
		ret = pthread_join(data->array_philos[i]->thread, NULL);
		if (ret)
			return (ret);
	}
	return (ret);
}

int	init_data(t_data *data)
{
	if (philos_inits(data))
		return (-1);
	if (init_forks(data))
		return (-1);
	if (init_threads(data))
		return (-1);
	return (0);
}
