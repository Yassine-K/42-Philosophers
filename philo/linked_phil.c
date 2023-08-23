/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_phil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:09:59 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/23 15:40:04 by ykhayri          ###   ########.fr       */
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
	philosopher->thinking = 1;
	philosopher->eating = 0;
	philosopher->sleeping = 0;
	philosopher->dead = 0;
	philosopher->next = NULL;
	return (philosopher);
}

t_single_p	*find_last(t_single_p *philo_list)
{
	while (philo_list->next)
		philo_list = philo_list->next;
	return (philo_list);
}

void	add_back(t_single_p **philo_list, t_single_p *new_p)
{
	if (!new_p)
		*philo_list = NULL;
	else if (!philo_list || new_p->id == 1)
		*philo_list = new_p;
	else
		find_last(*philo_list)->next = new_p;
}

void	no_cash_to_pay(t_single_p **philos)
{
	t_single_p	*tmp;

	while ((*philos)->id < (*philos)->next->id)
	{
		tmp = (*philos)->next;
		free(*philos);
		*philos = tmp;
	}
}
