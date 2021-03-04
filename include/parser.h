/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 10:41:48 by aroque            #+#    #+#             */
/*   Updated: 2021/03/03 23:23:49 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include "libft.h"

typedef struct			s_file
{
	char				*path;
	int					flags;
}						t_file;

typedef struct			s_process
{
	char				*argv[64];
	t_file				input_file;
	t_file				output_file[16];
	struct s_process	*next;
}						t_process;

t_process				*get_process(t_list *tokens);
t_list					*parser(t_list *tokens);
int						parse_input_redirect(t_process *command, t_list **tk);
int						parse_output_redirect(t_process *cmd,
							t_list **tk, bool append);
void					add_to_args(char **argv, char *word);
void					push_process(t_process **lst, t_process *new);

#endif
