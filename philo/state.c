/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:08:22 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/22 17:06:51 by ykhayri          ###   ########.fr       */
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
