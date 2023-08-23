/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:22 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/23 16:28:34 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	print_state(int id, t_settings *settings, int state)
{
	unsigned long	time;

	gettimeofday(&settings->curr_sec, &settings->zone);
	time = settings->curr_sec.tv_sec - settings->start_sec.tv_sec;
	printf("%lu %d %s\n", time * 1000, id, settings->arr[state]);
}

void	*routine(void *data)
{
	t_void_args	*args;
	t_settings	*settings;
	t_single_p	tmp;
	int			fork_p[2];

	args = data;
	settings = args->settings;
	tmp = args->tmp;
	if (tmp.id - 2 > -1)
		fork_p[left] = tmp.id - 2;
	else
		fork_p[left] = settings->nbr_phil - 1;
	fork_p[right] = tmp.id - 1;
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
		args->tmp = *tmp;
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
