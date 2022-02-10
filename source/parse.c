/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soumanso <soumanso@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:49:40 by soumanso          #+#    #+#             */
/*   Updated: 2022/02/09 21:07:18 by soumanso         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	int_is_outside_bounds(t_u64 uval, int next_digit)
{
	if (uval > 2147483647 / 10)
		return (TRUE);
	if (uval * 10 + next_digit > 2147483647)
		return (TRUE);
	return (FALSE);
}

static t_bool	parse_int(t_cstr str, int *out)
{
	t_u64	val;

	val = 0;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		if (int_is_outside_bounds (val, (*str) - '0'))
			return (FALSE);
		val *= 10;
		val += (*str) - '0';
		str += 1;
	}
	*out = val;
	return (TRUE);
}

t_bool	parse_arguments(t_data *data, int argc, t_str *args)
{
	if (argc < 4 || argc > 5)
		return (FALSE);
	if (!parse_int (args[0], &data->philo_count))
		return (FALSE);
	if (!parse_int (args[1], &data->time_to_die))
		return (FALSE);
	if (!parse_int (args[2], &data->time_to_eat))
		return (FALSE);
	if (!parse_int (args[3], &data->time_to_sleep))
		return (FALSE);
	data->eat_to_satiated = -1;
	if (argc == 5 && !parse_int (args[4], &data->eat_to_satiated))
		return (FALSE);
	return (TRUE);
}
