
#include "../../includes/includes.h"

static void	free_splited(char **var)
{
	int	i;

	i = -1;
	if (!var)
		return ;
	while (var[++i])
		free(var[i]);
	free(var);
}

static void	init_vars(t_options *options)
{
	options->floor_texture = false;
	options->skybox = false;
	options->sound = false;
	options->break_blocks = false;
}

static bool	create_options_file(t_file *file)
{
	int	fd;

	fd = open("./includes/options", O_CREAT, 0666);
	close(fd);
	if (!open_file(file, "./includes/options", O_RDWR))
	{
		msg_write(2, -1, OPTIONS_CREATE_FAILURE);
		return (false);
	}
	ft_putstr_fd("FLOOR_TEXTURE=TRUE\n", file->fd);
	ft_putstr_fd("SKYBOX=TRUE\n", file->fd);
	ft_putstr_fd("SOUND=TRUE\n", file->fd);
	ft_putstr_fd("BREAK_BLOCKS=TRUE\n", file->fd);
	close_file(file);
	if (!open_file(file, "./includes/options", O_RDONLY))
		return (false);
	return (true);
}

static void	set_option(t_options *options, char **var)
{
	if (ft_strcmp(var[0], "FLOOR_TEXTURE") == 0)
	{
		if (ft_strcmp(var[1], "TRUE\n") == 0 || ft_strcmp(var[1], "TRUE") == 0)
			options->floor_texture = true;
	}
	else if (ft_strcmp(var[0], "SKYBOX") == 0)
	{
		if (ft_strcmp(var[1], "TRUE\n") == 0 || ft_strcmp(var[1], "TRUE") == 0)
			options->skybox = true;
	}
	else if (ft_strcmp(var[0], "SOUND") == 0)
	{
		if (ft_strcmp(var[1], "TRUE\n") == 0 || ft_strcmp(var[1], "TRUE") == 0)
			options->sound = true;
	}
	else if (ft_strcmp(var[0], "BREAK_BLOCKS") == 0)
	{
		if (ft_strcmp(var[1], "TRUE\n") == 0 || ft_strcmp(var[1], "TRUE") == 0)
			options->break_blocks = true;
	}
	else
		msg_write(2, -1, UNKNOWN_OPTION);
	if (ft_strcmp(var[1], "TRUE\n") != 0 && ft_strcmp(var[1], "FALSE\n") != 0
		&& ft_strcmp(var[1], "TRUE") != 0 && ft_strcmp(var[1], "FALSE") != 0)
		msg_write(2, -1, OPTION_WRONG_VALUE);
}

void	initialize_options(t_core *core)
{
	t_file	file;
	char	**var;
	int		count;

	msg_write(1, -1, OPTIONS_LOAD);
	if (!open_file(&file, "./includes/options", O_RDONLY))
		if (!create_options_file(&file))
			msg_write(2, 2, ERROR_FATAL);
	init_vars(&core->options);
	while (get_next_line(&file) != false)
	{
		count = 0;
		var = ft_split(file.line, '=');
		if (var && file.line[0] != '\n')
		{
			while (var[count])
				count++;
			if (count != 2)
				msg_write(1, -1, BAD_OPTION_PATERN);
			else
				set_option(&core->options, var);
			free_splited(var);
		}
	}
	msg_write(1, -1, SUCCESS);
}
