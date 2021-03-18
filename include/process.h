/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:45:59 by aroque            #+#    #+#             */
/*   Updated: 2021/03/17 22:36:10 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <stdbool.h>
# include "libft.h"
# include "token.h"

typedef enum			e_index
{
	I_ARGV,
	I_ENV,
	I_IRED,
	I_ORED,
	__I_SIZE
}						t_index;

typedef struct			s_file
{
	char				*path;
	int					flags;
	int					fd;
}						t_file;

typedef struct			s_process
{
	char				*local_env[32];
	char				*command;
	char				*argv[64];
	t_file				*input_file[16];
	t_file				*output_file[16];
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

t_process				*parse_command(t_token **tokens);
void					push_process(t_process **lst, t_process *new);

#endif
