#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	signal_handler(int signo)
{
	g_signal = signo;
}

void setup_signals(void)
{
    struct sigaction sa;
    
    ft_memset(&sa, 0, sizeof(sa));
    
    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_RESTART;
    
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}
