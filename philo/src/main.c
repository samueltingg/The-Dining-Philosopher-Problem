/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:59:13 by sting             #+#    #+#             */
/*   Updated: 2024/10/15 11:08:43 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/*
void	eat(void) {

}

void	sleep(void) {

}

void	think(void) {

}

void	*run_routine(void *ptr) {



}
*/
void	init_philo_struct(t_philo *philo, char **argv, int argc)
{
	memset(philo, 0, sizeof(t_philo));
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->num_times_to_eat = ft_atoi(argv[5]);
	// todo: else -> initilize to 0?
}

// Todo: parse arguments
int	main(int argc, char **argv)
{
	t_philo	philo;
	// pthread_mutex_t mutex;
	// pthread_t thread1;

	// todo: Argv Error checking
	if (argc < 5)
	{
		printf("Error: Arguments should follow this format:\nnumber_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	init_philo_struct(&philo, argv, argc);

	// pthread_mutex_init(&mutex, NULL);
	// pthread_create(&thread1, NULL, run_routine, )
}
