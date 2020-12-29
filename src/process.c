/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 23:03:34 by aroque            #+#    #+#             */
/*   Updated: 2020/12/28 23:14:42 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "commands.h"
#include "libft.h"

#include <stdio.h>

void  		create_process(char **argv)
{
	pid_t	pid;
	int		status;
 
	if ((pid = fork()) < 0)
	{
		//message_and_exit(ERRFRK);
		printf("*** ERROR: forking child process failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		if (ft_strncmp(*argv, "echo", 5))
			echo(&argv[1]);
		if (execvp(*argv, argv) < 0)
		{
			printf("*** ERROR: exec failed\n");
			exit(1);
		}
	}
	else
	{
		while (wait(&status) != pid);
	}
}
