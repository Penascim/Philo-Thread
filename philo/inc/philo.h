/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: penascim <penascim@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 17:02:41 by penascim          #+#    #+#             */
/*   Updated: 2024/06/04 17:59:45 by penascim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mtx;
typedef pthread_t		t_thread;
typedef struct s_data	t_data;

/*	colors		*/
# define RESET  "\033[0m"
# define RED	"\033[1;31m"
# define G      "\033[1;32m"
# define Y      "\033[1;33m"
# define B      "\033[1;34m"
# define P		"\033[1;35m"
# define C      "\033[1;36m"
# define W      "\033[1;37m"

typedef enum e_status
{
	SLEEP,
	EAT,
	FORK,
	THINK,
	DEAD
}	t_status;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

/* each philosopher */
typedef struct s_philo
{
	int			id;
	bool		is_full;
	int			nbr_eats;
	int			last_eat;
	t_thread	thread;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_data		*table;
}	t_philo;

/* datas */
typedef struct s_data
{
	int		philo_nbr;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		eats_total;
	int		count_full;
	long	start_simulation;
	bool	is_all_alive;
	t_mtx	mutex;
	t_mtx	print_mtx;
	t_fork	*array_forks;
	t_philo	**array_philos;
}	t_data;

int			parse_data(t_data *data, char **av);
int			init_data(t_data *data);
void		*routine(void *arg);
int			monitor_routine(t_data *arg);
long		ft_atol(const char *nptr);
void		free_all(t_data *data);
long long	get_time(void);
void		print_status(t_philo *p, t_status flag);
bool		check_all_alive(t_data *data);
int			check_args(char **av);
void		print_error(int ac);
void		smart_sleep(t_data *t, long long time);

#endif
