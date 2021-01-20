#include <signal.h>
#include "libft.h"
#include "minishell.h"
#include <unistd.h>

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		// kill(getpid(), SIGINT);
		ft_putchar_fd('\n', 1);
		// signal(SIGINT, sighandler);
	}
}