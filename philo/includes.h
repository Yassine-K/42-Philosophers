/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhayri <ykhayri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:52:24 by ykhayri           #+#    #+#             */
/*   Updated: 2023/08/22 17:06:54 by ykhayri          ###   ########.fr       */
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

typedef struct s_single_p{
	int					id;
	int					eating;
	int					sleeping;
	int					thinking;
	int					dead;
	struct timeval		last_meal;
	struct s_single_p	*next;
}	t_single_p;

typedef struct s_settings{
	int				nbr_phil;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_meals;
	char			*arr[5];
	struct timeval	start_sec;
	struct timeval	curr_sec;
	struct timezone	zone;
	t_single_p		*philos;
}	t_settings;

void		add_back(t_single_p **philo_list, t_single_p *new_p);
void		print_state(int id, t_settings *settings, int state);
t_single_p	*new_phil(int id);
t_single_p	*find_last(t_single_p *philo_list);

#endif