/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:21:03 by atyurina          #+#    #+#             */
/*   Updated: 2024/03/13 15:51:06 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy(t_data *vars)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&vars->stdout_mutex);
	pthread_mutex_destroy(&vars->die_mutex);
	pthread_mutex_destroy(&vars->full_mutex);
	while (i < vars->forks_nbr)
	{
		vars->forks->id = i;
		pthread_mutex_destroy(&vars->forks[i].fork);
		pthread_mutex_destroy(&vars->philo[i].last_meal_mutex);
		i++;
	}
	free_memory(vars);
}
