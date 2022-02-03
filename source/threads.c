/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:30:07 by soumanso          #+#    #+#             */
/*   Updated: 2022/01/07 16:30:07 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (left + 1) % philo->data->philo_count;
	pthread_mutex_lock (&philo->data->fork_mutexes[left]);
	print (philo, get_time (philo->data), MSG_FORK_TAKEN);
	pthread_mutex_lock (&philo->data->fork_mutexes[right]);
	print (philo, get_time (philo->data), MSG_FORK_TAKEN);
	philo->meal_count += 1;
	philo->last_meal_time = get_time (philo->data);
	print (philo, philo->last_meal_time, MSG_EATING);
	usleep (philo->data->time_to_eat * 1000);
	pthread_mutex_unlock (&philo->data->fork_mutexes[left]);
	pthread_mutex_unlock (&philo->data->fork_mutexes[right]);
}

void	*thread_entry(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (TRUE)
	{
		if (philo->id % 2 == 0)
		{
			print (philo, get_time (philo->data), MSG_SLEEPING);
			usleep (philo->data->time_to_sleep * 1000);
		}
		eat (philo);
		if (philo->meal_count == philo->data->eat_to_satiated)
		{
			pthread_mutex_lock (&philo->data->satiated_mutex);
			philo->data->satiated_philos += 1;
			pthread_mutex_unlock (&philo->data->satiated_mutex);
			break ;
		}
		if (philo->id % 2 != 0)
		{
			print (philo, get_time (philo->data), MSG_SLEEPING);
			usleep (philo->data->time_to_sleep * 1000);
		}
	}
	return (NULL);
}
