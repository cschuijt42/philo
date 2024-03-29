/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cschuijt <cschuijt@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 22:21:55 by cschuijt      #+#    #+#                 */
/*   Updated: 2023/05/30 22:21:55 by cschuijt      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_simulation(t_philosopher **philo_array, t_state *state)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(state->state_mutex));
	while (philo_array[i])
	{
		pthread_create(&(philo_array[i]->thread), NULL, \
						philosopher_routine, philo_array[i]);
		i++;
	}
	state->start_time = time_in_us();
	i = 0;
	while (philo_array[i])
	{
		philo_array[i]->dies_at = state->start_time + \
									(state->time_to_die * 1000);
		i++;
	}
	pthread_mutex_unlock(&(state->state_mutex));
}

static void	run_single_philo_simulation(t_philosopher **philo_array, \
										t_state *state)
{
	state->start_time = time_in_us();
	print_with_time(philo_array[0], "is thinking");
	pthread_mutex_lock(&(philo_array[0]->fork_r));
	print_with_time(philo_array[0], "has grabbed a fork");
	scuffed_sleep(state->time_to_die);
	print_with_time(philo_array[0], "has died");
	pthread_mutex_unlock(&(philo_array[0]->fork_r));
}

static bool	simulation_wrapper(t_philosopher **philo_array, t_state *state)
{
	if (state->num_philosophers == 1)
	{
		run_single_philo_simulation(philo_array, state);
		return (false);
	}
	else
	{
		run_simulation(philo_array, state);
		return (true);
	}
}

int	main(int ac, char **av)
{
	t_state			state;
	t_philosopher	**philo_array;

	if (!run_input_validations(ac, av))
		return (1);
	state = create_state_struct(av);
	if (pthread_mutex_init(&state.state_mutex, NULL))
		return (1);
	if (setup_philosopher_array(&philo_array, &state))
	{
		if (distribute_forks(philo_array))
		{
			if (simulation_wrapper(philo_array, &state))
			{
				monitor_philosophers(philo_array);
				join_all_threads(philo_array);
			}
			free_philosopher_array(philo_array, false);
		}
		else
			free_philosopher_array(philo_array, true);
	}
	pthread_mutex_destroy(&state.state_mutex);
	return (0);
}
