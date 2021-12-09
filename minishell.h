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

typedef struct s_env
{
	char	**env;
	int		size;
}	t_env;

char	**ft_get_commands(char **argv, int len);
char	**ft_split_commands(char const *s, char c);
void	ft_close_pipes(t_pipe pipex, int *pipefd);
void	ft_child_process(t_pipe pipex, int *pipefd, char **envp);

void	signals(void);

int		ft_echo(char **args, int nr_args);
int		ft_pwd(void);
int		ft_cd(char **args);
void	ft_env(char **envp);
int		ft_export(char **args, t_env *s_env);
int		ft_exit(char **args, int nr_args);
void	copy_env(char **envp, t_env *s_env);

int		ft_executable(char **args, t_env *s_env);
void	expand_args(char **sp);
#endif
