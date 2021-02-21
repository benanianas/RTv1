/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:36:06 by moel-aza          #+#    #+#             */
/*   Updated: 2021/02/21 18:06:38 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RTv1.h"

int		check_sphere(char *tab, t_obj *obj)
{
	char	**object;
	char	**param;
	int		i;
	int		j;
	int		allnum[9];

	i = 1;
	j = 0;
	if ((ft_strncmp("sphere", tab, 6) != 0) || !(object = ft_strsplit(tab, ':')) || object[0] == NULL)
		return (0);
	if (arr_counter(object, 0) == 4)
	{
		if ((ft_strncmp("pos", object[1], 3)) || (ft_strncmp("trs", object[2], 3)) || (ft_strncmp("col", object[3], 3)) || (ft_strncmp("rad", object[4], 3)))
			return (0);
		while (i < 4)
		{
			param = ft_strsplit(object[i], ',');
			if (arr_counter(param, 1) != 3)
				return (0);
			allnum[j] = ft_atoi(param[1]);
			allnum[j + 1] = ft_atoi(param[2]);
			allnum[j + 2] = ft_atoi(param[3]);
			i++;
			j += 3;
			delet_table(param);
		}
		param = ft_strsplit(object[i], ',');
		if (arr_counter(param, 1) != 1)
			return (0);
		i = ft_atoi(param[1]);
		node_filler(2, allnum, 3, i, obj);
		delet_table(param);
		delet_table(object);
		return (1);
	}
	return (0);
}

int		check_plane(char *tab, t_obj *obj)
{
	char	**object;
	char	**param;
	int		i;
	int		j;
	int		allnum[15];

	i = 1;
	j = 0;
	if ((ft_strncmp("plane", tab, 5) != 0) || !(object = ft_strsplit(tab, ':')) || object[0] == NULL)
		return (0);
	if (arr_counter(object, 0) == 5)
	{
		if ((ft_strncmp("pos", object[1], 3)) || (ft_strncmp("trs", object[2], 3)) || (ft_strncmp("col", object[3], 3)) || (ft_strncmp("rot", object[4], 3)) || (ft_strncmp("dir", object[5], 3)))
			return (0);
		while (i < 6)
		{
			param = ft_strsplit(object[i], ',');
			if (arr_counter(param, 1) != 3)
				return (0);
			allnum[j] = ft_atoi(param[1]);
			allnum[j + 1] = ft_atoi(param[2]);
			allnum[j + 2] = ft_atoi(param[3]);
			i++;
			j += 3;
			delet_table(param);
		}
		node_filler(3, allnum, 5, 0, obj);
		delet_table(object);
		return (1);
	}
	return (0);
}

int		check_cone(char *tab, t_obj *obj)
{
	char	**object;
	char	**param;
	int		i;
	int		j;
	int		allnum[15];

	i = 1;
	j = 0;
	if ((ft_strncmp("cone", tab, 4) != 0) || !(object = ft_strsplit(tab, ':')) || object[0] == NULL)
		return (0);
	if (arr_counter(object, 0) == 6)
	{
		if ((ft_strncmp("pos", object[1], 3)) || (ft_strncmp("trs", object[2], 3)) || (ft_strncmp("col", object[3], 3)) || (ft_strncmp("rot", object[4], 3)) || (ft_strncmp("dir", object[5], 3)) || (ft_strncmp("ang", object[6], 3)))
			return (0);
		while (i < 6)
		{
			param = ft_strsplit(object[i], ',');
			if (arr_counter(param, 1) != 3)
				return (0);
			allnum[j] = ft_atoi(param[1]);
			allnum[j + 1] = ft_atoi(param[2]);
			allnum[j + 2] = ft_atoi(param[3]);
			i++;
			j += 3;
			delet_table(param);
		}
		param = ft_strsplit(object[i], ',');
		if (arr_counter(param, 1) != 1)
			return (0);
		i = ft_atoi(param[1]);
		if (i == 180)
			i = 0;
		node_filler(4, allnum, 5, i, obj);
		delet_table(param);
		delet_table(object);
		return (1);
	}
	return (0);
}

int		check_cy(char *tab, t_obj *obj)
{
	char	**object;
	char	**param;
	int		i;
	int		j;
	int		allnum[15];

	i = 1;
	j = 0;
	if ((ft_strncmp("cylinder", tab, 8) != 0) || !(object = ft_strsplit(tab, ':')) || object[0] == NULL)
		return (0);
	if (arr_counter(object, 0) == 6)
	{
		if ((ft_strncmp("pos", object[1], 3)) || (ft_strncmp("trs", object[2], 3)) || (ft_strncmp("col", object[3], 3)) || (ft_strncmp("rot", object[4], 3)) || (ft_strncmp("dir", object[5], 3)) || (ft_strncmp("rad", object[6], 3)))
			return (0);
		while (i < 6)
		{
			param = ft_strsplit(object[i], ',');
			if (arr_counter(param, 1) != 3)
				return (0);
			allnum[j] = ft_atoi(param[1]);
			allnum[j + 1] = ft_atoi(param[2]);
			allnum[j + 2] = ft_atoi(param[3]);
			i++;
			j += 3;
			delet_table(param);
		}
		param = ft_strsplit(object[i], ',');
		if (arr_counter(param, 1) != 1)
			return (0);
		i = ft_atoi(param[1]);
		node_filler(5, allnum, 5, i, obj);
		delet_table(param);
		delet_table(object);
		return (1);
	}
	return (0);
}
