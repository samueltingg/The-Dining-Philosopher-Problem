/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:59:13 by sting             #+#    #+#             */
/*   Updated: 2024/10/17 17:00:11 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *ptr) {
	t_philo *philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0) // even num delay
		ft_usleep(50);
	while (1) // todo: died condition
	{
		// todo: take left fork 
		// todo: take right fork

		printf("[timestamp] %i is eating\n", philo->id);
		ft_usleep(philo->time_to_eat);
		printf("[timestamp] %i is sleeping\n", philo->id);
		ft_usleep(philo->time_to_sleep);
		printf("[timestamp] %i is thinking\n", philo->id);
	}
	return (NULL);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

void	init_philo_struct(t_philo *philo, int index, char **argv, int argc)
{
	memset(philo, 0, sizeof(t_philo));
	philo->id = index + 1;
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->num_times_to_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_philo	*philo_arr;
	int	i;
	int num_of_philos;
	pthread_mutex_t print_mutex;

	// todo: Argv Error checking
	if (argc < 5)
	{
		printf("Error: Arguments should follow this format:\nnumber_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	num_of_philos = ft_atoi(argv[1]);

	philo_arr = ft_calloc(num_of_philos + 1, sizeof(t_philo));
	if (!philo_arr) 
	{
		printf("Error: ft_calloc");
		return (1);
	}
	
	// todo: init elements in each t_philo struct
	i = -1;
	while (++i < num_of_philos)
		init_philo_struct(&philo_arr[i], i, argv, argc);

	pthread_mutex_init(&print_mutex, NULL);
	
	i = -1;
	while (++i < num_of_philos)
		pthread_create(&(philo_arr[i].thread), NULL, philo_routine, (void *)&philo_arr[i]);
	i = -1; 
	while (++i < num_of_philos)
		pthread_join(philo_arr[i].thread, NULL);

	// pthread_mutex_destroy(&mutex);

	// TODO: FREE
	free(philo_arr);
}
