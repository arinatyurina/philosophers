/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:20:50 by atyurina          #+#    #+#             */
/*   Updated: 2024/03/13 14:20:51 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_data *vars)
{
	vars->thread = (pthread_t *)malloc(vars->philo_nbr * sizeof(pthread_t));
	if (vars->thread == NULL)
	{
		printf("Failed to allocate memory for threads\n");
		return ;
	}
	vars->philo = (t_philo *)malloc(vars->philo_nbr * sizeof(t_philo));
	if (vars->philo == NULL)
	{
		printf("Failed to allocate memory for philosophers\n");
		return ;
	}
	forks_init(vars);
	pthread_mutex_init(&vars->stdout_mutex, NULL);
	pthread_mutex_init(&vars->die_mutex, NULL);
	pthread_mutex_init(&vars->full_mutex, NULL);
	vars->i = 0;
	vars->if_dead = false;
}
