#include "../include/common.h"


// IMPLEMENTTAION of DIST

static double deg_to_rad(double deg)
{
  return (deg * PI) / 180;
}
static double rad_to_deg(double rad)
{
  return (rad * 180) / PI;
}

double distance(struct location *loc1, struct location *loc2)
{
  double dist;

  dist = (sin(deg_to_rad(loc1->lat)) * sin(deg_to_rad(loc2->lat))) +
    (cos(deg_to_rad(loc1->lat)) * cos(deg_to_rad(loc2->lat)) *
     cos(deg_to_rad(loc1->lon - loc2->lon)));
  dist = acos(dist) * 6371;
  return dist;
}

// IMPLEMENTTAION of TRIES
struct __trie_node {
  char val;
  int idx;
  struct __trie_node *child;
  struct __trie_node *next;
};

static struct __trie_node *__trie_root = NULL;
static size_t total_allocations = 0;

size_t get_alloc_size() {
  return total_allocations;
}

void print_total_allocations(int size)
{
  const size_t max_vid = (MSG_SCALE * size) + 1;
  printf("total allocations:%zd max_vid:%zd\n", total_allocations, max_vid);
}

static struct __trie_node* trie_allocate_node(char c, struct __trie_node *next)
{
  struct __trie_node *n;
  int i;

  n = (struct __trie_node*)malloc(sizeof(struct __trie_node));
  if (n == NULL) {
    printf("Out-of-memory\n");
    assert(0);
    return n;
  }

  n->val = c;
  n->child = NULL;
  n->next = next;
  return n;
}

static struct __trie_node* search_char(struct __trie_node *n, char c) {
  while (n && n->val != c) {
    n = n->next;
  }
  return n;
}

static int trie_insert(struct __trie_node *root, const char *word, int len, int idx)
{
  int i;
  struct __trie_node *n = root;
  struct __trie_node *next;
  int ret = 0;

  assert(len > 0);
  for (i = 0; i < len; i++) {
    if (!(next = search_char(n->child, word[i]))) {
      n->child = trie_allocate_node(word[i], n->child);
      next = n->child;
      ret = 1;
    }
    n = next;
  }
  if (ret) {
    n->idx = idx;
  }
  return ret;
}

static int trie_search(struct __trie_node *root, const char *word, int len)
{
  int i;
  struct __trie_node *n = root;

  assert(len > 0);
  for (i = 0; i < len && n; i++) {
    n = search_char(n->child, word[i]);
  }
  return (n == NULL) ? -1 : n->idx;
}

// IMPLEMENTTAION OF MALLOC

struct obj_header {
  size_t magic;
  size_t size;
};

#define MAGIC_VALUE 0xABCD123456ABCD

static struct obj_header* get_header(void *ptr)
{
  struct obj_header *obj = (struct obj_header*)(((char*)ptr) - sizeof(struct obj_header));
  if (obj->magic != MAGIC_VALUE) {
    printf("invalid address: %p\n", ptr);
    assert(0);
    return NULL;
  }
  return obj;
}

int pa3_enabled = 0;
void enable_pa3() {
  pa3_enabled = 1;
}

int pa4_enabled = 0;
void enable_pa4() {
  pa4_enabled = 1;
}

void *__mymalloc(size_t size)
{
  if (pa3_enabled == 1) {
    if (size != sizeof(struct trie_node) &&
        size != sizeof(struct list_posts) &&
        size != sizeof(struct list_events)) {
      printf("Allocations are only allowed for struct trie_node \
          or struct list_posts or struct list_events\n");
      assert(0);
    }
  }

  if (pa4_enabled == 1) {
    if (size != sizeof(struct list_records)) {
      printf("Allocations are only allowed for struct list_records\n");
      assert(0);
    }
  }

  struct obj_header *obj = (struct obj_header*)malloc(size + sizeof(struct obj_header));
  if (obj == NULL) {
    printf("allocation faild: size:%zd\n", size);
    return NULL;
  }
  obj->magic = MAGIC_VALUE;
  obj->size = size;
  total_allocations += size;
  return &obj[1];
}

void __myfree(void *ptr)
{
  struct obj_header *head = get_header(ptr);
  assert(total_allocations >= head->size);
  total_allocations -= head->size;
  free(head);
}

size_t __get_size(void *ptr)
{
  struct obj_header *head = get_header(ptr);
  if (head == NULL) {
    printf("unable to read size; are you not using allocate_memory API\n");
    assert(0);
  }
  return head->size;
}

void verify_size_insert(struct record *arr, int num_records)
{
  if (arr == NULL) {
    printf("record_arr null\n");
    assert(0);
  }
  size_t size = __get_size(arr) / sizeof(struct record);
  if (size < num_records) {
    printf("array size %zd * sizeof(struct record) too small for %d elements\n", 
        size, num_records);
    assert(0);
  }
  if (size >= 2 * num_records) {
    printf("array size %zd * sizeof(struct record) too large for %d elements\n", 
        size, num_records);
    assert(0);
  }
}

void verify_size_delete(struct record *arr, int num_records)
{
  if (arr == NULL) {
    printf("record_arr null\n");
    assert(0);
  }
  size_t size = __get_size(arr) / sizeof(struct record);
  if (size < num_records) {
    printf("array size %zd * sizeof(struct record) too small for %d elements\n", 
        size, num_records);
    assert(0);
  }
  if (size >= 4 * num_records) {
    printf("array size %zd * sizeof(struct record) too large for %d elements\n", 
        size, num_records);
    assert(0);
  }
}

void verify_memory_leak()
{
  if (total_allocations > 4 * sizeof(struct record)) {
    printf("%zd bytes are still allocated\n", total_allocations);
    printf("release memory that is not necessary\n");
    assert(0);
  }
}

#define MAX_RANDOM ((1ULL << 32) - 1)

static unsigned long long __seed = 0;

static unsigned __rand()
{
  __seed = (__seed * 1103515245 + 12345) & MAX_RANDOM;
  return (unsigned)__seed;
}

static char __names[][MAX_LEN] =
{
  "Sonpari", "Kroor", "Hobo", "Swami",
  "Maya", "Tulsi", "Praful", "Monisha",
  "Hansa", "Jassi", "Ramola", "Rosesh",
  "Mussadi", "Anandi", "Prem", "Hema",
  "Rekha", "Jaya", "Sushma", "Rancho",
  "Baburao", "Chatur", "Vijay", "Gabbar",
  "Pushpa", "Raj", "Gogo", "Devdas",
  "Sardar", "Omkar", "Guddu", "Munna",
  "Uday", "Chhote", "Imran", "Meera",
  "Sunder", "Rani", "Najma", "Kashi",
  "Chand", "Jai", "Veeru", "Thakur",
  "Indra", "Jaspal", "Radha", "Devaki",
  "Komolika", "Dang", "Mogambo", "Kancha",
  "Raka", "Teja", "Shakal", "Jaikant",
  "Katya", "Ravi"
};

void create_name(char name[MAX_LEN], int seed)
{
  __seed = seed;
  size_t const size = sizeof(__names)/sizeof(__names[0]);
  unsigned idx = __rand() % size;
  size_t len = strlen(__names[idx]);

  memcpy(name, __names[idx], len);
  name[len] = ' ';
  name[len+1] = '0' + (__rand() % 8);
  name[len+2] = '0' + (__rand() % 8);
  name[len+3] = '0' + (__rand() % 8);
  name[len+4] = '0' + (__rand() % 8);
  name[len+5] = '\0';
}

void create_uid(char uid[MAX_LEN], int seed, int verify)
{
  int i;
  __seed = seed;
  for (i = 0; i < MAX_LEN; i++) {
    uid[i] = __rand() % 127;
  }
  assert(!verify || trie_search(__trie_root, uid, MAX_LEN) == seed);
}

int uid_to_idx(char uid[MAX_LEN]) {
  int idx = trie_search(__trie_root, uid, MAX_LEN);
  assert(idx != -1);
  return idx;
}

static int fast_uid(int seed)
{
  __seed = seed;
  return __rand() % 127;
}

void create_uid_new(char uid[MAX_LEN], int seed)
{
  int i;
  __seed = seed;
  for (i = 0; i < MAX_LEN; i++) {
    uid[i] = __rand() % 127;
  }
  if (__trie_root == NULL) {
    __trie_root = trie_allocate_node('\0', NULL);
  }
  assert(trie_insert(__trie_root, uid, MAX_LEN, seed) == 1);
}

void create_record(struct record *r, int seed)
{
  memset(r, 0, sizeof(*r));
  create_name(r->name, seed);
  create_uid(r->uid, seed, 0);
  r->age = __rand() % 80;
}

void start_time(struct timeval *start)
{
  gettimeofday(start, 0);
}

unsigned long end_time(struct timeval *start)
{
  struct timeval end;
  unsigned long t;

  gettimeofday(&end, 0);
  t = ((end.tv_sec * 1000000) + end.tv_usec) - 
    ((start->tv_sec * 1000000) + start->tv_usec);
  return t/1000;
}


static char __posts[][MAX_MSG_LEN] =
{
  "All I know it's a mental hospital.",
  "Obey protocol, do you understand?",
  "Absolutely.",
  "What the heck did you do.",
  "Whathever can happen will happen.",
  "All work and no play makes Jack a dull boy.",
  "Maybe some kind of signal? I don't know.",
  "Carpe diem.",
  "There is no science without experiment.",
  "I don’t want to survive. I want to live.",
  "Take a seat.",
  "What about college?",
  "And things are getting better.",
  "We switched on the tractor.",
  "I have spoken.",
  "Earth is a planet.",
  "Don't underestimate the power of a common man.",
  "This is the way.",
  "Let's get out of here.",
  "This crew represents the best of humanity.",
  "It's gravity.",
  "I like those odds.",
  "I like recursion.",
  "Sit down!",
  "How many men?",
  "Weapons are the part of my religion.",
  "Do you understand this?",
  "Quick sort is a sorting algorithm.",
  "Nobody stumbles in here.",
  "There are many programming languages.",
  "It's a creed.",
  "What sort of anomaly?",
  "The training is nothing. The will is everything. The will to act.",
  "Driven by unshakable faith.",
  "Get busy living, or get busy dying.",
  "We are not meant to save the world.",
  "Mod galat nahi hote, insaan galat hote hain.",
  "Quantum physics is interesting.",
  "Not all who wander are lost.",
  "Good morning.",
  "How does an induction motor start?",
  "Hello!",
  "You are the same decaying organic matter as everything else.",
  "Nice to meet you.",
  "Even the smallest person can change the course of the future.",
  "List is a data structure.",
  "Is that a warmhole?",
  "Despair is only for those who see the end beyond all doubt.",
  "Tree is a data structure.",
  "Elementary, my dear Watson.",
  "We are a by-Product of a lifestyle obsession.",
  "Hence the bravery.",
  "My precious!",
  "A space station?",
  "If you hate a person, you hate something in him that is part of yourself.",
  "How far have you got?",
  "Just keep swimming.",
  "Out beyond ideas of wrongdoing and rightdoing there is a field. I'll meet you there.",
  "All izz well!",
  "Life was like a box of chocolates. You never know what you’re gonna get.",
  "Yesterday I was clever, so I wanted to change the world. Today I am wise, so I am changing myself.",
  "Mankind was born on earth.",
  "Don’t grieve. Anything you lose comes round in another form.",
  "You said ghost didn't exist.",
  "Silence is the language of god, all else is poor translation.",
  "Life is a race. If you don't run fast, you will be like broken anda.",
  "Be empty of worrying. Think of who created thought.",
  "Moon bada hi lool place hai.",
  "Good grammar is essential, Robin.",
  "Badges. We ain’t got no badges!",
  "Yo, Adrian.",
  "To infinity and beyond.",
  "There’s no place like home.",
  "What do you do for a living?",
  "What? Imagine that!",
  "We all wear masks.",
  "What a great idea!",
  "I'm the king of the world.",
  "Hope is a good thing, maybe the best of things. And no good thing ever dies.",
  "Houston, we have a problem.",
  "Just being honest.",
  "I found freedom. Losing all hope was freedom.",
  "We don't read and write poetry because it's cute. We read and write poetry because we are members of the human race.",
  "Come on, are you a man or an amoeba?",
  "A dream is not what you see in sleep.",  
  "Our lives are defined by opportunities, even the ones we miss.",
  "The things you own end up owning you.",
  "Don't think that I don't know that this assignment scares the hell out of you.",
};

static int get_vid(int id, int size, int iter) {
  const size_t max_vid = (MSG_SCALE * size) + 1;
  __seed = id + (iter * size);
  id = __rand() % max_vid;
  return id;
}

#define VID_LEN 8

int read_vid(char msg[MAX_MSG_LEN]) {
  int i;
  int factor = 1;
  int ret = 0;

  for (i = 0; i < VID_LEN; i++) {
    assert(msg[i] >= '0' && msg[i] <= '9');
    ret += (msg[i] - '0') * factor;
    factor *= 10;
  }
  return ret;
}

static void embed_vid(char msg[MAX_MSG_LEN], int vid) {
  int i;

  for (i = 0; i < VID_LEN; i++) {
    msg[i] = (vid % 10) + '0';
    vid = vid / 10;
  }
}

int create_msg(char msg[MAX_MSG_LEN], int id, int size, int iter)
{
  const int num_msgs = sizeof(__posts)/ sizeof(__posts[0]);
  const int max_msg_len = MAX_MSG_LEN - VID_LEN;
  int vid = get_vid(id, size, iter);
  __seed = vid;
  int i1 = __rand() % num_msgs;
  int i2 = __rand() % num_msgs;
  int i3 = __rand() % num_msgs;
  int i4 = __rand() % num_msgs;
  int i5 = __rand() % num_msgs;

  embed_vid(msg, vid);

  int len = snprintf(&msg[VID_LEN], max_msg_len, "%s %s %s %s %s",
      __posts[i1], __posts[i2], __posts[i3], __posts[i4], __posts[i5]);
  if (len >= max_msg_len) {
    len = max_msg_len - 1;
  }
  len += VID_LEN;
  assert(msg[len] == '\0');
  int i;
  for (i = len-1; i > 0; i--) {
    if (msg[i] == '!' || msg[i] == '.' || msg[i] == '?') {
      break;
    }
    msg[i] = '\0';
  }
  return vid;
}

static int __cmp_name(char *name1, char *name2)
{
  int i;

  for (i = 0; i < MAX_LEN; i++) {
    if (name1[i] == '\0' && name2[i] == '\0') {
      return 0;
    }
    if (name1[i] > name2[i]) {
      return 1;
    }
    else if (name1[i] < name2[i]) {
      return -1;
    }
  }
  assert(0);
  return 0;
}

static int __cmp_uid(char *uid1, char *uid2)
{
  int i;

  for (i = 0; i < MAX_LEN; i++) {
    if (uid1[i] > uid2[i]) {
      return 1;
    }
    else if (uid1[i] < uid2[i]) {
      return -1;
    }
  }
  return 0;
}

void check_array_is_sorted_by_name(struct record *record_arr, size_t num_record, size_t chksum)
{
  assert(record_arr != NULL);
  if (num_record == 1) {
    return;
  }
  size_t i;
  size_t check_sum = 0;
  for (i = 0; i < num_record-1; i++) {
    check_sum += record_arr[i].uid[0];
    if (__cmp_name(record_arr[i+1].name, record_arr[i].name) == -1) {
      printf("array is not sorted\n");
      assert(0);
    }
  }
  check_sum += record_arr[num_record-1].uid[0];
  if (check_sum != chksum) {
    printf("Integrity of data is violated\n");
    assert(0);
  }
}

void check_array_is_sorted_by_uid(struct record *record_arr, size_t num_record, size_t chksum)
{
  assert(record_arr != NULL);
  if (num_record == 1) {
    return;
  }
  size_t i;
  size_t check_sum = 0;
  for (i = 0; i < num_record-1; i++) {
    check_sum += record_arr[i].uid[0];
    if (__cmp_uid(record_arr[i+1].uid, record_arr[i].uid) == -1) {
      printf("array is not sorted\n");
      assert(0);
    }
  }
  check_sum += record_arr[num_record-1].uid[0];
  if (check_sum != chksum) {
    printf("Integrity of data is violated\n");
    assert(0);
  }
}

void verify_chksum(struct record *record_arr, size_t num_record, size_t chksum)
{
  size_t check_sum = 0, i;
  for (i = 0; i < num_record; i++) {
    check_sum += record_arr[i].uid[0];
  }
  if (check_sum != chksum) {
    printf("Integrity of data is violated\n");
    assert(0);
  }
}


size_t check_bst_property(struct record *root) {
  size_t check_sum = 0;
  if (root != NULL) {
    char *cur_uid = root->uid;
    char *left_uid = (root->left) ? root->left->uid : NULL;
    char *right_uid = (root->right) ? root->right->uid : NULL;
    check_sum += cur_uid[0];
    if (left_uid && __cmp_uid(left_uid, cur_uid) >= 0) {
      printf("ERROR: left_uid >= root_uid\n");
      assert(0);
    }

    if (right_uid && __cmp_uid(right_uid, cur_uid) <= 0) {
      printf("ERROR: left_uid >= root_uid\n");
      assert(0);
    }

    check_sum += check_bst_property(root->left);
    check_sum += check_bst_property(root->right);
  }
  return check_sum;
}

size_t check_avl_property(struct record *root, int *height) {
  int h = -1, left_height, right_height;
  size_t check_sum = 0;

  if (root != NULL) {
    char *cur_uid = root->uid;
    char *left_uid = (root->left) ? root->left->uid : NULL;
    char *right_uid = (root->right) ? root->right->uid : NULL;
    int diff;
    check_sum += cur_uid[0];

    if (left_uid && __cmp_uid(left_uid, cur_uid) >= 0) {
      printf("ERROR: left_uid >= root_uid\n");
      assert(0);
    }

    if (right_uid && __cmp_uid(right_uid, cur_uid) <= 0) {
      printf("ERROR: left_uid >= root_uid\n");
      assert(0);
    }

    check_sum += check_avl_property(root->left, &left_height);
    check_sum += check_avl_property(root->right, &right_height);
    diff = left_height - right_height;
    if (diff < -1 || diff > 1) {
      printf("left:%d right:%d\n", left_height, right_height);
      printf("ERROR: tree is not balanced\n");
      assert(0);
    }
    h = (left_height > right_height) ? left_height+1 : right_height+1;
  }
  *height = h;
  return check_sum;
}

#define MIN_FRIENDS 3

int generate_part_uid(char uid[MAX_LEN], int idx, int part, int size)
{
  assert(part < MIN_FRIENDS);
  int remaining = size - idx - 1;
  int blocks = remaining / MIN_FRIENDS;
  if (blocks == 0) {
    return -1;
  }
  int start = idx + 1 + (part * blocks);
  __seed = idx;
  int r = __rand() % blocks;
  assert(start + r < size);

  create_uid(uid, start + r, 0);
  return start + r;
}

void verify_checksum_flist(size_t check_sum, struct list_records *flist) {
  size_t csum = 0;
  while (flist) {
    csum += flist->record->uid[0];
    flist = flist->next;
  }
  if (check_sum != csum) {
    printf("Verification failed\n");
    printf("Ensure that there aren't duplicates in friend list\n");
    assert(0);
  }
}

void update_checksum_flist(size_t *check_sum_arr, int size, struct list_records *flist, char uid[MAX_LEN]) {
  size_t csum = 0;
  int idx;
  int val = uid[0];
  while (flist) {
    idx = uid_to_idx(flist->record->uid);
    if (idx == -1 || idx >= size) {
      printf("Friends list contains invalid entries\n");
    }
    assert(idx != -1);
    assert(idx < size);
    check_sum_arr[idx] -= val;
    flist = flist->next;
  }
}

int get_rand(int seed, int max) {
  __seed = seed;
  return __rand() % max;
}

void verify_memory_usage_tree(size_t size, size_t num_friends)
{
  size_t total_alloc = (size * sizeof(struct record)) + (num_friends * sizeof(struct list_records));

  if (total_allocations != total_alloc) {
    printf("expected memory allocation: %zd bytes\n", total_alloc);
    printf("actual allocations: %zd bytes\n", total_allocations);
    printf("Use allocate_memory and free_mmeory APIs to allocate and free nodes for tree\n");
    printf("Use allocate_memory and free_mmeory APIs to allocate and free nodes for the nodes in friend list\n");
    assert(0);
  }
}

int get_checksum_str(char msg[MAX_MSG_LEN]) {
  int i = 0;
  int ret = 0;
  while (msg[i] != '\0') {
    if (msg[i] >= 'A' && msg[i] <= 'Z') {
      ret += msg[i] - 'A';
    }
    else if (msg[i] >= 'a' && msg[i] <= 'z') {
      ret += msg[i] - 'a';
    }
    else {
      ret += msg[i];
    }
    i++;
  }
  return ret;
}

void verify_checksum_str(size_t *check_sum_arr, int id, size_t checksum) {
  assert(check_sum_arr[id] == checksum);
}

void update_checksum_str(size_t *check_sum_arr, int id, size_t checksum) {
  check_sum_arr[id] += checksum;
}

void verify_sssp(struct record *r)
{
  struct list_records *lr = r->friends;
  struct record *t;
  double dist;
  int visited;

  r->status = 0;

  while (lr) {
    t = lr->record;
    dist = r->distance + distance(&r->loc, &t->loc);
    assert(t->distance <= dist);
    visited = t->verify != 0;
    if (t->verify != 2) {
      t->verify = (t->distance == dist) ? 2 : 1;
    }
    if (!visited) {
      verify_sssp(t);
    }
    lr = lr->next;
  }
}

void verify_sssp1(struct record *r)
{
  struct list_records *lr = r->friends;
  struct record *t;
  int visited;

  while (lr) {
    t = lr->record;
    visited = t->verify == 3;
    assert(t->verify >= 2);
    if (t->verify == 2) {
      t->verify = 3;
    }
    if (!visited) {
      verify_sssp1(t);
    }
    lr = lr->next;
  }
}

static void verify_path(struct record *r)
{
  double dist = r->distance;
  struct record *pred = r->pred;
  while (pred != NULL) {
    dist -= distance(&pred->loc, &r->loc);
    assert(dist >= -0.1);
    r = pred;
    pred = r->pred;
  }
  assert((int)dist == 0);
}

void reset_verify(struct record *r)
{
  struct list_records *lr = r->friends;
  struct record *t;

  r->verify = 0;
  assert(r->status == 0);
  while (lr) {
    t = lr->record;
    if (t->verify != 0) {
      verify_path(t);
      reset_verify(t);
    }
    lr = lr->next;
  }
}

void check_status_and_verify(struct record *record_arr, int size)
{
  int i;
  for (i = 0; i < size; i++) {
    assert(record_arr[i].status == 0);
    assert(record_arr[i].verify == 0);
  }
}

double compute_checksum_record_arr(struct record *record_arr, int size)
{
  double ret = 0;
  int i;
  for (i = 0; i < size; i++) {
    ret += (i+1) * (record_arr[i].loc.lat + record_arr[i].loc.lon);
  }
  return ret;
}

void check_integrity_record_arr(struct record *record_arr, int size, double checksum)
{
  assert(checksum == compute_checksum_record_arr(record_arr, size));
}

void verify_memory_usage_graph(size_t num_friends)
{
  size_t total_alloc = num_friends * sizeof(struct list_records);

  if (total_allocations != total_alloc) {
    printf("expected memory allocation: %zd bytes\n", total_alloc);
    printf("actual allocations: %zd bytes\n", total_allocations);
    printf("Use allocate_memory and free_mmeory APIs to allocate and free nodes for the nodes in friend list\n");
    assert(0);
  }
}

#include <elf.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>


size_t getDataSecSz(char *path)
{
  static size_t DsecSz = 0;

  if (DsecSz != 0)
  {
    return DsecSz;
  }

  int fd = open(path, O_RDONLY);
  if (fd == -1) {
    return 0;
  }

  struct stat Statbuf;
  fstat(fd, &Statbuf);

  char *Base = mmap(NULL, Statbuf.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (Base == NULL) {
    close(fd);
    return 0;
  }

  Elf64_Ehdr *Header = (Elf64_Ehdr*)Base;

  if (Header->e_ident[0] != 0x7f
      || Header->e_ident[1] != 'E'
      || Header->e_ident[2] != 'L'
      || Header->e_ident[3] != 'F')
  {
    goto out;
  }

  int i;
  Elf64_Shdr *Shdr = (Elf64_Shdr*)(Base + Header->e_shoff);
  char *Strtab = Base + Shdr[Header->e_shstrndx].sh_offset;

  for (i = 0; i < Header->e_shnum; i++)
  {
    char *Name = Strtab + Shdr[i].sh_name;
    if (!strncmp(Name, ".data", 6))
    {
      DsecSz += Shdr[i].sh_size;
    }
    if (!strncmp(Name, ".bss", 5))
    {
      DsecSz += Shdr[i].sh_size;
    }
  }

out:
  munmap(Base, Statbuf.st_size);
  close(fd);
  return DsecSz;
}
