/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penascim <penascim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:08:36 by penascim          #+#    #+#             */
/*   Updated: 2024/06/04 17:22:14 by penascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_isdigit(int digit)
{
	return (digit >= '0' && digit <= '9');
}

static int	check_limits(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_atol(av[i++]) > 2147483647)
			return (1);
	}
	return (0);
}

static int	check_input_digit(char **args)
{
	int	i;
	int	k;

	i = 0;
	while (args[i])
	{
		k = 0;
		while (args[i][k])
		{
			if (!ft_isdigit(args[i][k]) && args[i][k] != '+')
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

int	check_args(char **av)
{
	if (av[0][0] == '0')
	{
		printf(RED"parse error: incorrect input"RESET);
		return (-1);
	}
	av++;
	if (check_input_digit(av) || check_limits(av))
	{
		printf(RED"parse error: incorrect input"RESET);
		return (-1);
	}
	return (0);
}

int	parse_data(t_data *data, char **av)
{
	data->philo_nbr = ft_atol(av[1]);
	data->time_die = ft_atol(av[2]);
	data->time_eat = ft_atol(av[3]) * 1000;
	data->time_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		data->eats_total = ft_atol(av[5]);
	else
		data->eats_total = -1;
	data->is_all_alive = true;
	data->count_full = 0;
	data->start_simulation = get_time();
	if (pthread_mutex_init(&data->mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&data->print_mtx, NULL))
		return (-1);
	data->array_forks = malloc(sizeof(t_fork) * data->philo_nbr);
	data->array_philos = malloc(sizeof(t_philo *) * data->philo_nbr);
	if (!data->array_forks || !data->array_forks)
		return (-1);
	return (0);
}
