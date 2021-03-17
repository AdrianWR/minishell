/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 22:59:11 by aroque            #+#    #+#             */
/*   Updated: 2021/03/17 11:33:52 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "process.h"
#include "errcode.h"
#include "minishell.h"
#include <fcntl.h>

typedef enum	e_index
{
	I_ARGV,
	I_ENV,
	I_IRED,
	I_ORED,
	__I_SIZE
}				t_index;

void		push_process(t_process **lst, t_process *new)
{
	t_process		*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}

int			parse_output_redirect(t_process *p, t_token **tokens, bool append, int i[])
{
	t_token			*token;
	t_file			*output;

	*tokens = (*tokens)->next;
	token = *tokens;
	if ((token)->type != T_WORD)
		return (EPARSE);
	if (!(output = malloc(sizeof(*output))))
		return (ERRSYS);
	output->path = ft_strdup(token->value);
	output->flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
	p->output_file[i[I_ORED]++] = output;
	return (0);
}

int			parse_input_redirect(t_process *p, t_token **tokens, int i[])
{
	t_token			*token;
	t_file			*input;

	*tokens = (*tokens)->next;
	token = *tokens;
	if ((*tokens)->type != T_WORD)
		return (EPARSE);
	if (!(input = malloc(sizeof(*input))))
		return (ERRSYS);
	input->path = ft_strdup((*tokens)->value);
	input->flags = O_RDONLY;
	p->input_file[i[I_IRED]++] = input;
	return (0);
}

int			parse_words(t_process *p, t_token **tokens, int i[])
{
	char			*word;

	word = ft_strdup((*tokens)->value);
	if (p->command == NULL && word[0] != '=' && ft_strchr(word, '='))
		p->local_env[i[I_ENV]++] = word;
	else
	{
		if (i[I_ARGV] == 0)
			p->command = ft_strdup(word);
		p->argv[i[I_ARGV]++] = word;
	}
	return (0);
}

t_process	*parse_command(t_token **tokens)
{
	t_process	*process;
	bool		exit;
	int 		i[__I_SIZE];

	i[I_ARGV] = 0;
	i[I_ENV] = 0;
	i[I_IRED] = 0;
	i[I_ORED] = 0;
	exit = false;
	if (!(process = ft_calloc(1, sizeof(*process))))
		return (NULL);
	while (*tokens && !exit)
	{
		if ((*tokens)->type == T_SEPARATOR || (*tokens)->type == T_PIPE)
			exit = true;
		else if ((*tokens)->type == T_WORD)
			parse_words(process, tokens, i);
		else if ((*tokens)->type == T_IREDIRECT)
			parse_input_redirect(process, tokens, i);
		else if ((*tokens)->type == T_OREDIRECT)
			parse_output_redirect(process, tokens, false, i);
		else if ((*tokens)->type == T_OAPPEND)
			parse_output_redirect(process, tokens, true, i);
		if (!exit)
			*tokens = (*tokens)->next;
	}
	return (process);
}
