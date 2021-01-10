/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:07:45 by abibi             #+#    #+#             */
/*   Updated: 2021/01/10 16:10:53 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	join_threads(pthread_t *threads, pthread_t mon, t_info info)
{
	int i;

	pthread_join(mon, NULL);
	i = 0;
	while (i < info.num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

static int	start_threads_odd(t_info info, t_philo *philos, pthread_t *threads)
{
	int i;

	i = 0;
	while (i < info.num)
	{
		if (i % 2 == 1)
		{
			i++;
			continue;
		}
		if (pthread_create(&threads[i], NULL, philo_process, &(philos[i])) != 0)
		{
			free(threads);
			return (-2);
		}
		usleep(25);
		i++;
	}
	return (1);
}

static int	start_threads_even(t_info info, t_philo *philos,
		pthread_t *threads)
{
	int i;

	i = 0;
	while (i < info.num)
	{
		if (i % 2 == 0)
		{
			i++;
			continue;
		}
		if (pthread_create(&threads[i], NULL, philo_process, &(philos[i])) != 0)
		{
			free(threads);
			return (-2);
		}
		usleep(25);
		i++;
	}
	return (1);
}

int			start_threads(t_info info, t_philo *philos)
{
	pthread_t	mon;
	pthread_t	*threads;

	if (!(threads = malloc(sizeof(pthread_t) * (info.num + 1))))
		return (-1);
	if (!start_threads_even(info, philos, threads))
		return (-1);
	if (!start_threads_odd(info, philos, threads))
		return (-1);
	if (pthread_create(&mon, NULL, monitor, philos) != 0)
	{
		free(threads);
		return (-2);
	}
	join_threads(threads, mon, info);
	free(threads);
	return (1);
}
