/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 11:37:19 by abenani           #+#    #+#             */
/*   Updated: 2020/12/24 17:03:18 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/RTv1.h"

char **file_reader(char **av, char **table)
{
    int fd;
    char tmp[BUFF_SIZE + 1];
    int i;
    char *file_str;

    file_str = "\0";
    if ((fd = open(av[1], 0)))
    {
        while ((i = read(fd, tmp, BUFF_SIZE)))
        {
            tmp[i] = '\0';
            file_str = ft_strjoin(file_str, tmp);
        }
    }
    table = ft_strsplit(file_str, '\n');
    return table;
}

t_obj parser(int ac, char **av)
{
    t_obj object;
    char **table;

     
    if (ac != 2 || !(table = file_reader(av,table)) || !(table[2]))
        return (object);
    
    return (object);
}
int main(int ac, char **av)
{
    t_obj object;

    if (!(object = parser(ac,av)))
        perror("file ERROR :(");
    return 0;
}