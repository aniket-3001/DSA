#include <stdio.h>
#include "../include/common.h"
#include "pa2.h"

// don't remove these globals
static struct record *bst_root = NULL;
static struct record *avl_root = NULL;
static size_t num_bst_nodes = 0;
static size_t num_avl_nodes = 0;

// don't modify this function
struct record *get_bst_root()
{
  return bst_root;
}

// don't modify this function
struct record *get_avl_root()
{
  return avl_root;
}

// don't modify this function
// compare two uids
// return -1 if uid1 < uid2
// return 0 if uid1 == uid2
// return 1 if uid1 > uid2
static int cmp_uid(char *uid1, char *uid2)
{
  int i;

  for (i = 0; i < MAX_LEN; i++)
  {
    if (uid1[i] > uid2[i])
    {
      return 1;
    }
    else if (uid1[i] < uid2[i])
    {
      return -1;
    }
  }
  return 0;
}

// don't modify this function
// compare two records
// we assume that uid is unique and
// there can't be two records with the
// same uid
// return -1 if record1 < record2
// return 0 if record1 == record2
// return 1 if record1 > record2
static int cmp_record(struct record *r1, struct record *r2)
{
  return cmp_uid(r1->uid, r2->uid);
}

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

// Function to allocate a node
struct record *allocate_node(struct record r)
{
  struct record *newNode = allocate_memory(sizeof(struct record));
  *newNode = r;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->friends = NULL;

  return newNode;
}

struct record *find_min(struct record *root)
{
  if (root == NULL || root->left == NULL)
    return root;

  return find_min(root->left);
}

// Function to get the balance of the node of an AVL tree
int get_balance(struct record *n)
{
  int l_height = (n->left) ? n->left->height : -1;
  int r_height = (n->right) ? n->right->height : -1;
  return l_height - r_height;
}

// Function to set the height of the node of an AVL tree
void set_height(struct record *n)
{
  int l_height = (n->left) ? n->left->height : -1;
  int r_height = (n->right) ? n->right->height : -1;
  n->height = (l_height > r_height) ? l_height + 1 : r_height + 1;
}

// Function to perform an LL rotation on the node of an AVL tree
struct record *LL(struct record *n)
{
  struct record *new_root = n->left;
  n->left = new_root->right;
  new_root->right = n;
  set_height(n);
  set_height(new_root);
  return new_root;
}

// Function to perform an RL rotation on the node of an AVL tree
struct record *RL(struct record *n)
{
  struct record *mid = n->right;
  struct record *new_root = mid->left;
  n->right = new_root->left;
  mid->left = new_root->right;
  new_root->left = n;
  new_root->right = mid;
  set_height(n);
  set_height(mid);
  set_height(new_root);
  return new_root;
}

// Function to perform an LR on the node of an AVL tree
struct record *LR(struct record *n)
{
  struct record *mid = n->left;
  struct record *new_root = mid->right;
  n->left = new_root->right;
  mid->right = new_root->left;
  new_root->right = n;
  new_root->left = mid;
  set_height(mid);
  set_height(n);
  set_height(new_root);
  return new_root;
}

// Function to perform an RR on the node of an AVL tree
struct record *RR(struct record *n)
{
  struct record *new_root = n->right;
  n->right = new_root->left;
  new_root->left = n;
  set_height(n);
  set_height(new_root);
  return new_root;
}

// Function to balance nodes and perform the required rotations on the node of an AVL tree
struct record *try_rotate(struct record *n)
{
  int bal = get_balance(n);

  if (bal < -1)
  {
    bal = get_balance(n->right);

    if (bal > 0)
      n = RL(n);

    else
      n = RR(n);
  }

  else if (bal > 1)
  {
    bal = get_balance(n->left);
    if (bal < 0)
      n = LR(n);

    else
      n = LL(n);
  }
  return n;
}

// Function to insert node in BST
struct record *insert_bst(struct record *root, struct record r)
{

  if (root == NULL)
  {
    num_bst_nodes++;
    return allocate_node(r);
  }

  else
  {
    if (cmp_uid(r.uid, root->uid) < 0)
    {
      root->left = insert_bst(root->left, r);
    }
    else
    {
      root->right = insert_bst(root->right, r);
    }
  }

  return root;
}

// Function to insert node in AVL tree
struct record *insert_avl(struct record *root, struct record r)
{
  if (root == NULL)
  {
    num_avl_nodes++;
    return allocate_node(r);
  }

  else
  {
    if (cmp_uid(r.uid, root->uid) >= 0)
    {
      root->right = insert_avl(root->right, r);
    }
    else
    {
      root->left = insert_avl(root->left, r);
    }

    set_height(root);
    root = try_rotate(root);
    return root;
  }
}

struct record *del_node_bst(struct record *root, char uid[MAX_LEN])
{
}

struct record *del_node_avl(struct record *root, char uid[MAX_LEN])
{
}

// Function to search for a node in a BST
struct record search(struct record *root, char uid[MAX_LEN])
{
  if (root == NULL)
  {
    struct record dummy;
    dummy.status = -1;
    dummy.friends = NULL;
    return dummy;
  }

  if (cmp_uid(root->uid, uid) < 0)
    return search(root->right, uid);
  else if (cmp_uid(root->uid, uid) > 0)
    return search(root->left, uid);
  else
    return *root;
}

struct record *search_node(struct record *root, char uid[MAX_LEN])
{
  if (root == NULL)
    return NULL;

  if (cmp_uid(root->uid, uid) < 0)
    return search_node(root->right, uid);
  else if (cmp_uid(root->uid, uid) > 0)
    return search_node(root->left, uid);
  else
    return root;
}

void del_bst(struct record *root)
{
  if (root == NULL)
  {
    return;
  }

  del_bst(root->left);
  del_bst(root->right);

  struct list_records *ptr = root->friends;

  while (ptr != NULL)
  {
    struct list_records *curr = ptr;
    ptr = ptr->next;
    free_memory(curr);
  }
  free_memory(root);
}

// Return the total number of records in the
// BST rooted at bst_root
size_t get_num_bst_records()
{
  return num_bst_nodes;
}

// Return the total number of records in the
// AVL tree rooted at avl_root.
size_t get_num_avl_records()
{
  return num_avl_nodes;
}

// Insert record r in the BST rooted at bst_root.
void insert_record_bst(struct record r)
{
  bst_root = insert_bst(bst_root, r);
}

// Insert record r in the AVL tree rooted at avl_root.
void insert_record_avl(struct record r)
{
  avl_root = insert_avl(avl_root, r);
}

// Search the record corresponding to uid in the BST
// rooted at bst_root.
// If the record is not present, return a dummy record
// with -1 in the status field.
struct record search_record_bst(char uid[MAX_LEN])
{
  return search(bst_root, uid);
}

// The friends field in "struct record" stores the
// head of the linked list of friends of a given user.
// Return the head of the linked list of friends
// of the user with uid uid in the BST rooted at bst_root.
// If the corresponding record doesn't exist, return NULL.
struct list_records *get_friends_list_bst(char uid[MAX_LEN])
{
  struct record ret = search_record_bst(uid);
  return ret.friends;
}

// Delete the record (say n) corresponding to uid from the BST.
// Remove n from the lists of friends of other records
// and release the memory for the linked list nodes.
// Release memory for all the nodes in the list of friends of n.
// Return a copy of the value of the deleted record.
// If the record is not present, return a dummy record
// with -1 in the status field.
struct record delete_record_bst(char uid[MAX_LEN])
{
}

// Search the record corresponding to uid in the AVL tree
// rooted at avl_root.
// If the record is not present, return a dummy record
// with -1 in the status field.
struct record search_record_avl(char uid[MAX_LEN])
{
  return search(avl_root, uid);
}

// The friends field in "struct record" stores the
// head of the linked list of friends of a given user.
// Return the head of the linked list of friends
// of the user with uid uid in the AVL tree rooted at avl_root.
// If the corresponding record doesn't exist, return NULL.
struct list_records *get_friends_list_avl(char uid[MAX_LEN])
{
  struct record ret = search_record_avl(uid);
  return ret.friends;
}

// Delete the record (say n) corresponding to uid from the AVL tree.
// Remove n from the lists of friends of other records
// and release the memory for the linked list nodes.
// Release memory for all the nodes in the list of friends of n.
// Return a copy of the value of the deleted record.
// If the record is not present, return a dummy record
// with -1 in the status field.
struct record delete_record_avl(char uid[MAX_LEN])
{
}

// Release memory for all BST nodes and their lists of friends.
// Make bst_root points to an empty tree.
void destroy_bst()
{
  del_bst(bst_root);
  bst_root = NULL;
  num_bst_nodes = 0;
}

// Release memory for all AVL nodes and their lists of friends.
// Make avl_root points to an empty tree.
void destroy_avl()
{
  del_bst(avl_root);
  avl_root = NULL;
  num_avl_nodes = 0;
}

// Make users with uids uid1 and uid2 in the BST rooted at bst_root
// friends of each other if they aren't already friends.
// The friends field in "struct record" stores the
// head of the linked list of friends of a given user.
// To make the user with record A a friend of the user with record B,
// add A to B's list of friends and add B to A's list of friends.
// Return 1 if uid1 and uid2 are already friends before this call.
// Return 0 if they become friends during this call.
// Make users with uids uid1 and uid2 in the BST rooted at bst_root
// friends of each other if they aren't already friends.
// The friends field in "struct record" stores the
// head of the linked list of friends of a given user.
// To make the user with record A a friend of the user with record B,
// add A to B's list of friends and add B to A's list of friends.
// Return 1 if uid1 and uid2 are already friends before this call.
// Return 0 if they become friends during this call.
int make_friends_bst(char uid1[MAX_LEN], char uid2[MAX_LEN])
{
  struct record *r1 = search_node(bst_root, uid1);
  struct record *r2 = search_node(bst_root, uid2);

  // checking if they already are friends
  struct list_records *h1 = r1->friends;
  while (h1 != NULL)
  {
    if (h1->record == r2)
      return 1;

    h1 = h1->next;
  }

  // make them friends
  struct list_records *new_h1 = allocate_memory(sizeof(struct list_records));
  struct list_records *new_h2 = allocate_memory(sizeof(struct list_records));

  new_h1->record = r2;
  new_h1->next = r1->friends;
  r1->friends = new_h1;

  new_h2->record = r1;
  new_h2->next = r2->friends;
  r2->friends = new_h2;

  return 0;
}

int make_friends_avl(char uid1[MAX_LEN], char uid2[MAX_LEN])
{
  struct record *r1 = search_node(avl_root, uid1);
  struct record *r2 = search_node(avl_root, uid2);

  // checking if they already are friends
  struct list_records *h1 = r1->friends;
  while (h1 != NULL)
  {
    if (h1->record == r2)
      return 1;

    h1 = h1->next;
  }

  // make them friends
  struct list_records *new_h1 = allocate_memory(sizeof(struct list_records));
  struct list_records *new_h2 = allocate_memory(sizeof(struct list_records));

  new_h1->record = r2;
  new_h1->next = r1->friends;
  r1->friends = new_h1;

  new_h2->record = r1;
  new_h2->next = r2->friends;
  r2->friends = new_h2;

  return 0;
}