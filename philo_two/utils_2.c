/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:36:12 by abibi             #+#    #+#             */
/*   Updated: 2021/01/09 04:36:14 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int		start_ind(const char *str)
{
	int i;

	i = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

static int		end_ind(int *start_i, const char *str, int *positive)
{
	int end_i;

	end_i = *start_i;
	if (str[end_i] == '-')
	{
		*positive = 0;
		end_i++;
	}
	else if (str[end_i] == '+')
		end_i++;
	*start_i = end_i;
	while (str[end_i] >= 48 && str[end_i] <= 57)
		end_i++;
	return (--end_i);
}

int				ft_atoi(const char *str)
{
	int				start_i;
	int				end_i;
	int				positive;
	int				res;

	positive = 1;
	start_i = start_ind(str);
	end_i = end_ind(&start_i, str, &positive);
	res = 0;
	while (start_i <= end_i)
	{
		res = res * 10 + (str[start_i] - '0') * (-1 + positive * 2);
		if (res > 0 && positive == 0)
			return (0);
		if (res < 0 && positive == 1)
			return (-1);
		start_i++;
	}
	return (res);
}

void			ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

unsigned long	get_timestamp(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}
