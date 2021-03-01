#ifndef _OBJ_LIST
#define _OBJ_LIST

typedef struct obj_list_node{
	void* this_obj;
	struct obj_list_node *next_obj;
} obj_list_node;

typedef struct obj_list{
	obj_list_node head;
	int obj_count;
} obj_list;

obj_list* new_list();
obj_list_node *add_obj(obj_list*, void*);
//void *top(obj_list*);
//void *next(obj_list*, )
void delete_list(obj_list*);

#endif
