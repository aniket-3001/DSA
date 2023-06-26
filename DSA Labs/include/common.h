#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <sys/time.h>

#define MAX_LEN 16
#define MAX_MSG_LEN 128
#define MSG_SCALE (7.0 / 22.0)
#define PI (22.0 / 7.0)
#define INVALID_STATUS (-1)
#define MAX_PARTITION 3


struct trie_node;
struct list_posts;
struct list_records;

struct location {
  double lat;
  double lon;
};

struct record {
  /* character string terminated with '\0'
   * maximum length is 16
   */
  char name[MAX_LEN];
  /* a character array of 16 characters
   * not-necessarily terminated with '\0'
   * a uid may contain multiple '\0''s
   * anywhere in the character array
   */
  char uid[MAX_LEN];

  int age;

  /* used for verification */
  int verify;

  /* location */
  struct location loc;

  /* list of posts */
  struct list_posts *posts;

  /* list of friends */
  struct list_records *friends;

  /* needed for shortest Path */
  int status;
  struct record *pred;
  double distance;

  /* needed for the tree data-structure */
  int height;
  struct record *left;
  struct record *right;
  struct record *parent;
};

#define DELETED 1
#define POSTED  2

struct list_events {
  int action;
  struct record *record;
  struct list_events *next;
};

struct trie_node {
  char val;
  /*child is the first child of trie node */
  struct trie_node *child;
  /* next is the right sibling of a trie node */
  struct trie_node *next;

  /* parent of this trie node */
  struct trie_node *parent;

  /* If the current trie node is last character
   * of a messagae, history is the list of all the events
   * which took place on the message (i.e., post or delete).
   * The list elements are organized in the order in which the
   * events took place. The first element contains the most 
   * recent event.
   */
  struct list_events *history;
};

// list of trie_nodes corresponding to messages
struct list_posts {
  struct trie_node *node;
  struct list_posts *next;
};

// list of record pointers
struct list_records {
  struct record *record;
  struct list_records *next;
};

struct heap_elem {
  struct record *r;
};

void *__mymalloc(size_t size);
void __myfree(void *ptr);
size_t __get_size(void *ptr);
void create_record(struct record *r, int seed);
void create_uid(char uid[MAX_LEN], int seed, int verify);
void create_uid_new(char uid[MAX_LEN], int seed);
void verify_size_insert(struct record *arr, int num_records);
void verify_size_delete(struct record *arr, int num_records);
void verify_memory_leak();
void start_time(struct timeval *start);
unsigned long end_time(struct timeval *start);
int create_msg(char msg[MAX_MSG_LEN], int id, int size, int iter);
void initialize_hash_tables(size_t size);
void delete_msg(int id, int size);
double distance(struct location *loc1, struct location *loc2);
void create_name(char name[MAX_LEN], int seed);
void check_array_is_sorted_by_uid(struct record *record_arr, size_t num_record, size_t chksum);
void check_array_is_sorted_by_name(struct record *record_arr, size_t num_record, size_t chksum);
void verify_chksum(struct record *record_arr, size_t num_record, size_t chksum);
size_t check_avl_property(struct record *root, int *height);
size_t check_bst_property(struct record *root);
int generate_part_uid(char uid[MAX_LEN], int idx, int part, int size);
int uid_to_idx(char uid[MAX_LEN]);
void verify_checksum_flist(size_t check_sum, struct list_records *flist);
int get_rand(int seed, int max);
void update_checksum_flist(size_t *check_sum_arr, int size, struct list_records *flist, char uid[MAX_LEN]);
void verify_memory_usage_tree(size_t size, size_t num_friends);
void print_total_allocations(int size);
size_t get_alloc_size();
int get_checksum_str(char msg[MAX_MSG_LEN]);
void verify_checksum_str(size_t *check_sum_arr, int id, size_t checksum);
void update_checksum_str(size_t *check_sum_arr, int id, size_t checksum);
void enable_pa3();
void enable_pa4();
int read_vid(char msg[MAX_MSG_LEN]);
void verify_sssp(struct record *r);
void verify_sssp1(struct record *r);
void reset_verify(struct record *r);
void check_integrity_record_arr(struct record *record_arr, int size, double checksum);
double compute_checksum_record_arr(struct record *record_arr, int size);
void check_status_and_verify(struct record *record_arr, int size);
size_t getDataSecSz(char *path);
void verify_memory_usage_graph(size_t num_friends);

#endif
