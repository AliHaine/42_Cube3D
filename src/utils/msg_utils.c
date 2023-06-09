#include "../../includes/includes.h"



void	msg_write_multiple(int fd, const char *str1, const char *str2)
{
	while (*str1)
		write(fd, str1++, 1);
	while (*str2)
		write(fd, str2++, 1);
	if (str2[ft_strlen(str2) - 1] == '\n')
		return ;
	write(fd, "\n", 1);
}

void	msg_write(int fd, int exitVal, MsgType msg)
{
	const char *str;

	str = Messages[msg];
	while (*str)
		write(fd, str++, 1);
	write(fd, "\n", 1);
	if (exitVal >= 0)
		exit(exitVal);
}
