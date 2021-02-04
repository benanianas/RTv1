/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsercamlight.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:09:29 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/04 15:09:35 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

void first_node(t_obj *obj, int *object, int objnum)
{
    int i;
    int c;
    int k;
    int j;

    i = -1;
    c = 0;
    k = 0;
    j = 0;
    obj->id = 0;
    obj->oneint = 0;
    obj->obj = malloc(sizeof(int *) * 3);
    while(++i < 3)
        obj->obj[i] = malloc(sizeof(int) * 3);
    obj->next = NULL;
    obj->head = obj;
    while (c < objnum * 3)
    {
            if(c == 3 || c == 6)
            {
                k++;
                j = 0;
            }
            obj->obj[k][j] = object[c];
            j++;
            c++;
    }
}
void node_filler(int id, int *object, int objnum, int add, t_obj *obj)
{   
    int i;
    int c;
    int j;
    int k;

    i = -1;
    c = 0;
    j = 0;
    k = 0;
    if (id == 0)
        first_node(obj, object, objnum);
    else
    {
        while(obj->next != NULL)
            obj = obj->next;
        obj->next = (t_obj *)malloc(sizeof(t_obj));
        obj->next->head = obj->head;
        obj = obj->next;
        obj->id = id;
        obj->oneint = add;
        obj->obj = malloc(sizeof(int *) * objnum);
        while(++i < objnum)
            obj->obj[i] = malloc(sizeof(int) * 3);
        obj->next = NULL;
        while(c < objnum * 3)
        {
            if(c == 3 || c == 6 || c == 9 || c == 12 || c == 15)
            {
                j++;
                k = 0;
            }
            obj->obj[j][k] = object[c];
            k++;
            c++;
        }
    }
}

int arr_counter(char **arr)
{
    int i;
    int j;

    i = 1;
    if (arr == NULL || arr[0] == NULL)
        return (0);
    else
    {
        while(arr[i])
        {
            j = 0;
            while(arr[i][j])
            {
                if(arr[i][j] < '0' && arr[i][j] > '9' && arr[i][j] != '-')
                    return (0);
                j++;
            }
            i++;
        }
        return (i - 1);
    }
}

int check_cam(char *tab, t_obj *obj)
{
    char **object;
    char **param;
    int i;
    int j;
    int allnum[9];
    
    i = 1;
    j = 0;
    if ((ft_strncmp("cam", tab, 2) != 0) || !(object = ft_strsplit(tab, ':')) || object[0] == NULL)
        return (0);
    if (arr_counter(object) == 3)
    {
        if ((ft_strncmp("pos", object[1], 2)) || (ft_strncmp("trs", object[2], 2)) || (ft_strncmp("dir", object[3], 2)))
            return (0);
        while(object[i])
        {
            param = ft_strsplit(object[i], ',');
            if(arr_counter(param) != 3)
                return (0);
            allnum[j] = ft_atoi(param[1]);
            allnum[j+1] = ft_atoi(param[2]);
            allnum[j+2] = ft_atoi(param[3]);
            i++;
            j += 3;
        }
        node_filler(0, allnum, 3, 0, obj);
        return(1);
    }
    return (0);

}
int check_light(char *tab, t_obj *obj)
{
    char **object;
    char **param;
    int i;
    int j;
    int allnum[9];
    
    i = 1;
    j = 0;
    if ((ft_strncmp("light", tab, 4) != 0) || !(object = ft_strsplit(tab, ':')) || object[0] == NULL)
        return (0);
    if (arr_counter(object) == 4)
    {
        if ((ft_strncmp("pos", object[1], 2)) || (ft_strncmp("trs", object[2], 2)) || (ft_strncmp("col", object[3], 2)) || (ft_strncmp("int", object[4], 2)))
            return (0);
        while(i < 4)
        {
            param = ft_strsplit(object[i], ',');
            if(arr_counter(param) != 3)
                return (0);
            allnum[j] = ft_atoi(param[1]);
            allnum[j+1] = ft_atoi(param[2]);
            allnum[j+2] = ft_atoi(param[3]);
            i++;
            j += 3;
        }
        param = ft_strsplit(object[i], ',');
        if(arr_counter(param) != 1)
                return (0);
        i = ft_atoi(param[1]);
        node_filler(1, allnum, 3, 1, obj);
        return (1);
    }
    return (0);
}

int check_sphere(char *tab, t_obj *obj)
{
    char **object;
    char **param;
    int i;
    int j;
    int allnum[9];
    
    i = 1;
    j = 0;
    if ((ft_strncmp("sphere", tab, 5) != 0) || !(object = ft_strsplit(tab, ':')) || object[0] == NULL)
        return (0);
    if (arr_counter(object) == 4)
    {
        if ((ft_strncmp("pos", object[1], 2)) || (ft_strncmp("trs", object[2], 2)) || (ft_strncmp("col", object[3], 2)) || (ft_strncmp("rad", object[4], 2)))
            return (0);
        while(i < 4)
        {
            param = ft_strsplit(object[i], ',');
            if(arr_counter(param) != 3)
                return (0);
            allnum[j] = ft_atoi(param[1]);
            allnum[j+1] = ft_atoi(param[2]);
            allnum[j+2] = ft_atoi(param[3]);
            i++;
            j += 3;
        }
        param = ft_strsplit(object[i], ',');
        if(arr_counter(param) != 1)
                return (0);
        i = ft_atoi(param[1]);
        node_filler(2, allnum, 3, i, obj);
        return (1);
    }
    return (0);

}

int check_plane(char *tab, t_obj *obj)
{
     char **object;
    char **param;
    int i;
    int j;
    int allnum[15];
    
    i = 1;
    j = 0;
    if ((ft_strncmp("plane", tab, 4) != 0) || !(object = ft_strsplit(tab, ':')) || object[0] == NULL)
        return (0);
    if (arr_counter(object) == 5)
    {
        if ((ft_strncmp("pos", object[1], 2)) || (ft_strncmp("trs", object[2], 2)) || (ft_strncmp("col", object[3], 2)) || (ft_strncmp("rot", object[4], 2)) || (ft_strncmp("dir", object[5], 2)))
            return (0);
        while(i < 6)
        {
            param = ft_strsplit(object[i], ',');
            if(arr_counter(param) != 3)
                return (0);
            allnum[j] = ft_atoi(param[1]);
            allnum[j+1] = ft_atoi(param[2]);
            allnum[j+2] = ft_atoi(param[3]);
            i++;
            j += 3;
        }
        node_filler(3, allnum, 5, 0, obj);
        return(1);
    }
    return (0);
}

int check_cone(char *tab, t_obj *obj)
{
    char **object;
    char **param;
    int i;
    int j;
    int allnum[15];
    
    i = 1;
    j = 0;
    if ((ft_strncmp("cone", tab, 3) != 0) || !(object = ft_strsplit(tab, ':')) || object[0] == NULL)
        return (0);
    if (arr_counter(object) == 6)
    {
        if ((ft_strncmp("pos", object[1], 2)) || (ft_strncmp("trs", object[2], 2)) || (ft_strncmp("col", object[3], 2)) || (ft_strncmp("rot", object[4], 2)) || (ft_strncmp("dir", object[5], 2)) || (ft_strncmp("ang", object[6], 2)))
            return (0);
        while(i < 6)
        {
            param = ft_strsplit(object[i], ',');
            if(arr_counter(param) != 3)
                return (0);
            allnum[j] = ft_atoi(param[1]);
            allnum[j+1] = ft_atoi(param[2]);
            allnum[j+2] = ft_atoi(param[3]);
            i++;
            j += 3;
        }
        param = ft_strsplit(object[i], ',');
        if(arr_counter(param) != 1)
                return (0);
        i = ft_atoi(param[1]);
        node_filler(4, allnum, 5, i, obj);
        return (1);
    }
    return (0);

}

int check_cy(char *tab, t_obj *obj)
{
    char **object;
    char **param;
    int i;
    int j;
    int allnum[15];
    
    i = 1;
    j = 0;
    if ((ft_strncmp("cylinder", tab, 7) != 0) || !(object = ft_strsplit(tab, ':')) || object[0] == NULL)
        return (0);
    if (arr_counter(object) == 6)
    {
        if ((ft_strncmp("pos", object[1], 2)) || (ft_strncmp("trs", object[2], 2)) || (ft_strncmp("col", object[3], 2)) || (ft_strncmp("rot", object[4], 2)) || (ft_strncmp("dir", object[5], 2)) || (ft_strncmp("rad", object[6], 2)))
            return (0);
        while(i < 6)
        {
            param = ft_strsplit(object[i], ',');
            if(arr_counter(param) != 3)
                return (0);
            allnum[j] = ft_atoi(param[1]);
            allnum[j+1] = ft_atoi(param[2]);
            allnum[j+2] = ft_atoi(param[3]);
            i++;
            j += 3;
        }
        param = ft_strsplit(object[i], ',');
        if(arr_counter(param) != 1)
                return (0);
        i = ft_atoi(param[1]);
        node_filler(5, allnum, 5, i, obj);
        return (1);
    }
    return (0);
}