/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsercamlight.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:09:29 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/22 17:50:20 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv1.h"

void		first_node(t_obj *obj, int *object, int objnum)
{
	t_node n;

	n.i = -1;
	n.c = 0;
	n.k = 0;
	n.j = 0;
	obj->id = 0;
	obj->oneint = 0;
	obj->obj = malloc(sizeof(double *) * 4);
	while (++n.i < 3)
		obj->obj[n.i] = malloc(sizeof(double) * 3);
	obj->next = NULL;
	obj->head = obj;
	while (n.c < objnum * 3)
	{
		if (n.c == 3 || n.c == 6)
		{
			n.k++;
			n.j = 0;
		}
		obj->obj[n.k][n.j] = object[n.c];
		n.j++;
		n.c++;
	}
	obj->obj[3] = NULL;
}

void		node_filler(int id, int *object, int objnum, int add, t_obj *obj)
{
	t_node n;

	n.i = -1;
	n.c = -1;
	n.j = 0;
	n.k = 0;
	if (id == 0)
		first_node(obj, object, objnum);
	else
	{
		while (obj->next != NULL)
			obj = obj->next;
		obj->next = (t_obj *)malloc(sizeof(t_obj));
		obj->next->head = obj->head;
		obj = obj->next;
		obj->id = id;
		obj->oneint = add;
		obj->obj = malloc(sizeof(double *) * objnum + 1);
		while (++n.i < objnum)
			obj->obj[n.i] = malloc(sizeof(double) * 3);
		obj->next = NULL;
		while (++n.c < objnum * 3)
		{
			if (n.c == 3 || n.c == 6 || n.c == 9 || n.c == 12 || n.c == 15)
			{
				n.j++;
				n.k = 0;
			}
			obj->obj[n.j][n.k] = object[n.c];
			n.k++;
		}
	}
	obj->obj[objnum] = NULL;
}

int			arr_counter(char **arr, int flag)
{
	int i;
	int j;

	i = 0;
	if (arr == NULL || arr[0] == NULL)
		return (0);
	else
	{
		while (arr[++i])
		{
			if (flag == 1)
			{
				j = 0;
				while (arr[i][j])
				{
					if (j == 0 && arr[i][j] == '-')
						j++;
					if (arr[i][j] < '0' || arr[i][j] > '9')
						return (0);
					j++;
				}
			}
		}
		return (i - 1);
	}
}

int			check_cam(char *tab, t_obj *obj)
{
	t_check c;

	c.i = 1;
	c.j = 0;
	if ((ft_stc("cam", tab, 3) != 0) || !(c.obt = ft_strsplit(tab, ':'))
			|| c.obt[0] == NULL)
		return (0);
	if (arr_counter(c.obt, 0) == 3)
	{
		if ((ft_stc("pos", c.obt[1], 3)) || (ft_stc("trs", c.obt[2], 3))
				|| (ft_stc("dir", c.obt[3], 3)))
			return (0);
		while (c.obt[c.i])
			paramtonum(&c);
		node_filler(0, c.allnum, 3, 0, obj);
		delet_table(c.obt);
		return (1);
	}
	return (0);
}

int			check_light(char *tab, t_obj *obj)
{
	t_check c;

	c.i = 1;
	c.j = 0;
	if ((ft_stc("light", tab, 5) != 0) || !(c.obt = ft_strsplit(tab, ':'))
			|| c.obt[0] == NULL)
		return (0);
	if (arr_counter(c.obt, 0) == 4)
	{
		if ((ft_stc("pos", c.obt[1], 3)) || (ft_stc("trs", c.obt[2], 3))
				|| (ft_stc("col", c.obt[3], 3)) || (ft_stc("int", c.obt[4], 3)))
			return (0);
		while (c.i < 4)
			paramtonum(&c);
		c.param = ft_strsplit(c.obt[c.i], ',');
		if (arr_counter(c.param, 1) != 1)
			return (0);
		c.i = ft_atoi(c.param[1]);
		node_filler(1, c.allnum, 3, c.i, obj);
		delet_table(c.param);
		delet_table(c.obt);
		return (1);
	}
	return (0);
}

int		check_sphere(char *tab, t_obj *obj)
{
	t_check c;

	c.i = 1;
	c.j = 0;
	if ((ft_stc("sphere", tab, 6) != 0) || !(c.obt = ft_strsplit(tab, ':')) || c.obt[0] == NULL)
		return (0);
	if (arr_counter(c.obt, 0) == 4)
	{
		if ((ft_stc("pos", c.obt[1], 3)) || (ft_stc("trs", c.obt[2], 3))
			|| (ft_stc("col", c.obt[3], 3)) || (ft_stc("rad", c.obt[4], 3)))
			return (0);
		while (c.i < 4)
			paramtonum(&c);
		c.param = ft_strsplit(c.obt[c.i], ',');
		if (arr_counter(c.param, 1) != 1)
			return (0);
		c.i = ft_atoi(c.param[1]);
		node_filler(2, c.allnum, 3, c.i, obj);
		delet_table(c.param);
		delet_table(c.obt);
		return (1);
	}
	return (0);
}