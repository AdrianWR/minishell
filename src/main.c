/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 20:14:00 by aroque            #+#    #+#             */
/*   Updated: 2021/03/20 08:39:04 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include "libft.h"
#include "minishell.h"
#include "errcode.h"
#include "commands.h"
#include <unistd.h>

t_session			*g_session;

int				main(int argc, char *argv[], char *envp[])
{
	t_session	*session;

	(void)argv;
	if (!(session = ft_calloc(1, sizeof(*session))))
		message_and_exit(ERRSYS, NULL);
	g_session = session;
	if (argc != 1)
		message_and_exit(EUSAGE, NULL);
	session->env = load_env(envp);
	repl(session);
	return (EXIT_SUCCESS);
}
