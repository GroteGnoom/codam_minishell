#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		size;
	int		iter;

	char	**commands;
	char	**paths;

	char	*cmd;
	char	**cmd_flag;
}	t_pipe;

char	**ft_get_commands(char **argv, int len);
char	**ft_split_commands(char const *s, char c);
void	ft_close_pipes(t_pipe pipex, int *pipefd);
void	ft_child_process(t_pipe pipex, int *pipefd, char **envp);

void	signals(void);

int		ft_echo(char **args, int nr_args);
int		ft_pwd(void);
int		ft_cd(char **args);
void	ft_env(char **envp);

void	expand_args(char **sp);
#endif
