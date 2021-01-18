/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:33:07 by abibi             #+#    #+#             */
/*   Updated: 2021/01/18 19:38:03 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	init_forks(t_info *info)
{
	sem_unlink("/forks");
	sem_unlink("/write");
	sem_unlink("/stop");
	sem_unlink("/turn");
	info->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, info->num);
	if (info->forks == SEM_FAILED)
		return (0);
	info->write = sem_open("/write", O_CREAT | O_EXCL, 0644, 1);
	if (info->write == SEM_FAILED)
		return (0);
	info->sem_stop = sem_open("/stop", O_CREAT | O_EXCL, 0644, 1);
	if (info->sem_stop == SEM_FAILED)
		return (0);
	info->turn = sem_open("/turn", O_CREAT | O_EXCL, 0644, 1);
	if (info->turn == SEM_FAILED)
		return (0);
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

int			init_table(t_philo **philos, t_info *info)
{
	int res;

	if (!init_philos(philos, info))
	{
		ft_putendl_fd("Malloc failed!", 2);
		return (0);
	}
	res = init_forks(info);
	if (res == 0)
	{
		ft_putendl_fd("Sem open error!", 2);
		return (0);
	}
	return (1);
}
