/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:33:31 by aroque            #+#    #+#             */
/*   Updated: 2020/12/29 11:44:46 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>


/*
 * Main shell execution loop. REPL stands
 * for Read-Eval-Print-Loop. All the process
 * may be forked from REPL, and it runs until
 * an 'exit' command or a SIGINT.
 */
void	repl(void)
{
	char 	*line;
	char	**args;

	while (true)
	{
		ft_putstr_fd("aroque@minishell $ ", STDOUT_FILENO);
		get_next_line(STDIN_FILENO, &line);
		args = ft_split(line, ' ');
		create_process(args);
	}
}

int		main(int argc, char *argv[], char *envp[])
{
	// Load configuration file and env variables
	(void) argc;
	(void) argv;

	printf("%s\n", *envp);

	// REPL loop
	repl();

	// Free memory and config

	return (EXIT_SUCCESS);
}
