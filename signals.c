#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

/*void rl_replace_line (const char *text, int clear_undo);*/
/*rl_replace_line("", 0);*/
void	sigint_handler(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

void	signals(void)
{
	signal(SIGINT, sigint_handler);
}
