/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:45:59 by aroque            #+#    #+#             */
/*   Updated: 2021/03/06 17:53:09 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

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

int						parse_input_redirect(t_process *command, t_list **tk);
int						parse_output_redirect(t_process *cmd,
							t_list **tk, bool append);
void					add_to_args(char **argv, char *word);
void					push_process(t_process **lst, t_process *new);
t_process				*parse_command(t_list **tokens);

#endif
