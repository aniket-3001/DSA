#ifndef __PA3_H__
#define __PA3_H__

#include "../include/common.h"


void post_a_msg(char msg[MAX_MSG_LEN], struct record *r);
int delete_latest_post(struct record *r);
int read_latest_post(struct record *r, char msg[MAX_MSG_LEN]);
void delete_all_posts(struct record *r);
void destroy_trie();
struct list_events* get_history(char msg[MAX_MSG_LEN]);
struct list_events* get_clean_history(char msg[MAX_MSG_LEN]);

#endif
