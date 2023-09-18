/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:54:31 by ykhayri           #+#    #+#             */
/*   Updated: 2023/09/18 13:43:43 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include <sys/semaphore.h>

void	ft_usleep(time_t t, t_settings *settings)
{
	struct timeval	time;
	time_t			later;
	time_t			now;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000 - settings->start_sec;
	later = now + t;
	while (now < later && settings->progress)
	{
		if (!settings->progress)
			break ;
		usleep(100);
		gettimeofday(&time, NULL);
		now = time.tv_sec * 1000 + time.tv_usec / 1000 - settings->start_sec;
	}
}

int	ft_atoi(char *s)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (s[i] && s[i] < 33)
		i++;
	if (s[i] == '-')
		return (0);
	if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
		res = res * 10 + s[i++] - 48;
	if (s[i])
		res = 0;
	return (res);
}

void	get_time(t_settings *settings, int type)
{
	struct timeval	time;
	time_t			mil;

	gettimeofday(&time, NULL);
	mil = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (!type)
		settings->start_sec = mil;
	else if (type == 1)
		settings->last_meal = mil;
	else if (type == 2)
		settings->curr = mil;
}

void	print_state(int id, t_settings *settings, int state, time_t t)
{
	time_t	time;

	time = t - settings->start_sec;
	sem_wait(settings->print);
	if (settings->progress)
		printf("%ld %d %s\n", time, id + 1, settings->arr[state]);
	if (state == 4)
			sem_post(settings->ko);
	else
		sem_post(settings->print);
}
