#ifndef __PA1_H__
#define __PA1_H__

#include "../include/common.h"

void insert_record(struct record r);
struct record search_record_linear(char uid[MAX_LEN]);
struct record search_record_binary(char uid[MAX_LEN]);
struct record delete_record(char uid[MAX_LEN]);
void sort_records_quick();
void sort_records_merge();
void sort_records_selection();
size_t get_num_records_with_name_linear(char name[MAX_LEN]);
void rearrange_data();
size_t get_num_records_with_name_binary(char name[MAX_LEN]);
size_t get_num_records();
void delete_all_records();
struct record *get_record_arr();

#endif
