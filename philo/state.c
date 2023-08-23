/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:22 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/23 15:30:37 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include <stdio.h>

void	print_state(int id, t_settings *settings, int state)
{
	unsigned long	time;

	gettimeofday(&settings->curr_sec, &settings->zone);
	time = settings->curr_sec.tv_sec - settings->start_sec.tv_sec;
	printf("%lu %d %s\n", time * 1000, id, settings->arr[state]);
}

void	*routine(void *data)
{
	t_single_p	*f;

	f = data;
	printf("routine: %d\n", f->id);
	return (data);
}

void	create_thread(t_single_p **philos)
{
	t_single_p	*tmp;
	int			max;

	max = 0;
	tmp = *philos;
	while (tmp && ++max == tmp->id)
	{
		if (pthread_create(&tmp->thread, NULL, &routine, tmp))
			philos = NULL;
		if (!philos)
			break ;
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
