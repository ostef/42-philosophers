/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:30:07 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/08 18:51:37 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	should_stop(t_philo *philo)
{
	t_bool	val;

	pthread_mutex_lock (&philo->data->death_mutex);
	val = philo->data->dead;
	pthread_mutex_unlock (&philo->data->death_mutex);
	if (philo->data->eat_to_satiated >= 0)
	{
		pthread_mutex_lock (&philo->data->satiated_mutex);
		val |= philo->data->satiated_philos == philo->data->philo_count;
		pthread_mutex_unlock (&philo->data->satiated_mutex);
	}
	return (val);
}

static t_bool	wait_until_stop(t_philo *philo)
{
	while (!should_stop (philo))
	{
	}
	return (TRUE);
}

static void	eat(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (left + 1) % philo->data->philo_count;
	pthread_mutex_lock (&philo->data->fork_mutexes[left]);
	print (philo, MSG_FORK_TAKEN);
	if (left == right && wait_until_stop (philo))
		return ;
	pthread_mutex_lock (&philo->data->fork_mutexes[right]);
	print (philo, MSG_FORK_TAKEN);
	pthread_mutex_lock (&philo->meal_mutex);
	philo->meal_count += 1;
	philo->last_meal_time = get_time (philo->data);
	pthread_mutex_unlock (&philo->meal_mutex);
	print (philo, MSG_EATING);
	sleep_ms (philo->data, philo->data->time_to_eat);
	pthread_mutex_unlock (&philo->data->fork_mutexes[left]);
	pthread_mutex_unlock (&philo->data->fork_mutexes[right]);
	if (philo->meal_count == philo->data->eat_to_satiated)
	{
		pthread_mutex_lock (&philo->data->satiated_mutex);
		philo->data->satiated_philos += 1;
		pthread_mutex_unlock (&philo->data->satiated_mutex);
	}
}

void	*philo_thread(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (TRUE)
	{
		if (philo->id % 2 == 0)
		{
			print (philo, MSG_SLEEPING);
			sleep_ms (philo->data, philo->data->time_to_sleep);
			if (should_stop (philo))
				break ;
		}
		eat (philo);
		if (should_stop (philo))
			break ;
		if (philo->id % 2 != 0)
		{
			print (philo, MSG_SLEEPING);
			sleep_ms (philo->data, philo->data->time_to_sleep);
			if (should_stop (philo))
				break ;
		}
		print (philo, MSG_THINKING);
	}
	return (NULL);
}
