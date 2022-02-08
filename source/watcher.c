/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:28:07 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/08 18:07:58 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	is_dead(t_philo *philo)
{
	t_u64	time;
	t_u64	last_meal_time;

	pthread_mutex_lock (&philo->meal_mutex);
	last_meal_time = philo->last_meal_time;
	pthread_mutex_unlock (&philo->meal_mutex);
	time = get_time (philo->data);
	if ((int)(time - last_meal_time) > philo->data->time_to_die)
	{
		print (philo, time, MSG_DIED);
		return (TRUE);
	}
	return (FALSE);
}

void	watch_philos(t_data *data)
{
	int	i;

	while (TRUE)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (is_dead (&data->philos[i]))
				return ;
			i += 1;
		}
		if (data->eat_to_satiated >= 0)
		{
			pthread_mutex_lock (&data->satiated_mutex);
			if (data->satiated_philos == data->philo_count)
			{
				pthread_mutex_unlock (&data->satiated_mutex);
				return ;
			}
			pthread_mutex_unlock (&data->satiated_mutex);
		}
	}
}
