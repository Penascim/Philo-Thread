/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldantas <aldantas@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:24:14 by aldantas          #+#    #+#             */
/*   Updated: 2024/06/04 23:22:23 by aldantas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	run_threads(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (check_args(av) || parse_data(&data, av))
			return (-1);
		init_data(&data);
		monitor_routine(&data);
		if (run_threads(&data))
			return (-1);
		free_all(&data);
	}
	else
		print_error(ac);
	return (0);
}

static int	run_threads(t_data *data)
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
