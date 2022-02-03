/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:39:15 by soumanso          #+#    #+#             */
/*   Updated: 2022/01/07 15:39:15 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef pthread_mutex_t	t_mutex;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef int				t_s32;
typedef unsigned int	t_u32;
typedef long			t_s64;
typedef unsigned long	t_u64;
typedef char			*t_str;
typedef const char		*t_cstr;

typedef struct s_data
{
	t_u64			start_time;
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_to_satiated;
	struct s_philo	*philos;
	t_bool			dead;
	int				satiated_philos;
	t_mutex			*fork_mutexes;
	t_mutex			print_mutex;
	t_mutex			death_mutex;
	t_mutex			satiated_mutex;
}	t_data;

typedef struct s_philo
{
	t_data		*data;
	int			id;
	pthread_t	thread_id;
	t_u64		last_meal_time;
	int			meal_count;
}	t_philo;

typedef enum e_msg
{
	MSG_FORK_TAKEN,
	MSG_EATING,
	MSG_SLEEPING,
	MSG_THINKING,
	MSG_DIED
}	t_msg;

void	terminate(t_data *data);
t_u64	get_time(t_data *data);
void	print(t_philo *philo, t_u64 time, t_msg msg);
void	*thread_entry(void *data);
void	watch_philos(t_data *data);

#endif
