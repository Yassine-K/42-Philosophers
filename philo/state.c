/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:22 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/23 21:56:20 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	print_state(int id, t_settings *settings, int state, time_t t)
{
	time_t	time;

	time = t - settings->start_sec;
	printf("%ld %d %s\n", time, id, settings->arr[state]);
}

void	*routine(void *data)
{
	t_void_args		*args;
	t_settings		*settings;
	t_single_p		*tmp;

	args = data;
	settings = args->settings;
	tmp = args->tmp;
	if (!(tmp->id % 2))
		usleep(50);
	while (settings->progress)
	{
		get_time(tmp, 2);
		print_state(tmp->id, settings, 0, tmp->curr);
		pthread_mutex_lock(&tmp->mutex);
		if (settings->nbr_phil > 1)
		{
			get_time(tmp, 1);
			print_state(tmp->id, settings, 1, tmp->curr);
			pthread_mutex_lock(&find_prev(&args->tmp, tmp->id)->mutex);
			get_time(tmp, 1);
			print_state(tmp->id, settings, 1, tmp->curr);
			tmp->eating = 1;
			if (settings->progress)
				ft_usleep(settings->time_eat, settings);
			get_time(tmp, 1);
			print_state(tmp->id, settings, 2, tmp->curr);
		}
		pthread_mutex_unlock(&tmp->mutex);
		if (settings->nbr_phil > 1)
			pthread_mutex_unlock(&find_prev(&args->tmp, tmp->id)->mutex);
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
				if (settings->num_meals == tmp->rounds)
					settings->progress = 0;
			}
		}
	}
	return (data);
}

void	create_thread(t_single_p **philos, t_settings *settings)
{
	int			max;
	t_void_args	*args;
	t_single_p	*tmp;

	max = 0;
	tmp = *philos;
	args = malloc(sizeof(t_void_args));
	while (tmp && ++max == tmp->id)
	{
		args->settings = settings;
		args->tmp = tmp;
		if (pthread_create(&tmp->thread, NULL, &routine, args))
			philos = NULL;
		if (!philos)
			break ;
		usleep(50);
		tmp = tmp->next;
	}
	free(args);
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
		phil = ptr;
		if (type == 1)
			phil->last_meal = mil;
		else
			phil->curr = mil;
	}
	else
	{
		settings = ptr;
		settings->start_sec = mil;
	}
}
