/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldantas <aldantas@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:50:03 by aldantas          #+#    #+#             */
/*   Updated: 2024/06/04 23:21:56 by aldantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/philo.h"

static int	check_is_alive(t_philo	*p, t_data *table)
{
	long long	now;

	pthread_mutex_lock(&table->mutex);
	now = get_time() - table->start_simulation;
	if (now - p->last_eat > table->time_die)
	{
		table->is_all_alive = false;
		pthread_mutex_unlock(&table->mutex);
		print_status(p, DEAD);
		return (-1);
	}
	pthread_mutex_unlock(&table->mutex);
	return (0);
}

static int	check_philo_status(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (check_is_alive(data->array_philos[i], data))
			return (-1);
		pthread_mutex_lock(&data->mutex);
		if (data->array_philos[i]->nbr_eats == data->eats_total
			&& !data->array_philos[i]->is_full)
		{
			data->count_full++;
			data->array_philos[i]->is_full = true;
		}
		pthread_mutex_unlock(&data->mutex);
		if (data->count_full == data->philo_nbr)
			return (1);
		i++;
	}
	return (0);
}

int	monitor_routine(t_data *data)
{
	while (42)
	{
		if (check_philo_status(data))
			return (1);
		usleep(1200);
	}
	return (0);
}

bool	check_all_alive(t_data *data)
{
	bool	ret;

	ret = true;
	pthread_mutex_lock(&data->mutex);
	if (data->is_all_alive == false)
		ret = false;
	pthread_mutex_unlock(&data->mutex);
	return (ret);
}
