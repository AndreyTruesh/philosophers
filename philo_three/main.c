/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:52:00 by abibi             #+#    #+#             */
/*   Updated: 2021/01/09 04:57:30 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	str_is_int(const char *s)
{
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

static char	**get_sem_name_arr(int n)
{
	int		i;
	char	**sem_arr;
	char	*sem_num;

	sem_arr = malloc(sizeof(char *) * n);
	i = 0;
	while (i < n)
	{
		sem_num = ft_itoa(i);
		sem_arr[i] = malloc(sizeof(char) * (6 + ft_strlen(sem_num)));
		ft_strlcpy(sem_arr[i], "/eat_", 6);
		ft_strlcpy(sem_arr[i] + 5, sem_num, ft_strlen(sem_num) + 1);
		sem_unlink(sem_arr[i]);
		free(sem_num);
		i++;
	}
	return (sem_arr);
}

static int	get_info(int argc, char **argv, t_info *info)
{
	int i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (-1);
	while (i < argc)
	{
		if (!str_is_int(argv[i]))
			return (-2);
		i++;
	}
	info->ts = get_timestamp();
	info->num = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->sem_name_arr = get_sem_name_arr(info->num);
	if (argc == 6)
		info->eat_times = ft_atoi(argv[5]);
	else
		info->eat_times = -1;
	return (1);
}

static int	start_threads_error(int ret, t_philo *philos, t_info info)
{
	if (ret == -1)
		ft_putendl_fd("Malloc error!", 2);
	if (ret == -2)
		ft_putendl_fd("Fork error!", 2);
	free(info.forks);
	free(philos);
	return (1);
}

int			main(int argc, char **argv)
{
	t_philo	*philos;
	t_info	info;
	int		ret;

	ret = get_info(argc, argv, &info);
	if (ret == -1)
		ft_putendl_fd("Wrong number of arguments", 1);
	if (ret == -2)
		ft_putendl_fd("Wrong arguments", 1);
	if (ret != 1)
		return (1);
	if (!init_table(&philos, &info))
		return (1);
	ret = start_threads(info, philos);
	if (ret < 0)
		return (start_threads_error(ret, philos, info));
	free(philos);
	return (0);
}
