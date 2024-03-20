/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:16:09 by atyurina          #+#    #+#             */
/*   Updated: 2024/03/14 12:16:10 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_stdout(t_data *vars, char *str, int i)
{
	long long int	time;

	pthread_mutex_lock(&vars->die_mutex);
	if (vars->if_dead == false)
	{
		pthread_mutex_unlock(&vars->die_mutex);
		pthread_mutex_lock(&vars->stdout_mutex);
		time = (get_time()) - (vars->begin_time);
		printf("%lld  %i %s\n", time, i, str);
		pthread_mutex_unlock(&vars->stdout_mutex);
	}
	else
		pthread_mutex_unlock(&vars->die_mutex);
}
