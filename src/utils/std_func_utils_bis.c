/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_func_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:37:56 by ngalzand          #+#    #+#             */
/*   Updated: 2023/10/02 15:38:00 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/includes.h"

int	ft_atoi_for_texture(const char *s)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	if (!s)
		return (-1);
	if (s[0] == '0')
		return (0);
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (-1);
		val += (s[i++] - '0');
		val *= 10;
	}
	val /= 10;
	if (val > 255 || val < 0)
		return (-1);
	return (val);
}

bool	is_str_blank(const char *s)
{
	while (*s && *s != '\n')
	{
		if (*s != ' ')
			return (false);
		s++;
	}
	return (true);
}

void	free_tab_three(char ***tab)
{
	int	i;
	int	y;

	i = 9;
	y = 0;
	while (i-- > 0)
	{
		while (tab[i][y])
			free(tab[i][y++]);
		y = 0;
		free(tab[i]);
	}
}

void	copy_tab(char **tab_src, char **tab_dst, int height, int width)
{
	int	i;

	i = width;
	while (height-- > 0)
	{
		while (i-- > 0)
			tab_dst[height][i] = tab_src[height][i];
		i = width;
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!fd || (fd < 0 || fd > 255) || !s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
