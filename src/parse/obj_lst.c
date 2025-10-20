#include <parse.h>
#include <stdlib.h>

t_object_list	*node_create(t_object_data data)
{
	t_object_list	*new;

	new = malloc(sizeof (t_object_list));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = NULL;
	return (new);
}
