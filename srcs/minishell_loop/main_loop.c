/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberset <pberset@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:00:53 by hlibine           #+#    #+#             */
/*   Updated: 2024/06/27 18:08:12 by pberset          ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../parsing/parsing.h"

char	*make_prompt(t_core *core)
{
	char	*prompt;
	char	*tmp;

	prompt = core->prompt;
	if (prompt != NULL)
		gfree(prompt);
	if (core->env->hasenv == false)
		prompt = ft_strjoin(&core->argv[0][2], "$ ");
	else
	{
		tmp = ft_strjoin("minshell:\033[1;34m", findenv("PWD")->value);
		prompt = ft_strjoin(tmp, "\033[0m$ ");
		gfree(tmp);
	}
	return (prompt);
}

static char	*ms_prompt(t_core *core)
{
	char	*tmp;
	char	*prompt;

	prompt = make_prompt(core);
	tmp = readline(prompt);
	if (!tmp)
		ms_error("readline error");
	addgarbage(tmp);
	gfree(prompt);
	return (tmp);
}

t_core	*minishell_loop(int ac, char **av, char **env)
{
	t_core		*core;

	while (true)
	{
		core = init(ac, av, env);
		core->line = ms_prompt(core);
		if (core->line[0] != 0)
			add_history(core->line);
		if (ft_strcmp(core->line, "exit") == 0)
			break ;
		if (tokenizer(ft_strtrim(core->line, WHITESPACE), core) < 0)
			continue ;
		parser(core, core->token);
		if (core->token_count > 0)
			execute(core, env);
		ms_pipelinesclear(&core->pipeline);
	}
	gfree(core->line);
	return (core);
}
