/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:45:59 by aroque            #+#    #+#             */
/*   Updated: 2021/03/15 08:17:26 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <stdbool.h>
# include "libft.h"
# include "token.h"

typedef struct			s_file
{
	char				*path;
	int					flags;
	int					fd;
}						t_file;

typedef struct			s_process
{
	char 				*local_env[32];
	char				*command;
	char				*argv[64];
	t_file				*input_file[16];
	t_file				*output_file[16];
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

t_process				*parse_command(t_token **tokens);
int						parse_input_redirect(t_process *process,
							t_token **token);
int						parse_output_redirect(t_process *process,
							t_token **token, bool append);
void					add_to_args(char **argv, char *word);
void					push_process(t_process **lst, t_process *new);

#endif
