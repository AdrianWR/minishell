/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gariadno <gariadno@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 02:37:39 by gariadno          #+#    #+#             */
/*   Updated: 2021/03/16 23:56:31 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "token.h"

void	free_variable(void *v)
{
	free(((t_variable *)v)->value);
	free(v);
}

void	free_tokens(t_token **tokens)
{
	if (!(*tokens))
		return ;
	if ((*tokens)->next)
		free_tokens(&(*tokens)->next);
	free((*tokens)->value);
	free(*tokens);
	*tokens = NULL;
}

void	free_buffer(char **buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
		free(buffer[i++]);
}

void	free_process(t_process **process)
{
	int i;

	if (!(*process))
		return ;
	if ((*process)->next)
		free_process(&(*process)->next);
	i = 0;
	while ((*process)->input_file[i])
	{
		free((*process)->input_file[i]->path);
		free((*process)->input_file[i++]);
	}
	i = 0;
	while ((*process)->output_file[i])
	{
		free((*process)->output_file[i]->path);
		free((*process)->output_file[i++]);
	}
	free_buffer((*process)->local_env);
	free_buffer((*process)->argv);
	free((*process)->command);
	free(*process);
	*process = NULL;
}

void	free_jobs(t_job **jobs)
{
	if (!(*jobs))
		return ;
	if ((*jobs)->next)
		free_jobs(&(*jobs)->next);
	free_process(&((*jobs)->process_list));
	free(*jobs);
	*jobs = NULL;
	return ;
}

void		freemat(char **mat)
{
	int i;

	i = 0;
	while (mat[i])
		free(mat[i++]);
	free(mat);
}

void		free_shell(t_shell *shell)
{
	ht_destroy(shell->env, free_variable);
	free_jobs(&(shell->jobs));
	freemat(shell->envp);
	free(shell);
}
