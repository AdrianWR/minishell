/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 22:59:11 by aroque            #+#    #+#             */
/*   Updated: 2021/03/15 08:27:35 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "process.h"
#include "errcode.h"
#include "minishell.h"
#include <fcntl.h>

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

int			parse_output_redirect(t_process *p, t_token **tokens, bool append)
{
	static unsigned	i;
	static void		*tmp;
	t_token			*token;
	t_file			*output;

	if (!tmp || tmp != p)
	{
		tmp = p;
		i = 0;
	}
	*tokens = (*tokens)->next;
	token = *tokens;
	if ((token)->type != T_WORD)
		return (EPARSE);
	if (!(output = malloc(sizeof(*output))))
		return (ERRSYS);
	output->path = token->value;
	output->flags = O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC);
	p->output_file[i++] = output;
	return (0);
}

int			parse_input_redirect(t_process *p, t_token **tokens)
{
	static unsigned	i;
	static void		*tmp;
	t_token			*token;
	t_file			*input;

	if (!tmp || tmp != p)
	{
		tmp = p;
		i = 0;
	}
	*tokens = (*tokens)->next;
	token = *tokens;
	if ((*tokens)->type != T_WORD)
		return (EPARSE);
	if (!(input = malloc(sizeof(*input))))
		return (ERRSYS);
	input->path = (*tokens)->value;
	input->flags = O_RDONLY;
	p->input_file[i++] = input;
	return (0);
}

int			parse_words(t_process *p, t_token **tokens)
{
	static unsigned	i;
	static unsigned	j;
	static void		*tmp;
	char			*word;

	if (!tmp || tmp != p)
	{
		tmp = p;
		i = 0;
		j = 0;
	}
	word = (*tokens)->value;
	if (p->command == NULL && word[0] != '=' && ft_strchr(word, '='))
		p->local_env[j++] = word;
	else
	{
		if (i == 0)
			p->command = word;
		p->argv[i++] = word;
	}
	return (0);
}

t_process	*parse_command(t_token **tokens)
{
	t_process	*process;
	bool		exit;

	exit = false;
	if (!(process = ft_calloc(1, sizeof(*process))))
		return (NULL);
	while (*tokens && !exit)
	{
		if ((*tokens)->type == T_SEPARATOR || (*tokens)->type == T_PIPE)
			exit = true;
		else if ((*tokens)->type == T_WORD)
			parse_words(process, tokens);
		else if ((*tokens)->type == T_IREDIRECT)
			parse_input_redirect(process, tokens);
		else if ((*tokens)->type == T_OREDIRECT)
			parse_output_redirect(process, tokens, false);
		else if ((*tokens)->type == T_OAPPEND)
			parse_output_redirect(process, tokens, true);
		if (!exit)
			*tokens = (*tokens)->next;
	}
	return (process);
}
