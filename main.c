#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct	s_list
{
	int	nb;
	char	*val;
}		t_list;

void ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

char *ft_getnb(int fd)
{
	int i;
	int size;
	char c[1];
	char *str;

	if (!(str = malloc(sizeof(char) * 128)))
		exit(1);
	i = 0;
	size = read(fd, c, 1);
	while (c[0] >= '0' && c[0] <= '9')
	{
		str[i] = c[0];
		size = read(fd, c, 1);
		i++;
	}
	return(str);
}

char *ft_getval(int fd, char *c)
{
	int i;
	int size;
	char *str;

	if (!(str = malloc(sizeof(char) * 128)))
		exit(1);
	i = 0;
	while (c[0] != '\n')
	{
		str[i] = c[0];
		size = read(fd, c, 1);
		i++;
	}
	return(str);
}

t_list *process(char *file)
{
	int	i;
	int	fd;
	int	len;
	int	size;
	char	c[1];
	t_list	*tab;

	if (!(tab = malloc(sizeof(t_list) * 33)))
		exit (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit (1);
	i = 0;
	while (i < 30)
	{
		tab[i].nb = atoi(ft_getnb(fd));
		size = read(fd, c, 1);
		while (c[0] == ' ')
			size = read(fd, c, 1);
		if (c[0] == ':')
			size = read(fd, c, 1);	
		while (c[0] == ' ')
			size = read(fd, c, 1);
		tab[i].val = strdup(ft_getval(fd, c));
		i++;
	}
	close (fd);
	return (tab);
}

void ft_print(int n, t_list *tab)
{
	int i;

	i = 0;
	if (n < 20)
	{
		while (n != tab[i].nb)
			i++;
		if (n == tab[i].nb)
			ft_putstr(tab[i].val);
		write(1, " ", 1);
	}
	else
	{
		while (n >= tab[i + 1].nb)
			i++;
		ft_putstr(tab[i].val);
		write(1, " ", 1);
		ft_print(n % 10, tab);
	}
}

int main(int ac, char **av)
{
	t_list *tab;

	if (ac == 2)
	{
		if (atoi(av[1]) < 0)
		{
			write(1, "Error\n", 6);
			return (0);
		}
		tab = process("dict.txt");
		ft_print(atoi(av[1]), tab);
	}
	return(0);
}
