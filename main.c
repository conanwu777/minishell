/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:54:29 by cwu               #+#    #+#             */
/*   Updated: 2018/09/07 14:54:31 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_existing(char **arg, char **env)
{
	int		i;
	int		j;

	if (!arg[1] || !arg[2] || arg[3])
	{
		ft_printf("{R}😑  Incorrect number of arguments\n");
		return (env);
	}
	if ((i = findenvnum(env, arg[1])) != -1)
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		ft_strcpy(&env[i][j + 1], arg[2]);
		return (env);
	}
	return (NULL);
}

char	*find_path(char *str, char **env, t_vp vp)
{
	if (findenv(env, "PATH"))
		vp.tmp = ft_strdup(findenv(env, "PATH"));
	vp.st = 0;
	while (vp.tmp && vp.tmp[vp.st])
	{
		vp.end = vp.st;
		while (vp.tmp[vp.end] && vp.tmp[vp.end] != ':')
			vp.end++;
		if (vp.tmp[vp.end])
			vp.tmp[vp.end] = '\0';
		if ((vp.dir = opendir(&vp.tmp[vp.st])))
		{
			while ((vp.entry = readdir(vp.dir)))
				if (!ft_strcmp(vp.entry->d_name, str))
				{
					vp.t = ft_strdup(&vp.tmp[vp.st]);
					free(vp.tmp);
					return (vp.t);
				}
			closedir(vp.dir);
		}
		vp.st = vp.end + 1;
	}
	vp.tmp ? free(vp.tmp) : 1;
	return (NULL);
}

int		sys_path(char **arg, char **env)
{
	t_vp	vp;
	int		pid;
	char	*str;

	vp.tmp = NULL;
	pid = fork();
	if (pid == 0)
	{
		if ((str = find_path(arg[0], env, vp)))
			str = cw_stradd(str, "/", 1);
		str = cw_stradd(str, arg[0], ft_strlen(arg[0]));
		ft_printf(YELLO);
		if (!access(str, F_OK) && !access(str, X_OK))
			execve(str, arg, env);
		else
		{
			ft_printf("{R}minishell😅 : command not found: %s\n", arg[0]);
			exit(1);
		}
	}
	else
		wait(NULL);
	return (0);
}

char	**process_args(char **arg, char **env)
{
	if (!ft_strcmp(arg[0], "echo"))
		echo(arg, env);
	else if (!ft_strcmp(arg[0], "exit"))
		exit(1);
	else if (!ft_strcmp(arg[0], "cd"))
		cd(arg, env);
	else if (!ft_strcmp(arg[0], "env"))
		list_env(env);
	else if (!ft_strcmp(arg[0], "setenv"))
		env = set_env(arg, env);
	else if (!ft_strcmp(arg[0], "unsetenv"))
		env = unset_env(arg, env);
	else
		sys_path(arg, env);
	return (env);
}

int		main(void)
{
	extern char	**environ;
	t_mp		mv;

	mv.b = 0;
	while (environ[mv.b])
		mv.b++;
	mv.env = (char**)malloc(sizeof(char*) * (mv.b + 1));
	mv.b = -1;
	while (environ[++mv.b])
		mv.env[mv.b] = environ[mv.b];
	mv.env[++mv.b] = NULL;
	ft_printf("%s%s😃  $> ", SCRC, WHITE);
	while ((mv.b = ft_gnl(0, &mv.line)) == 1)
	{
		mv.line = remove_space(mv.line);
		if (mv.line[0] && !(mv.v.res = NULL))
		{
			if ((mv.arg = split_args(mv.line, mv.v))
				&& (mv.env = process_args(mv.arg, mv.env)))
				free(mv.arg);
			free(mv.line);
		}
		ft_printf("%s😃  $> ", WHITE);
	}
	free(mv.env);
}
