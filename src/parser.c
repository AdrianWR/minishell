/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:26:28 by aroque            #+#    #+#             */
/*   Updated: 2021/03/03 23:24:58 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokenizer.h"
#include "parser.h"
#include "errcode.h"

t_process	*parse_command(t_list **tokens)
{
	t_process	*command;
	bool		exit;
	unsigned	i;

	i = 0;
	exit = false;
	command = ft_calloc(1, sizeof(*command));
	while (*tokens && !exit)
	{
		if (((t_token *)(*tokens)->content)->type == T_SEPARATOR ||
				((t_token *)(*tokens)->content)->type == T_PIPE)
			exit = true;
		else if (((t_token *)(*tokens)->content)->type == T_WORD)
			command->argv[i++] = ((t_token *)(*tokens)->content)->value;
		else if (((t_token *)(*tokens)->content)->type == T_IREDIRECT)
			parse_input_redirect(command, tokens);
		else if (((t_token *)(*tokens)->content)->type == T_OREDIRECT)
			parse_output_redirect(command, tokens, false);
		else if (((t_token *)(*tokens)->content)->type == T_OAPPEND)
			parse_output_redirect(command, tokens, true);
		if (!exit)
			*tokens = (*tokens)->next;
	}
	return (command);
}

t_process	*parse_job(t_list **tokens)
{
	t_process	*head;
	t_process	*command;

	head = NULL;
	while (*tokens && ((t_token *)((*tokens)->content))->type != T_SEPARATOR)
	{
		command = parse_command(tokens);
		push_process(&head, command);
		if (*tokens && ((t_token *)((*tokens)->content))->type != T_SEPARATOR)
			*tokens = (*tokens)->next;
	}
	return (head);
}

t_list		*parser(t_list *tokens)
{
	t_list		*jobs;
	t_process	*commands;

	jobs = NULL;
	while (tokens)
	{
		commands = parse_job(&tokens);
		ft_lstadd_back(&jobs, ft_lstnew(commands));
		if (tokens)
			tokens = tokens->next;
	}
	return (jobs);
}
