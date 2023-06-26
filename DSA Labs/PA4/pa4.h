#ifndef __PA1_H__
#define __PA1_H__

#include "../include/common.h"

void initialize_min_heap_arr(struct heap_elem *arr);
struct list_records* get_friends_list(struct record *r);
int make_friends(struct record *r1, struct record *r2);
void compute_sssp(struct record *r);
void delete_friends_list(struct record *r);

#endif
