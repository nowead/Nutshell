/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonseo <seonseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:28:43 by seonseo           #+#    #+#             */
/*   Updated: 2023/11/04 18:22:01 by seonseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char const *set, char c)
{
	if (set == NULL)
		return (0);
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*branch;
	size_t	s1_len;
	size_t	i;
	size_t	j;
	size_t	branch_size;

	s1_len = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_is_set(set, s1[i]))
		i++;
	if (s1[i] == '\0')
		branch_size = s1_len + 1;
	else
	{
		j = s1_len - 1;
		while (j >= 0 && ft_is_set(set, s1[j]))
			j--;
		branch_size = j - i + 2;
	}
	branch = (char *)malloc(sizeof(char) * branch_size);
	if (branch == NULL)
		return (NULL);
	ft_strlcpy(branch, &s1[i], branch_size);
	return (branch);
}

// #include <stdio.h>

// int	main(void)
// {
// 	// char	str[] = "234ad23sf223232323232";
// 	// char	set[] = "32";
// 	// char	*branch;

// 	// branch = ft_strtrim(str, set);
// 	printf("%d\n", ft_is_set(NULL, 0));
// }
