/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 14:54:59 by cwu               #+#    #+#             */
/*   Updated: 2018/09/07 14:55:00 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(char **args, char **env)
{
	int		i;
	bool	nl;

	nl = 1;
	i = 1;
	if (!ft_strcmp(args[i], "-n") && (i++ >= 0))
		nl = 0;
	while (args[i])
	{
		(i == 1 || (!nl && i == 2)) ? 1 : ft_printf(" ");
		if (args[i][0] == '$')
			ft_printf("%s%s", YELLO, findenv(env, &args[i][1]));
		else
			ft_printf("%s%s", YELLO, args[i]);
		i++;
	}
	if (!nl)
		ft_printf("%s%%%s", REV, CLR);
	write(1, "\n", 1);
	return (0);
}

int		cd(char **arg, char **env)
{
	char *buf;

	if (arg[1] == NULL)
		buf = ft_strdup(findenv(env, "HOME"));
	else if (!ft_strcmp(arg[1], "-") && !arg[2])
		buf = ft_strdup(findenv(env, "OLDPWD"));
	else if (arg[2] != NULL)
		return (ft_printf("{R}😑 Incorrect number of arguments\n"));
	else if (arg[1][0] == '~' && (buf = ft_strdup(findenv(env, "HOME"))))
	{
		if (arg[1][1])
			buf = cw_stradd(buf, arg[1] + 1, ft_strlen(arg[1]) - 1);
	}
	else
		buf = arg[1];
	if (chdir(buf))
		ft_printf("{R}😶  cd: no such file or directory: %s\n", buf);
	else
	{
		ft_strcpy(findenv(env, "OLDPWD"), findenv(env, "PWD"));
		getcwd(findenv(env, "PWD"), 512);
	}
	if (!arg[1] || (!ft_strcmp(arg[1], "-") && !arg[2]) || arg[1][0] == '~')
		free(buf);
	return (0);
}

int		list_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s%s\n", YELLO, env[i]);
		i++;
	}
	return (0);
}

char	**set_env(char **arg, char **env)
{
	int		i;
	char	**tmp;
	char	**t;

	if ((t = check_existing(arg, env)))
		return (t);
	i = 0;
	while (env[i])
		i++;
	tmp = (char**)malloc(sizeof(char*) * (i + 2));
	i = 0;
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	tmp[i] = ft_strdup(arg[1]);
	tmp[i] = cw_stradd(tmp[i], "=", 1);
	tmp[i] = cw_stradd(tmp[i], arg[2], ft_strlen(arg[2]));
	tmp[i + 1] = NULL;
	free(env);
	return (tmp);
}

char	**unset_env(char **arg, char **env)
{
	int		i;

	if (!arg[1] || arg[2])
	{
		ft_printf("{R}😑  Incorrect number of arguments\n");
		return (env);
	}
	if ((i = findenvnum(env, arg[1])))
	{
		while (env[i + 1])
		{
			env[i] = env[i + 1];
			i++;
		}
		env[i] = NULL;
		return (env);
	}
	ft_printf("{R}🤣  Env does not exist\n");
	return (env);
}
