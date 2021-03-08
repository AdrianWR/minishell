/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:44:23 by aroque            #+#    #+#             */
/*   Updated: 2021/03/06 18:28:37 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"
#include "process.h"
#include "libft.h"
#include "token.h"
#include "errcode.h"

static void		push_job(t_job **job, t_job *new)
{
	t_job		*tmp;

	if (!*job)
		*job = new;
	else
	{
		tmp = *job;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_job	*parse_job(t_token **tokens)
{
	t_job		*job;
	t_process	*head;
	t_process	*command;

	job = ft_calloc(1, sizeof(*job));
	head = NULL;
	while (*tokens && (*tokens)->type != T_SEPARATOR)
	{
		command = parse_command(tokens);
		push_process(&head, command);
		if (*tokens && (*tokens)->type != T_SEPARATOR)
			*tokens = (*tokens)->next;
	}
	job->process_list = head;
	return (job);
}

t_job			*parser(t_token *tokens)
{
	t_job		*jobs;

	jobs = NULL;
	while (tokens)
	{
		push_job(&jobs, parse_job(&tokens));
		if (tokens)
			tokens = tokens->next;
	}
	return (jobs);
}
