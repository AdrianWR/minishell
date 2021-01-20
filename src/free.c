#include "minishell.h"

void	freemat(char **mat)
{
	int i;

	i = 0;
	while (mat && mat[i])
	{
		free(mat[i]);
		mat[i++] = NULL;
	}
	if (mat)
	{
		free(mat);
		mat = NULL;
	}
}