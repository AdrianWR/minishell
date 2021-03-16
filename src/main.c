/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 20:14:00 by aroque            #+#    #+#             */
/*   Updated: 2021/03/16 03:30:08 by gariadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "libft.h"
#include "minishell.h"
#include "errcode.h"
#include "commands.h"
#include <unistd.h>

t_shell			*g_shell;

int				main(int argc, char *argv[], char *envp[])
{
	t_shell	*shell;

	(void)argv;
	if (!(shell = ft_calloc(1, sizeof(*shell))))
		message_and_exit(ERRSYS, EXIT_FAILURE, NULL);
	g_shell = shell;
	if (argc != 1)
		message_and_exit(EUSAGE, EXIT_FAILURE, NULL);
	shell->env = load_env(envp);
	shell->fd = STDOUT_FILENO;
	repl(shell);
	free_shell(shell);
	return (EXIT_SUCCESS);
}
