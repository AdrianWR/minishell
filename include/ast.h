/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroque <aroque@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:33:38 by aroque            #+#    #+#             */
/*   Updated: 2021/02/09 22:56:41 by aroque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "libft.h"

typedef enum	e_asttype
{
	WORD = 1,
	PIPE_SEQUENCE,
	COMMAND,
	CMD_NAME,
	CMD_SUFFIX
}				t_asttype;

typedef struct			s_astnode
{
	void				*content;
	t_asttype			type;
	struct s_astnode	*left;
	struct s_astnode	*right;
}						t_astnode;

t_astnode				*ft_nodenew(void *content);
void					ft_astclear(t_astnode *node, void (*del)(void *));
t_astnode 				*ast_parser(t_list *tokens);

#endif
