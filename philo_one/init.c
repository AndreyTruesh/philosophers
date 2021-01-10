/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:06:26 by abibi             #+#    #+#             */
/*   Updated: 2021/01/10 16:10:28 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	init_forks(t_philo *philos, t_info *info)
{
	int				i;
	pthread_mutex_t	*forks;

	if (!(forks = malloc(sizeof(pthread_mutex_t) * info->num)))
		return (-1);
	i = 0;
	while (i < info->num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (-2);
		i++;
	}
	info->forks = forks;
	i = 0;
	while (i < info->num)
	{
		philos[i].right = &forks[i];
		if (i != 0)
			philos[i].left = philos[i - 1].right;
		i++;
	}
	philos[0].left = philos[info->num - 1].right;
	return (1);
}

static int	init_philos(t_philo **philos, t_info *info)
{
	int i;

	i = 0;
	if (!(*philos = malloc(info->num * sizeof(t_philo))))
		return (0);
	while (i < info->num)
	{
		(*philos)[i].num = i;
		(*philos)[i].info = info;
		(*philos)[i].last_time_eat = get_timestamp();
		if (info->eat_times >= 0)
			(*philos)[i].eat_count = 0;
		i++;
	}
	return (1);
}

static int	mut_init(t_info *info)
{
	if (pthread_mutex_init(&info->write, NULL) != 0)
	{
		ft_putendl_fd("Mutex init failed!", 2);
		return (0);
	}
	if (pthread_mutex_init(&info->mutex_stop, NULL) != 0)
	{
		ft_putendl_fd("Mutex init failed!", 2);
		return (0);
	}
	return (1);
}

int			init_table(t_philo **philos, t_info *info)
{
	int res;

	if (!mut_init(info))
		return (0);
	if (!init_philos(philos, info))
	{
		free(info->forks);
		ft_putendl_fd("Malloc failed!", 2);
		return (0);
	}
	res = init_forks(*philos, info);
	if (res == -1)
	{
		ft_putendl_fd("Malloc failed!", 2);
		return (0);
	}
	if (res == -2)
	{
		free(info->forks);
		ft_putendl_fd("Mutex init failed!", 2);
		return (0);
	}
	return (1);
}
