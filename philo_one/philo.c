/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:10:04 by abibi             #+#    #+#             */
/*   Updated: 2021/01/17 17:52:51 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	if (philo->info->stop)
	{
		pthread_mutex_unlock(philo->left);
		return (0);
	}
	report_status(philo, philo->info, 0);
	pthread_mutex_lock(philo->right);
	return (1);
}

static int	eat(t_philo *philo)
{
	if (!take_forks(philo))
		return (0);
	pthread_mutex_lock(&philo->info->mutex_stop);
	if (philo->info->stop)
	{
		pthread_mutex_unlock(&philo->info->mutex_stop);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
		return (0);
	}
	report_status(philo, philo->info, 0);
	report_status(philo, philo->info, 1);
	philo->last_time_eat = get_timestamp();
	if (philo->info->eat_times >= 0)
		philo->eat_count++;
	pthread_mutex_unlock(&philo->info->mutex_stop);
	usleep(1000 * philo->info->time_to_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (1);
}

void		*philo_process(void *ptr_philo)
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
