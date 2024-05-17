/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlibine <hlibine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:20:59 by hlibine           #+#    #+#             */
/*   Updated: 2024/05/17 17:23:52 by hlibine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_core	*init(int ac, char **av, char **env)
{
	static t_core	*core;

	if (core)
		return (core);
	if (ac > 1)
		ms_error("minishell called with argument");
	core = galloc(sizeof(t_core));
	core->env = galloc(sizeof(t_env));
	core->env->rawenvs = galloc(sizeof(t_envparam));
	(*core->env->rawenvs) = NULL;
	core->token = galloc(sizeof(t_token));
	(*core->token) = NULL;
	core->argc = ac;
	core->argv = av;
	if (!env[0])
		init_noenv(core);
	else
		init_envs(core, env);
	fill_core_env(core);
	core->ms_stdin = dup(STDIN_FILENO);
	core->ms_stdout = dup(STDOUT_FILENO);
	return (core);
}

t_core	*get_core(void)
{
	static t_core *core;

	if (!core)
		core = init(0, 0, 0);
	return (core);
}
