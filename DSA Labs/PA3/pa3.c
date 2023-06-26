#include "../include/common.h"
#include "pa3.h"
#include <stdio.h>
#include <string.h>

// don't remove these globals
static struct trie_node *trie_root = NULL;
size_t num_msgs = 0;

// don't modify this function
static void *allocate_memory(size_t size)
{
  return __mymalloc(size);
}

// don't modify this function
static void free_memory(void *ptr)
{
  __myfree(ptr);
}

// ---------------- Add your code below this line ----------------- //

// return the list that contains the history of
// events on msg.
// return NULL if the msg is not present in the trie.
struct list_events *get_history(char msg[MAX_MSG_LEN])
{
  return NULL;
}

// remove all the delete and the corresponding
// post events from the history of msg, before returning
// the head of the linked list that contains the history.
// return NULL if the msg is not present in the trie.
// For example, if the following events occur for the msg
// in the given order, where rightmost is the most recent event
// (u1, P), (u1, P), (u2, P), (u1, D), (u1, P), (u3, P), (u4, P), (u3, D), (u1, D)
// Here, u1, u2, u3 are users, P and D corresponds to post and delete
// events
// Then after the cleanup the sequence of events looks like
// (u1, P), (u2, P), (u4, P)
// Notice that the history list only contains the post events
// after the cleanup
// the order of the post events remains the same during the cleanup
struct list_events *get_clean_history(char msg[MAX_MSG_LEN])
{
  return NULL;
}

// allocate node and ReverseString are helper functions

// to make an empty trie node
struct trie_node *allocate_node()
{
  struct trie_node *node = allocate_memory(sizeof(struct trie_node));
  node->val = '\0';
  node->child = NULL;
  node->next = NULL;
  node->parent = NULL;
  node->history = NULL;
  return node;
}

// to reverse a string
void ReverseString(char *str)
{
  int len = strlen(str);
  for (int idx = 0, j = len - 1; idx < j; idx++, j--)
  {
    char temp = str[idx];
    str[idx] = str[j];
    str[j] = temp;
  }
}

// the maximum length of the '\0' terminated message
// stored in msg is MAX_MSG_LEN
// Insert the msg in the trie rooted at trie_root
// store the reference of the square node
// corresponding to the msg in the linked list r->posts,
// where r is "struct record*"
// A user can post a message several times, say k times,
// in that case r->posts contain k entries corresponding to
// the message
// r->posts is a stack. The first node in the linked-list
// r->posts corresponds to the lasted post by the user
// A square node in trie also contains the history of post and delete
// events on the corresponding message. The history is stored in
// a linked list n->history, where n is "struct trie_node*"
// n->history is also a stack. The first node in the linked
// list corresponds to the most recent event. The linked list
// node is of type struct event the contains the type of event
// and a reference to the user's record that posted or deleted
// the message
void post_a_msg(char msg[MAX_MSG_LEN], struct record *r)
{

  // creating a new square node for the message if root of our trie is not initialized
  if (trie_root == NULL)
    trie_root = allocate_node();

  struct trie_node *curr = trie_root; // initializing a pointer to keep track of the current node
  struct trie_node *prev = NULL;      // initializing a pointer to keep track of the previous node
  int idx = 0;

  while (msg[idx] != '\0')
  {
    struct trie_node *child = curr->child;

    // check whether a child node with the given character exists
    while (child != NULL)
    {
      if (child->val == msg[idx])
        break;

      prev = child;
      child = child->next;
    }

    if (child == NULL)
    {
      struct trie_node *new_node = allocate_node(); // creating a new child node in case it does not exist
      new_node->val = msg[idx];
      new_node->parent = curr;

      if (prev != NULL)
        prev->next = new_node;
      else
        curr->child = new_node;

      child = new_node;
    }

    curr = child;
    prev = NULL;
    idx++;
  }

  struct list_events *new_event = allocate_memory(sizeof(struct list_events));
  new_event->action = POSTED;
  new_event->record = r;
  new_event->next = NULL;

  if (curr->history != NULL)
    new_event->next = curr->history; // attaching the new event to the beginning of the history list

  curr->history = new_event;

  struct list_posts *new_post = allocate_memory(sizeof(struct list_posts));
  new_post->node = curr;
  new_post->next = NULL;

  if (r->posts != NULL)
    new_post->next = r->posts; // attaching the new post to the beginning of the posts list

  r->posts = new_post;
}

// delete the latest post by a given user
// the first node in linked list r->posts corresponds to
// the latest post
// To delete the latest post the first node in the r->posts
// is removed
// In addition the history of the corresponding square node
// in the trie also gets updated
// a square node also contains the history of post and delete
// events on that message. The history is stored in
// a linked list n->history, where n is "struct trie_node*"
// n->history is also a stack. The first node in the linked
// list corresponds to the most recent event. The linked list
// node is of type struct event the contains the type of event
// and a reference to the user's record that posted or deleted
// the message
// return 1 if a message was deleted
// return 0 id there is nothing to delete
int delete_latest_post(struct record *r)
{
  if (r->posts == NULL)
    return 0;

  // finding the square node corresponding to the latest post
  struct trie_node *node = r->posts->node;

  // updating history of the square node by removing the latest post event
  struct list_events *event = node->history;
  node->history = event->next;
  free_memory(event);

  // remove the first node from the list of posts
  struct list_posts *post = r->posts;
  r->posts = post->next;
  free_memory(post);

  return 1;
}

void delete_all_posts(struct record *r)
{
  while (delete_latest_post(r))
  {
    // empty loop body
  }

  r->posts = NULL;
}

// store the latest post (null terminated) by the user (r) in msg
// return 0 if there is no post by r
// return 1 if msg contains the latest post
// "struct record" contains references to square nodes of
// trie in the linked list posts
// To facilitate the finding of corresponding message from
// a trie node, a trie node contains a reference to its
// parent node, that is updated when a message is inserted
// in the trie
int read_latest_post(struct record *r, char msg[MAX_MSG_LEN])
{

  if (r->posts == NULL)
    return 0;

  struct trie_node *current_node = r->posts->node;
  int idx = 0;

  while (current_node != NULL && idx < MAX_MSG_LEN - 1)
  {
    msg[idx] = current_node->val;
    current_node = current_node->parent; // start traversing to the parent node
    idx++;
  }

  ReverseString(msg); // reverse the message string

  return 1;
}

void destroy_event_list(struct list_events *event)
{
  if (event == NULL)
    return;

  destroy_event_list(event->next);
  free_memory(event);
}

void destroy_trie_nodes(struct trie_node *node)
{
  if (node == NULL)
    return;

  destroy_trie_nodes(node->child);
  destroy_event_list(node->history); // deleting linked list of events
  free_memory(node);
  destroy_trie_nodes(node->next); // recursively deleting sibling nodes
}

// Delete all the memory allocated for the trie and
// the linked list that contains the history
void destroy_trie()
{
  destroy_trie_nodes(trie_root);
  trie_root = NULL;
}