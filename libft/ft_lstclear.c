/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucotte <jlucotte@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 13:26:03 by jlucotte          #+#    #+#             */
/*   Updated: 2026/10/18 11:45:05 by jlucotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*curr;
	t_list	*next;

	if (lst == NULL)
		return ;
	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		curr->next = NULL;
		ft_lstdelone(curr, del);
		curr = next;
	}
	*lst = NULL;
}
