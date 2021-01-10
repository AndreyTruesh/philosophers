/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abibi <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 04:07:51 by abibi             #+#    #+#             */
/*   Updated: 2021/01/09 04:28:13 by abibi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*ft_strdup(const char *s1)
{
	unsigned int	l;
	unsigned int	i;
	char			*buf;

	l = 0;
	while (s1[l] != '\0')
		l++;
	l++;
	buf = (char *)malloc(sizeof(*s1) * l);
	if (!buf)
		return ((char *)0);
	i = 0;
	while (i < l)
	{
		buf[i] = s1[i];
		i++;
	}
	return (buf);
}

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		len;
	int		neg;
	char	*res;

	if (n == 0)
		return (ft_strdup("0"));
	neg = n < 0 ? 1 : 0;
	len = ft_intlen(n) + neg;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return ((char *)0);
	if (neg)
		res[0] = '-';
	res[len] = '\0';
	while (len-- > neg)
	{
		res[len] = (n % 10) * (1 - 2 * neg) + '0';
		n /= 10;
	}
	return (res);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t len;

	i = 0;
	len = ft_strlen(src);
	while (src[i] != '\0' && i + 1 < size)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	if (len <= i)
		return (i);
	else
		return (len);
}
