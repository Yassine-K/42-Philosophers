/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_phil_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 20:09:59 by ykhayri           #+#    #+#             */
/*   Updated: 2023/09/18 11:49:52 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	no_cash_to_pay(t_settings *settings)
{
	sem_unlink("/Forks");
	sem_unlink("/Prog");
	sem_unlink("/Death");
	sem_unlink("/Print");
	sem_unlink("/Pay");
	free(settings);
}
