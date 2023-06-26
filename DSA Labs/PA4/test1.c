#include "pa4.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage ./test1 <problem-size>\n");
    return 0;
  }
  static struct record *record_arr = NULL;
  unsigned size = atoi(argv[1]);
  unsigned i, j, k;
  struct record r;
  char uid[MAX_LEN];
  struct timeval start;
  char msg[MAX_MSG_LEN];
  size_t mem_usage;
  size_t size_msg = 0;
  double checksum;
  size_t *check_sum_arr = NULL;
  struct list_records *friends;
  struct heap_elem *heap_arr;
  int ret;
  int num_friends = 0;
  size_t data_size;

  enable_pa4();

  data_size = getDataSecSz("libpa4.so");
  if (data_size > 512) {
    printf("Too much global allocation\n");
    assert(0);
  }

  record_arr = (struct record*)malloc(size * sizeof(struct record));
  assert(record_arr);

  check_sum_arr = (size_t*)malloc(size * sizeof(size_t));
  assert(check_sum_arr);
  memset(check_sum_arr, 0, size * sizeof(size_t));

  heap_arr = (struct heap_elem*)malloc(size * sizeof(struct heap_elem));
  assert(heap_arr);

  initialize_min_heap_arr(heap_arr);

  start_time(&start);
  for (i = 0; i < size; i++) {
    create_uid_new(uid, i);
  }
  printf("Creating %d uids took %ld ms.\n", size, end_time(&start));

  start_time(&start);

  for (i = 0; i < size; i++) {
    create_record(&record_arr[i], i);
    record_arr[i].loc.lat = (0.03) * i * i;
    record_arr[i].loc.lon = (-0.02) * i * i;
  }
  printf("adding %d records took %ld ms.\n", size, end_time(&start));

  checksum = compute_checksum_record_arr(record_arr, size);

  start_time(&start);
  for (i = 0; i < size; i++) {
    for (j = 0; j < MAX_PARTITION; j++) {
      k = generate_part_uid(uid, i, j, size);
      if (k != -1) {
        ret = make_friends(&record_arr[i], &record_arr[k]);
        assert(ret == 0);
        check_sum_arr[i] += record_arr[k].uid[0];
        check_sum_arr[k] += record_arr[i].uid[0];
        num_friends += 2;
      }
    }
    j = get_rand(i, MAX_PARTITION);
    k = generate_part_uid(uid, i, j, size);
    if (k != -1) {
      ret = make_friends(&record_arr[i], &record_arr[k]);
      assert(ret == 1);
    }
  }
  printf("making %d friends took %ld ms.\n", num_friends, end_time(&start));

  start_time(&start);
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      friends = get_friends_list(&record_arr[i]);
      verify_checksum_flist(check_sum_arr[i], friends);
    }
    verify_memory_usage_graph(num_friends);
    check_status_and_verify(record_arr, size);
    check_integrity_record_arr(record_arr, size, checksum);
    compute_sssp(&record_arr[i]);
    verify_sssp(&record_arr[i]);
    assert(record_arr[i].distance == 0);
    record_arr[i].verify = 3;
    verify_sssp1(&record_arr[i]);
    reset_verify(&record_arr[i]);
  }
  printf("computing all shortest paths took %ld ms.\n", end_time(&start));

  for (i = 0; i < size; i++) {
    delete_friends_list(&record_arr[i]);
  }

  free(record_arr);
  free(check_sum_arr);
  free(heap_arr);

  verify_memory_leak();

  printf("Test-case-1 passed\n");

  return 0;
}
