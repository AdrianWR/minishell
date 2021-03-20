/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:37:39 by gariadno          #+#    #+#             */
/*   Updated: 2021/03/20 08:36:57 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "token.h"

static void	free_process(t_process **process)
{
	int			i;
	t_process	*p;

	p = *process;
	if (!p)
		return ;
	if (p->next)
		free_process(&(p->next));
	i = 0;
	while ((p)->input_file[i])
	{
		free((p)->input_file[i]->path);
		free((p)->input_file[i++]);
	}
	i = 0;
	while ((p)->output_file[i])
	{
		free((p)->output_file[i]->path);
		free((p)->output_file[i++]);
	}
	free_buffer((p)->local_env);
	free_buffer((p)->argv);
	free(p->command);
	free(p);
}

void		free_jobs(t_job **jobs)
{
	t_job	*job;

	job = *jobs;
	if (!job)
		return ;
	if (job->next)
		free_jobs(&(job->next));
	free_process(&(job->process_list));
	free(job);
	return ;
}

void		free_variable(void *v)
{
	free(((t_variable *)v)->value);
	free(v);
}

void		free_tokens(t_token **tokens)
{
	if (!(*tokens))
		return ;
	if ((*tokens)->next)
		free_tokens(&(*tokens)->next);
	free((*tokens)->value);
	free(*tokens);
	*tokens = NULL;
}

void		free_shell(t_session *session)
{
	ht_destroy(session->env, free_variable);
	free_jobs(&(session->jobs));
	freemat(session->envp);
	free(session);
}
