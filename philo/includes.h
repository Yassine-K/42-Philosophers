/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:52:24 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/21 20:53:38 by ykhayri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct t_philo{
    int nbr_phil;
    int time_die;
    int time_eat;
    int time_sleep;
    int num_meals;
}   s_philo;

typedef struct t_single_p{
    int id;
    int eating;
    int waiting;
    int sleeping;
    int dead;
    struct t_single_p *next;
} s_single_p;

void	    add_back(s_single_p **philo_list, s_single_p *new_p);
s_single_p	*new_phil(int id);
s_single_p	*find_last(s_single_p *philo_list);

#endif