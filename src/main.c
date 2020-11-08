#include "minishell.h"

int	main()
{
	// Load config files, if any.

	// Run command loop.

	// Perform any shutdown/cleanup.

	
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current working dir: %s\n", cwd);
	else
		perror("getcwd() error");

	return 0;
}
