/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 21:54:31 by ykhayri           #+#    #+#             */
/*   Updated: 2023/09/25 19:46:15 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include <pthread.h>

void	ft_usleep(time_t t, t_settings *settings)
{
	struct timeval	time;
	time_t			later;
	time_t			now;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec / 1000 - settings->start_sec;
	later = now + t;
	while (now < later && check_val(&settings->mutex, &settings->progress))
	{
		if (!check_val(&settings->mutex, &settings->progress))
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

void	get_time(void *ptr, int type)
{
	t_settings		*settings;
	t_single_p		*phil;
	struct timeval	time;
	time_t			mil;

	if (type)
	{
		phil = (t_single_p *) ptr;
		pthread_mutex_lock(&phil->settings->mutex);
		gettimeofday(&time, NULL);
		mil = time.tv_sec * 1000 + time.tv_usec / 1000;
		if (type == 1)
			phil->last_meal = mil;
		else if (type == 2)
			phil->curr = mil;
		pthread_mutex_unlock(&phil->settings->mutex);
		return ;
	}
	settings = (t_settings *) ptr;
	pthread_mutex_lock(&settings->mutex);
	gettimeofday(&time, NULL);
	mil = time.tv_sec * 1000 + time.tv_usec / 1000;
	pthread_mutex_unlock(&settings->mutex);
	settings->start_sec = mil;
}

int	check_val(pthread_mutex_t *mtx, int *val)
{
	int	ret;

	pthread_mutex_lock(mtx);
	ret = *val;
	pthread_mutex_unlock(mtx);
	return (ret);
}

void	print_state(int id, t_settings *settings, int state, time_t t)
{
	time_t	time;

	time = t - settings->start_sec;
	pthread_mutex_lock(&settings->x);
	if (check_val(&settings->mutex, &settings->progress))
		printf("%ld %d %s\n", time, id, settings->arr[state]);
	pthread_mutex_unlock(&settings->x);
}
