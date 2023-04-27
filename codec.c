#include <stdio.h>
#include "./gnl/get_next_line.h"
#include "./libft/libft.h"

int startwith(char *major, char *minor, int len)
{
	int	i;

	i = 0;
	while (major[i] == minor[i] && major[i] && minor[i])
		i++;
	if (i == len)
		return (1);
	else
		return (0);
}

int endwith(char *major, char *minor, int len)
{
	int	i;
	int i2;

	i = 0;
	while (major[i])
		i++;
	i -= len;
	i2 = 0;
	while (major[i] == minor[i2] && major[i] && minor[i2])
	{
		i++;
		i2++;
	}
	if (len == i2)
		return (1);
	else
		return (0);
}

char *set_cypher(char	*code)
{
	code += 8;
	return(ft_strdup(code));
}

char *set_cypher_ceasar(char	*code)
{
	code += 14;
	return(ft_strdup(code));
}

int	set_key(char	*code)
{
	code += 10;
	return(ft_atoi(code));
}

char *ceaser_type_encode(char *cypher, int decode_key)
{
	int	i;

	i = 0;
	while (cypher[i])
	{
		cypher[i] = cypher[i] + decode_key;
		i++;
	}
	return (cypher);
}

char *ceaser_type_decode(char *cypher, int decode_key)
{
	int	i;

	i = 0;
	while (cypher[i])
	{
		cypher[i] = cypher[i] - decode_key;
		i++;
	}
	return (cypher);
}

int printerror(int error)
{
	if (error == 1)
	{
		printf("\nERROR - This program implies that you use 2 arguments: the first is refering to the file you wish to decode, and the second to the file you wish to create with its results ;)\n");
		return (0);
	}
	if (error == 2)
	{
		printf("\nERROR - The file inserted as the first argument could not be read (not poggers)");
		return (0);
	}
	if (error == 3)
	{
		printf("\nCONTEXT SCREEN - This program is meant to be used with 2 arguments other than the program itself! for example, you have a .encode file that has the contents to be encoded, and you want the decoding results to be in a file called 'sanchopansa'. Therefore, the correct way to execute this program is by calling it as './codec file.encode sanchopansa'\n This, upon completion, will create a file called 'sanchopansa.ENCODETYPE', with the result of the decodification\n There are several types of decoding this program can do, starting with the .cyceasar files, generated from a encode file with the ceasar crypt type. If you wish to decode a cyceasar file, you can simply put it as the first argument on the program execution.\n");
		return (0);
	}
	else
		return (0);
}

int main(int argc, char **argv)
{
	int	fd;
	int fd_created;
	char *gnl;
	int	decode_key;
	char *cypher;

	if (argc != 3)
		return (printerror(1));
	gnl = "oi";
	if (endwith(argv[1], "CONTEXT", 7))
		return(printerror(3));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return(printerror(2));
	if (endwith(argv[1], ".encode", 7))
	{
		while (!startwith(gnl, "END_ENCODE", 10))
		{
			gnl = get_next_line(fd);
			printf("%s", gnl);
			if (startwith(gnl, "NEXT_CODE", 9))
				decode_key = set_key(gnl);
			if (startwith(gnl, "CONTENT", 7))
				cypher = set_cypher(gnl);
			if (startwith(gnl, "CYPHER_ENCODE_TYPE=caesar", 25))
			{
				cypher = ceaser_type_encode(cypher, decode_key);
				fd_created = open(ft_strjoin(argv[2], ".cyceasar"), O_WRONLY|O_CREAT|O_TRUNC, 00700);
				cypher = ft_strjoin("CYPHERCEASAR=",cypher);
				cypher = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin("NEXT_CODE=", ft_itoa(decode_key)), "\n"), cypher), "\nEND_DECODE");
				write(fd_created, cypher, ft_strlen(cypher));
				close(fd_created);
			}
			// if (startwith(gnl, "CYPHER_ENCODE_TYPE="))
		}
	}
	else if (endwith(argv[1], ".cyceasar", 9))
	{
		while (!startwith(gnl, "END_DECODE", 10))
		{
			gnl = get_next_line(fd);
			printf("%s", gnl);
			if (startwith(gnl, "NEXT_CODE", 9))
				decode_key = set_key(gnl);
			if (startwith(gnl, "CYPHERCEASAR", 12))
			{
				cypher = set_cypher_ceasar(gnl);
				cypher = ceaser_type_decode(cypher, decode_key);
				fd_created = open(ft_strjoin(argv[2], ".cyceasar_decrip"), O_WRONLY|O_CREAT|O_TRUNC, 00700);
				cypher = ft_strjoin("CONTENT=",cypher);
				cypher = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin("NEXT_CODE=", ft_itoa(decode_key)), "\n"), cypher), "\nEND_ENCODE");
				write(fd_created, cypher, ft_strlen(cypher));
				close(fd_created);
			}
		}
	}
}

// int main(int argc, char **argv)
// {
// 	int	fd;
// 	int fd_created;
// 	char *gnl;
// 	int	decode_key;
// 	char *cypher;

// 	if (argc != 3)
// 		return (1);
// 	gnl = "oi";
// 	fd = open(argv[1], O_RDONLY);
// 	while (!startwith(gnl, "END_DECODE", 10))
// 	{
// 		gnl = get_next_line(fd);
// 		printf("%s", gnl);
// 		if (startwith(gnl, "NEXT_CODE", 9))
// 			decode_key = set_key(gnl);
// 		if (startwith(gnl, "CONTENT", 7))
// 			cypher = set_cypher(gnl);
// 		if (startwith(gnl, "CYPHER_ENCODE_TYPE=caesar", 25))
// 		{
// 			cypher = ceaser_type_decode(cypher, decode_key);
// 			fd_created = open(ft_strjoin(argv[2], ".cyceasar"), O_WRONLY|O_CREAT|O_TRUNC, 00700);
// 			cypher = ft_strjoin("CYPHERCEASAR=",cypher);
// 			printf("%s\n",cypher);
// 			write(fd_created, cypher, ft_strlen(cypher));
// 			close(fd_created)
// 		}
// 	}
// }