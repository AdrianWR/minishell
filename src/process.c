/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
/*   Updated: 2020/12/29 14:57:53 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "commands.h"
#include "libft.h"
#include "errcode.h"

#include <stdio.h>

void		execute(char *const *argv)
{
	(void) argv;
}

void  		create_process(char *const *argv)
{
	pid_t	pid;
	int		status;
 
	if ((pid = fork()) < 0)
		message_and_exit(ERRSYS, NULL);
	// Child process
	else if (pid == 0)
		execute(argv);
	// Parent process
	else
	{
		while (wait(&status) != pid);
	}
}
