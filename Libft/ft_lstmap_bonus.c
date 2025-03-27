/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oilyine- <oleg.ilyine@student42.luxembour  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:33:01 by oilyine-          #+#    #+#             */
/*   Updated: 2024/11/03 20:29:35 by oilyine-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp;
	void	*new_content;
	t_list	*new_node;

	new_list = NULL;
	tmp = lst;
	while (tmp)
	{
		new_content = f(tmp->content);
		if (new_content == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		tmp = tmp->next;
	}
	return (new_list);
}
/*
void	*double_value(void *content)
{
	int	*result;

	result = malloc(sizeof(int));
	if (result == NULL)
		return (NULL);
	*result = (*(int *)content) * 2;
	return (result);
}

void	delete_content(void *content)
{
	free(content);
}

int	main(void)
{
	t_list	*list;
	t_list	*new_list;
	t_list	*tmp;
	int		i;
	int		*value;

	list = NULL;
	int	values[] = {1, 2, 3, 4, 5};
	i = 0;
	while (i < 5)
	{
		value = malloc(sizeof(int));
		*value = values[i];
		ft_lstadd_back(&list, ft_lstnew(value));
		i++;
	}
	new_list = ft_lstmap(list, double_value, delete_content);
	tmp = new_list;
	printf("New list values:\n");
	while (tmp)
	{
		printf("%d\n", *(int *)tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&list, delete_content);
	ft_lstclear(&new_list, delete_content);
	return (0);
}
*/
