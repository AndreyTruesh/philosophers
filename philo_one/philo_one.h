/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:07:21 by abibi             #+#    #+#             */
/*   Updated: 2021/01/09 04:10:17 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdint.h>
# include <string.h>
# include <stdio.h>

typedef struct	s_info
{
	int				num;
	unsigned long	ts;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_times;
	pthread_mutex_t	write;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_stop;
	int				stop;
}				t_info;

typedef struct	s_philo
{
	int				num;
	unsigned long	last_time_eat;
	int				eat_count;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	t_info			*info;
}				t_philo;

void			ft_putendl_fd(char *s, int fd);
char			*ft_itoa(int n);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
unsigned long	get_timestamp(void);
int				init_table(t_philo **philos, t_info *info);
void			report_status(t_philo *philo, t_info *info, int id);
int				start_threads(t_info info, t_philo *philos);
int				ft_atoi(const char *str);
void			*monitor(void *ptr_philos);
void			*philo_process(void *ptr_philo);

#endif
