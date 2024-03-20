/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyurina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:58:16 by atyurina          #+#    #+#             */
/*   Updated: 2024/03/04 16:58:18 by atyurina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_pointers(t_philo *philo)
{
	if (philo->vars->philo_nbr == 1)
		philo->right_fork = &philo->vars->forks[philo->nbr - 1].fork;
	else if (philo->nbr != philo->vars->philo_nbr)
	{
		philo->right_fork = &philo->vars->forks[philo->nbr - 1].fork;
		philo->left_fork = &philo->vars->forks[philo->nbr].fork;
	}
	else
	{
		philo->right_fork = &philo->vars->forks[philo->nbr - 1].fork;
		philo->left_fork = &philo->vars->forks[0].fork;
	}
}

void	forks_init(t_data *vars)
{
	int	i;

	i = 0;
	vars->forks = (t_fork *)malloc(vars->forks_nbr * sizeof(t_fork));
	if (!vars->forks)
		printf("Malloc error");
	while (i < vars->forks_nbr)
	{
		vars->forks[i].id = i;
		pthread_mutex_init(&vars->forks[i].fork, NULL);
		i++;
	}
}
