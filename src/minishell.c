/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:33:31 by aroque            #+#    #+#             */
/*   Updated: 2021/03/06 18:19:06 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "hash.h"
#include "libft.h"
#include "minishell.h"
#include "errcode.h"
#include "token.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>

static void	prompt(t_hashtable *env)
{
	ft_putstr_fd(ht_get(env, "USERNAME"), STDOUT_FILENO);
	ft_putchar_fd('@', STDOUT_FILENO);
	ft_putstr_fd(ht_get(env, "HOSTNAME"), STDOUT_FILENO);
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

	while (shell->exit == false)
	{
		signal(SIGINT, sighandler);
		prompt(shell->env);
		get_next_line(STDIN_FILENO, &input);
		shell->tokens = tokenizer(shell->input, shell->env);
		shell->args = ft_split(input, ' ');
		execute_command(shell);
	}
}
