/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:33:31 by aroque            #+#    #+#             */
/*   Updated: 2021/01/05 21:24:33 by aroque           ###   ########.fr       */
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
#include <signal.h>

static void	prompt(t_hashtable *env)
{
	ft_putstr_fd(ht_get(env, "USER"), STDOUT_FILENO);
	ft_putchar_fd('@', STDOUT_FILENO);
	ft_putstr_fd(ht_get(env, "HOST"), STDOUT_FILENO);
	ft_putstr_fd(" $ ", STDOUT_FILENO);
}

/*
** Main shell execution loop. REPL stands
** for Read-Eval-Print-Loop. All the process
** may be forked from REPL, and it runs until
** an 'exit' command or a SIGINT.
*/

void		repl(t_hashtable *env, char **envp)
{
	char	*input;
	char	**args;

	signal(SIGINT, sighandler);
	while (true)
	{
		prompt(env);
		get_next_line(STDIN_FILENO, &input);
		// args = tokenizer(input);
		args = ft_split(input, ' ');
		create_process(args, envp, env);
		// create_process(args);
	}
}
