/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:08:37 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/04 15:10:15 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

void delet_table(char **tab)
{
    int i;
    while (tab[i])
    {
        ft_strdel(&tab[i]);
        i++;
    }
    free(tab);
}

char **nocomment(char **table)
{
    int i;
    int j;
    char **tab;
    
    i = 0;
    j = 0;
    while(table[i])
    {
        if (table[i][0] != '#')
            j++;
        i++;
    }
    tab = malloc(sizeof(char *) * (j + 1));
    i = 0;
    j = 0;
    while (table[i])
    {
        if (table[i][0] != '#')
        {
            tab[j] = ft_strdup(table[i]);
            j++;
        }
        i++;
    }
    tab[j] = NULL;
    delet_table(table);
    return(tab);
}

char **nospace_nocomment(char **table)
{
    int i;
    int j;
    int k;
    char *tmp;
    char *tmp2;

    i = 0;
    table = nocomment(table);
    while (table[i])
    {
        j = 0;
        k = 0;
        while (table[i][j] != '\0')
        {
            if (table[i][j] != ' ')
                k++;
            j++;
        }
        tmp = malloc(sizeof(char) * k + 1);
        j = 0;
        k = 0;
        while (table[i][j] != '\0')
        {
            if (table[i][j] != ' ')
            {
                tmp[k] = table[i][j];
                k++;
            }
            j++;
        }
        tmp[k] = '\0';
        tmp2 = table[i];
        table[i] = ft_strdup(tmp);
        free(tmp);
        //free(tmp2);
        i++;
    }
    return (table);
    
}
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

int parser(int ac, char **av, t_obj *object)
{
    char **table;
    int i;

    i = 2;
    if (ac != 2 || !(table = file_reader(av,table)) || !(table[2]))
        return (0);
    table = nospace_nocomment(table);
    int t = -1;
    if (!check_cam(table[0], object) || !check_light(table[1], object))
    {
        printf("bro\n");
        return(0);
    }
    while(table[i])
    {
        if(!check_sphere(table[i], object) && !check_plane(table[i], object) && !check_cone(table[i], object) && !check_cy(table[i], object))
        {
            return(0);
        }
        i++;   
    }
    return (1);
}