/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:22 by ykhayri           #+#    #+#             */
/*   Updated: 2023/09/03 14:45:47 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	print_state(int id, t_settings *settings, int state, time_t t)
{
	time_t	time;

	time = t - settings->start_sec;
	pthread_mutex_lock(&settings->mutex);
	if (settings->progress)
		printf("%ld %d %s\n", time, id, settings->arr[state]);
	pthread_mutex_unlock(&settings->mutex);
}

void	*routine(void *data)
{
	t_settings		*settings;
	t_single_p		*tmp;

	tmp = (t_single_p *) data;
	pthread_mutex_lock(&tmp->settings->mutex);
	settings = tmp->settings;
	pthread_mutex_unlock(&tmp->settings->mutex);
	if (!(tmp->id % 2))
		usleep(100);
	while (settings->progress)
	{
		get_time(tmp, 2);
		print_state(tmp->id, settings, 0, tmp->curr);
		get_time(tmp, 2);
		print_state(tmp->id, settings, 1, tmp->curr);
		if (settings->nbr_phil > 1)
		{
			pthread_mutex_lock(&find_prev(tmp, tmp->id)->mutex);
			pthread_mutex_lock(&tmp->mutex);
			get_time(tmp, 2);
			print_state(tmp->id, settings, 1, tmp->curr);
			tmp->eating = 1;
			get_time(tmp, 1);
			print_state(tmp->id, settings, 2, tmp->curr);
				ft_usleep(settings->time_eat, settings);
			pthread_mutex_unlock(&tmp->mutex);
			pthread_mutex_unlock(&find_prev(tmp, tmp->id)->mutex);
		}
		if (tmp->eating)
		{
			tmp->eating = 0;
			get_time(tmp, 2);
			print_state(tmp->id, settings, 3, tmp->curr);
			if (settings->progress)
				ft_usleep(settings->time_sleep, settings);
			if (settings->num_meals && tmp->rounds < settings->num_meals)
			{
				tmp->rounds++;
				pthread_mutex_lock(&settings->mutex);
				settings->num_rounds++;
				if (settings->num_rounds >= settings->nbr_phil * settings->num_meals)
					settings->progress = 0;
				pthread_mutex_unlock(&settings->mutex);
			}
		}
		if (settings->nbr_phil == 1)
		{
			ft_usleep(settings->time_die, settings);
			get_time(tmp, 2);
			if (tmp->curr - settings->start_sec >= settings->time_die)
			{
				print_state(tmp->id, settings, 4, tmp->curr);
				settings->progress = 0;
			}
		}
	}
	return (data);
}

void	create_thread(t_single_p **philos, t_settings *settings)
{
	int			max;
	t_single_p	*tmp;

	max = 0;
	tmp = *philos;
	while (tmp && ++max == tmp->id)
	{
		pthread_mutex_lock(&settings->mutex);
		tmp->settings = settings;
		pthread_mutex_unlock(&settings->mutex);
		if (pthread_create(&tmp->thread, NULL, &routine, tmp))
			philos = NULL;
		if (!philos)
			break ;
		usleep(100);
		tmp = tmp->next;
	}
}

void	wait_for_thread(t_single_p **philos)
{
	t_single_p	*tmp;
	int			max;

	max = 0;
	tmp = *philos;
	while (tmp && ++max == tmp->id)
	{
		if (pthread_join(tmp->thread, NULL))
			philos = NULL;
		if (!philos)
			break ;
		tmp = tmp->next;
	}
}

void	get_time(void *ptr, int type)
{
	t_settings		*settings;
	t_single_p		*phil;
	struct timeval	time;
	time_t			mil;

	gettimeofday(&time, NULL);
	mil = time.tv_sec * 1000 + time.tv_usec / 1000;
	if (type)
	{
		phil = (t_single_p *) ptr;
		if (type == 1)
			phil->last_meal = mil;
		else if (type == 2)
			phil->curr = mil;
	}
	else
	{
		settings = (t_settings *) ptr;
		settings->start_sec = mil;
	}
}
