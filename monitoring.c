/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:19:09 by atyurina          #+#    #+#             */
/*   Updated: 2024/03/14 12:19:10 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_data *vars)
{
	vars->j = 0;
	while (1)
	{
		pthread_mutex_lock(&vars->die_mutex);
		pthread_mutex_lock(&vars->full_mutex);
		while (vars->j != vars->philo_nbr)
		{
			if (vars->if_dead == true)
				break ;
			if (is_dead(&vars->philo[vars->j]) == 1)
				break ;
			if (vars->flag == true)
			{
				if (vars->all_full == true)
					break ;
			}
			vars->j++;
		}
		pthread_mutex_unlock(&vars->die_mutex);
		pthread_mutex_unlock(&vars->full_mutex);
		if (vars->j == vars->philo_nbr)
			vars->j = 0;
		else
			break ;
	}
}

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	if ((get_time() - philo->time_last_meal) >= philo->vars->t_die)
	{
		pthread_mutex_unlock(&philo->last_meal_mutex);
		philo->alive = false;
		philo->vars->if_dead = true;
		pthread_mutex_lock(&philo->vars->stdout_mutex);
		printf("%lld  %i %s\n", (get_time()) - (philo->vars->begin_time),
			philo->nbr, "died");
		pthread_mutex_unlock(&philo->vars->stdout_mutex);
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->last_meal_mutex);
	return (0);
}

void	philo_is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->full_mutex);
	if (philo->vars->philos_to_eat != 0)
	{
		philo->vars->philos_to_eat--;
		if (philo->vars->philos_to_eat == 0)
			philo->vars->all_full = true;
	}
	pthread_mutex_unlock(&philo->vars->full_mutex);
}
