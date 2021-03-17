/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:33:31 by aroque            #+#    #+#             */
/*   Updated: 2021/03/17 00:10:47 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "hash.h"
#include "commands.h"
#include "libft.h"
#include "minishell.h"
#include "errcode.h"
#include "token.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>

void		prompt(t_hashtable *env)
{
	ft_putstr_fd(get_value(env, "USERNAME"), STDOUT_FILENO);
	ft_putchar_fd('@', STDOUT_FILENO);
	ft_putstr_fd(get_value(env, "HOSTNAME"), STDOUT_FILENO);
	ft_putstr_fd(" $ ", STDOUT_FILENO);
}

/*
** Main shell execution loop. REPL stands
** for Read-Eval-Print-Loop. All the process
** may be forked from REPL, and it runs until
** an 'exit' command or a SIGINT.
*/

void		repl(t_shell *shell)
{
	char	*input;
	t_token	*tokens;

	while (true)
	{
		signal(SIGINT, sighandler_prompt);
		signal(SIGQUIT, sighandler_prompt);
		prompt(shell->env);
		if (!(get_next_line(STDIN_FILENO, &input)))
		{
			ht_destroy(shell->env, free_variable);
			free(input);
			free(shell);
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(EXIT_SUCCESS);
		}
		tokens = tokenizer(input, shell->env);
		free(input);
		shell->jobs = parser(tokens);
		free_tokens(&tokens);
		execute_all(shell);
	}
}
