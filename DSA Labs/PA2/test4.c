#include "pa2.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usstatus ./test1 <problem-size>\n");
    return 0;
  }
  unsigned size =  atoi(argv[1]);
  unsigned i, j;
  struct record r;
  char uid[MAX_LEN];
  char fuid[MAX_LEN];
  struct timeval start;
  int height;
  size_t iter;
  size_t checkpoint;
  size_t check_sum = 0;
  size_t cs = 0;
	size_t *check_sum_arr = NULL;
	int tidx;
	struct list_records *friends;
	int ret;
	size_t total_friends_nodes = 0;

	check_sum_arr = (size_t*)malloc(size * sizeof(size_t));
	assert(check_sum_arr);
	memset(check_sum_arr, 0, size * sizeof(size_t));

  start_time(&start);
  for (i = 0; i < size; i++) {
    create_uid_new(uid, i);
  }
  printf("Creating %d uids took %ld ms.\n", size, end_time(&start));

  start_time(&start);
  checkpoint = 1;
  check_sum = 0;
  for (i = 0; i < size; i++) {
    assert(get_num_avl_records() == i);
    create_record(&r, i);
    check_sum += r.uid[0];
    insert_record_avl(r);
    if (i == checkpoint) {
      cs = check_avl_property(get_avl_root(), &height);
  		if (cs != check_sum) {
    		printf("Integrity was violated\n");
    		assert(0);
  		}
      checkpoint *= 2;
    }
  }
  cs = check_avl_property(get_avl_root(), &height);
  if (cs != check_sum) {
    printf("Integrity was violated\n");
    assert(0);
  }
  assert(get_num_avl_records() == size);
  printf("adding %d records took %ld ms.\n", size, end_time(&start));

  start_time(&start);

  for (i = 0; i < size; i++) {
    create_uid(uid, i, 0);
		for (j = 0; j < MAX_PARTITION; j++) {
			tidx = generate_part_uid(fuid, i, j, size);
			if (tidx != -1) {
				ret = make_friends_avl(uid, fuid);
				assert(ret == 0);
				check_sum_arr[i] += fuid[0];
				check_sum_arr[tidx] += uid[0];
				total_friends_nodes += 2;
			}
		}
		j = get_rand(i, MAX_PARTITION);
		tidx = generate_part_uid(fuid, i, j, size);
		if (tidx != -1) {
			ret = make_friends_avl(uid, fuid);
			assert(ret == 1);
		}
  }
  printf("making %zd friends took %ld ms.\n", total_friends_nodes, end_time(&start));

  for (i = size; i < size + 1000; i++) {
    assert(get_num_avl_records() == size);
    create_uid(uid, i, 0);
    r = delete_record_avl(uid);
    assert(r.status == -1);
  }

  start_time(&start);
  iter = 0;
  checkpoint = 1;
  for (i = 0; i < size; i+=2) {
    assert(get_num_avl_records() == size - iter);
    create_uid(uid, i, 0);
		friends = get_friends_list_avl(uid);
		verify_checksum_flist(check_sum_arr[i], friends);
		update_checksum_flist(check_sum_arr, size, friends, uid);
    r = delete_record_avl(uid);
    check_sum -= r.uid[0];
    assert(r.status != -1);
    iter++;
    if (iter == checkpoint) {
      cs = check_avl_property(get_avl_root(), &height);
      if (cs != check_sum) {
        printf("Integrity was violated\n");
        assert(0);
      }
      checkpoint *= 2;
    }
  }

  assert(get_num_avl_records() == size - iter);
  cs = check_avl_property(get_avl_root(), &height);
  if (cs != check_sum) {
    printf("Integrity was violated\n");
    assert(0);
  }
  printf("deleting %zd records took %ld ms.\n", iter, end_time(&start));

  destroy_avl();
  verify_memory_leak();

	printf("Test-case-4 passed\n");

  return 0;
}
