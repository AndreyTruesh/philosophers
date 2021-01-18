/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:36:27 by abibi             #+#    #+#             */
/*   Updated: 2021/01/18 20:11:01 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	take_forks(t_philo *philo)
{
	sem_wait(philo->info->turn);
	sem_wait(philo->info->forks);
	if (philo->info->stop)
	{
		sem_post(philo->info->turn);
		sem_post(philo->info->forks);
		return (0);
	}
	report_status(philo, philo->info, 0);
	sem_wait(philo->info->forks);
	sem_post(philo->info->turn);
	return (1);
}

static int	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	sem_wait(philo->info->sem_stop);
	if (philo->info->stop)
	{
		sem_post(philo->info->sem_stop);
		sem_post(philo->info->forks);
		sem_post(philo->info->forks);
		return (0);
	}
	report_status(philo, philo->info, 0);
	report_status(philo, philo->info, 1);
	philo->last_time_eat = get_timestamp();
	if (philo->info->eat_times >= 0)
		philo->eat_count++;
	sem_post(philo->info->sem_stop);
	usleep(1000 * philo->info->time_to_eat);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	return (1);
}

static void	*philo_process(void *ptr_philo)
{
	t_philo *philo;
	int		res;

	philo = (t_philo *)(ptr_philo);
	while (1 == 1)
	{
		res = eat(philo);
		if (!res)
			return (0);
		if (philo->info->stop)
			return (0);
		report_status(philo, philo->info, 2);
		usleep(1000 * philo->info->time_to_sleep);
		if (philo->info->stop)
			return (0);
		report_status(philo, philo->info, 3);
	}
}

void		join_threads(pthread_t *threads, pthread_t mon, t_info info)
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

int			start_threads(t_info info, t_philo *philos)
{
	int			i;
	pthread_t	mon;
	pthread_t	*threads;

	if (!(threads = malloc(sizeof(pthread_t) * (info.num + 1))))
		return (-1);
	i = 0;
	if (pthread_create(&mon, NULL, monitor, philos) != 0)
	{
		free(threads);
		return (-2);
	}
	while (i < info.num)
	{
		if (pthread_create(&threads[i], NULL, philo_process, &(philos[i])) != 0)
		{
			free(threads);
			return (-2);
		}
		usleep(50);
		i++;
	}
	join_threads(threads, mon, info);
	close_sems(info, threads);
	return (1);
}
