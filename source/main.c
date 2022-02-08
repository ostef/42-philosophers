/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 15:39:31 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/08 18:54:25 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	initialize(t_data *data)
{
	int	i;

	pthread_mutex_init (&data->print_mutex, NULL);
	pthread_mutex_init (&data->death_mutex, NULL);
	pthread_mutex_init (&data->satiated_mutex, NULL);
	data->fork_mutexes = (t_mutex *)malloc (
			sizeof (t_mutex) * data->philo_count);
	if (!data->fork_mutexes)
		return (FALSE);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init (&data->fork_mutexes[i], NULL);
		i += 1;
	}
	data->philos = (t_philo *)malloc (sizeof (t_philo) * data->philo_count);
	memset (data->philos, 0, sizeof (t_philo) * data->philo_count);
	if (!data->philos)
		return (FALSE);
	data->start_time = get_time (data);
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		pthread_mutex_init (&data->philos[i].meal_mutex, NULL);
		pthread_create (&data->philos[i].thread_id, NULL, &philo_thread,
			&data->philos[i]);
		i += 1;
	}
	return (TRUE);
}

static void	terminate(t_data *data)
{
	int	i;

	i = 0;
	while (data->philos && i < data->philo_count)
	{
		pthread_join (data->philos[i].thread_id, NULL);
		i += 1;
	}
	i = 0;
	while (data->fork_mutexes && i < data->philo_count)
	{
		pthread_mutex_destroy (&data->philos[i].meal_mutex);
		pthread_mutex_destroy (&data->fork_mutexes[i]);
		i += 1;
	}
	free (data->philos);
	free (data->fork_mutexes);
	pthread_mutex_destroy (&data->satiated_mutex);
	pthread_mutex_destroy (&data->death_mutex);
	pthread_mutex_destroy (&data->print_mutex);
}

int	main(int argc, t_str *args)
{
	t_data	data;

	memset (&data, 0, sizeof (t_data));
	if (!parse_arguments (&data, argc - 1, args + 1))
	{
		write (2, "Error\n", sizeof ("Error\n") - 1);
		terminate (&data);
		return (1);
	}
	if (!initialize (&data))
	{
		terminate (&data);
		return (1);
	}
	watch_philos (&data);
	terminate (&data);
	return (0);
}
