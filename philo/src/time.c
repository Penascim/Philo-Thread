/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penascim <penascim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 02:40:30 by penascim          #+#    #+#             */
/*   Updated: 2024/06/04 17:24:36 by penascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	time_diff(long long past, long long pres)
{
	return ((pres - past) * 1000);
}

void	smart_sleep(t_data *t, long long time)
{
	long long	past;

	past = get_time() - t->start_simulation;
	while (check_all_alive(t))
	{
		if (time_diff(past, get_time() - t->start_simulation) >= time)
			break ;
		usleep(42);
	}
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
