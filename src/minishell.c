/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:33:31 by aroque            #+#    #+#             */
/*   Updated: 2021/01/03 14:27:01 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "hash.h"
#include "libft.h"
#include "minishell.h"
#include "errcode.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

static void prompt(t_hashtable *env)
{
	ft_putstr_fd(ht_get(env, "USER"), STDOUT_FILENO);
	ft_putchar_fd('@', STDOUT_FILENO);
	ft_putstr_fd(ht_get(env, "HOSTNAME"), STDOUT_FILENO);
	ft_putstr_fd(" $ ", STDOUT_FILENO);
}

/*
 * Main shell execution loop. REPL stands
 * for Read-Eval-Print-Loop. All the process
 * may be forked from REPL, and it runs until
 * an 'exit' command or a SIGINT.
 */
void	repl(t_hashtable *env)
{
	char 	*input;
	char	**args;

	while (true)
	{
		prompt(env);
		get_next_line(STDIN_FILENO, &input);
		//args = ft_split(line, ' ');
		args = tokenizer(input);
		create_process(args);
	}
}

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
