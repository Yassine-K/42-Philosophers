/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_phil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:09:59 by ykhayri           #+#    #+#             */
/*   Updated: 2023/09/11 14:57:09 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

t_single_p	*new_phil(int id)
{
	t_single_p	*philosopher;

	philosopher = (t_single_p *) malloc(sizeof(t_single_p));
	if (!philosopher)
		return (NULL);
	philosopher->id = id;
	philosopher->eating = 0;
	philosopher->last_meal = 0;
	philosopher->curr = 0;
	pthread_mutex_init(&philosopher->mutex, NULL);
	philosopher->next = NULL;
	return (philosopher);
}

t_single_p	*find_last(t_single_p *philo_list)
{
	while (philo_list->next)
		philo_list = philo_list->next;
	return (philo_list);
}

t_single_p	*find_prev(t_single_p *philo_list, int id)
{
	t_single_p	*tmp;

	tmp = philo_list;
	while (tmp->next->id != id)
		tmp = tmp->next;
	return (tmp);
}

void	add_back(t_single_p **philo_list, t_single_p *new_p)
{
	if (new_p->id == 1)
		free(*philo_list);
	if (!new_p)
		*philo_list = NULL;
	else if (!philo_list || new_p->id == 1)
		*philo_list = new_p;
	else
		find_last(*philo_list)->next = new_p;
}

void	no_cash_to_pay(t_single_p **philos, int nbr)
{
	t_single_p	*tmp;
	int			i;

	i = -1;
	while (++i < nbr)
	{
		tmp = (*philos)->next;
		pthread_mutex_destroy(&tmp->mutex);
		free(*philos);
		*philos = tmp;
	}
}
