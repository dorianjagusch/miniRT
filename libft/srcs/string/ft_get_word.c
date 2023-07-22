/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:51:12 by djagusch          #+#    #+#             */
/*   Updated: 2023/07/22 19:25:12 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_get_word(const char *str)
{
	int		i;
	int		len;
	int		flag;
	char	*word;

	i = 0;
	len = 0;
	flag = 0;
	while (str && ft_isspace(str[i]))
		i++;
	if (str && str[i] == '\"')
		flag = 1;
	else if (str && str[i] == '\'')
		flag = 2;
	while (str && str[i] && (!(str[i] == '\"' && flag == 1)
			|| !(str[i] == '\'' && flag == 2)))
		len++;
	word = ft_calloc(len + 1, sizeof(char));
	if (!str || !word)
		return (NULL);
	ft_strlcpy(word, &str[i - (len + 1)], len + 1);
	return (word);
}

int	main(void)
{
	static const char	*str[] = {"Hello",
		NULL,
		"a",
		"",
		"\'\'",
		"wieyegfrj\"eroogher\"",
		"    \"Success\n\""};
	char				*word;

	word = ft_get_word(str[0]);
	printf("%s\t%p\t%p\n", word, str[0], word);
	word = ft_get_word(str[1]);
	printf("%s\t%p\t%p\n", word, str[1], word);
	word = ft_get_word(str[2]);
	printf("%s\t%p\t%p\n", word, str[2], word);
	word = ft_get_word(str[3]);
	printf("%s\t%p\t%p\n", word, str[3], word);
	word = ft_get_word(str[4]);
	printf("%s\t%p\t%p\n", word, str[4], word);
	word = ft_get_word(str[5]);
	printf("%s\t%p\t%p\n", word, str[5], word);
	word = ft_get_word(str[6]);
	printf("%s\t%p\t%p\n", word, str[6], word);
	return (0);
}
