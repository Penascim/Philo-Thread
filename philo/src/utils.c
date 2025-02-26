/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldantas <aldantas@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:10:18 by aldantas          #+#    #+#             */
/*   Updated: 2024/06/04 23:23:01 by aldantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_philo *p, t_status flag)
{
	long long	now;
	t_data		*table;

	table = p->table;
	pthread_mutex_lock(&table->print_mtx);
	now = get_time() - table->start_simulation;
	if (flag == DEAD)
		printf(RED"time: %lld, id: %d died\n"RESET, now, p->id + 1);
	pthread_mutex_lock(&table->mutex);
	if (!table->is_all_alive)
	{
		pthread_mutex_unlock(&table->mutex);
		pthread_mutex_unlock(&table->print_mtx);
		return ;
	}
	pthread_mutex_unlock(&table->mutex);
	if (flag == SLEEP)
		printf (Y"time: %lld, id: %d is sleeping\n"RESET, now, p->id + 1);
	if (flag == THINK)
		printf (C"time: %lld, id: %d is thinking\n"RESET, now, p->id + 1);
	if (flag == EAT)
		printf (G"time: %lld, id: %d is eating\n"RESET, now, p->id + 1);
	if (flag == FORK)
		printf (B"time: %lld, id: %d takes a fork\n"RESET, now, p->id + 1);
	pthread_mutex_unlock(&table->print_mtx);
}

void	free_all(t_data *data)
{
	int	i;

	i = data->philo_nbr;
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->print_mtx);
	while (--i >= 0)
	{
		pthread_mutex_destroy(&data->array_forks[i].fork);
		free(data->array_philos[i]);
	}
	free(data->array_forks);
	free(data->array_philos);
}

long	ft_atol(const char *nptr)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while ((*nptr == 32) || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res *= 10;
		res += *nptr++ - '0';
	}
	return ((long)(res * sign));
}

void	print_error(int ac)
{
	if (ac < 5)
		printf(RED"too few arguments\n"RESET);
	else if (ac > 6)
		printf(RED"too more arguments\n"RESET);
}
