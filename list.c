#include <stdlib.h>
#include "list.h"

obj_list* new_list()
{
	obj_list *nw = malloc(sizeof(obj_list));

	nw->head.this_obj = NULL;	
	nw->head.next_obj = &nw->head;
	nw->obj_count = 0;

	return nw;
}

obj_list_node *add_obj(obj_list *list, void *obj)
{
	obj_list_node *nw = malloc(sizeof(obj_list_node));
	nw->this_obj = obj;
	nw->next_obj = list->head.next_obj;
	list->head.next_obj = nw;

	(list->obj_count)++;
	return nw;
}

void remove_first_node(obj_list *list)
{
	obj_list_node *temp;
	
	if (list->obj_count > 0){
		temp = list->head.next_obj->next_obj;
		free(list->head.next_obj);
		list->head.next_obj = temp;
		(list->obj_count)--;
	}
}

void delete_list(obj_list *list)
{
	while (list->obj_count > 0){
		remove_first_node(list);
	}

	free(list);
}
