#ifndef MINISHELL_H
# define MINISHELL_H

enum e_part_type {
	SPACES,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
	NORMAL,
	SPECIAL
};

typedef struct s_part {
	char				*part;
	enum e_part_type	type;
}	t_part;

typedef struct s_pipe
{
	int		infile;
	int		outfile;
	int		size;
	int		iter;
	int		len;
	int		begin;
	int		end;

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

char	**ft_get_commands(char **argv, int len, t_pipe *pipex);
char	**ft_split_commands(char const *s, char c);
void	ft_close_pipes(t_pipe pipex, int *pipefd);
void	ft_child_process(t_pipe pipex, int *pipefd, char **envp);
int		ft_pipex(int argc, char **argv, char **envp);

void	signals(void);

int		ft_echo(char **args, int nr_args);
int		ft_pwd(void);
int		ft_cd(char **args);
int		ft_env(char **envp);
int		ft_export(char **args, t_env *s_env);
int		ft_exit(char **args, int nr_args);
void	copy_env(char **envp, t_env *s_env);
int		ft_unset(char **args, t_env *s_env);

int		ft_executable(char **args, t_env *s_env);
void	expand_args(char **sp, int last_exit_status);
int		ft_export_print(char **envp);
t_part	*quote_split(char *s);
void	expand_unquoted_args(t_part *parts, int last_exit_status);
char	**parts_to_strings(t_part *parts);

int		ft_redirect_in(char **args, t_env *s_env, int argc);
int		ft_redirect_out(char **args, t_env *s_env, int argc);
int		ft_redirect_out_app(char **args, t_env *s_env, int argc);
void	ft_try_paths(char **paths, char **args, char **envp);
#endif
