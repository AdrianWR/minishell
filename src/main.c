/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 20:14:00 by aroque            #+#    #+#             */
/*   Updated: 2021/01/05 20:14:47 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errcode.h"

int		main(int argc, char *argv[], char *envp[])
{
	t_hashtable *env;

	//(void) argc;
	//(void) argv;
	// Load configuration file and env variables
	if (argc != 1 || ft_strncmp("./minishell", argv[0], 11))
		message_and_exit(EUSAGE, 0x0);
	env = load_env(envp);
	// REPL loop
	repl(env);

	// Free memory and config

	return (EXIT_SUCCESS);
}
