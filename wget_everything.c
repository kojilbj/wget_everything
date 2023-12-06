#include "./libft.h"
#include <stdio.h>
#include <fcntl.h>
void child_process(char *args[])
{
    execve("/opt/homebrew/bin/wget", args, NULL);
}


void run_process(char *url)
{
    int ipd = fork();
    char *args[] = {"wget", url, NULL};
    if(ipd == 0)
        child_process(args);
    wait(NULL);
}


char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*str_joined;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str_joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str_joined == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_joined[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\"')
	{
		str_joined[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	str_joined[ft_strlen(s1) + i] = 0;
	return (str_joined);
}

const char	**split_line(int fd)
{
	const char	**splited_line;
	char	*buf;
	buf = malloc(100000);

	ft_bzero(buf, 100000);
	read(fd, buf, 100000);
	splited_line = ft_split(buf, '\n');
	free(buf);
	return splited_line;
}

void	wget_all_photo(const char **splited_line)
{
	char	*path = "<div class=\"photo\"><img src=\"/teamdata/players/image/2023/";
	char	*url_path = "https://dragons.jp/teamdata/players/image/2023/";
	while(*splited_line)
	{
		while(**splited_line == 9 || **splited_line == ' ')
			(*splited_line)++;
		if(ft_strncmp(*splited_line, path, ft_strlen(path)) == 0)
		{
			run_process(ft_strjoin_path(url_path, *splited_line + ft_strlen(path)));
		}
		splited_line++;
	}
}

int	main(int ac, char *av[])
{
	char	*file_path;
	int	fd;
	if(ac != 2)
		return 0;
	file_path = av[1];
	fd = open(file_path, O_RDONLY);
	const char	**splited_line = split_line(fd);
	wget_all_photo(splited_line);
	close(fd);
	return 0;
}
