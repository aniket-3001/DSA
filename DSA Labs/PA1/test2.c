#include "pa1.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage ./test1 <problem-size>\n");
    return 0;
  }
  unsigned size = atoi(argv[1]);
  unsigned i;
  struct record r;
  char uid[MAX_LEN];
  struct timeval start;
	size_t iter;
	size_t size1 = size;
	size_t chksum = 0;

	if (size > 20000) {
		size1 = 20000;
	}

	printf("\nRunning TEST2 for %d inputs\n", size);

  start_time(&start);
  for (i = 0; i < size; i++) {
    create_uid_new(uid, i);
		chksum += uid[0];
  }
  printf("Creating %d uids took %ld ms.\n", size, end_time(&start));

  start_time(&start);
  for (i = 0; i < size; i++) {
    assert(get_num_records() == i);
    create_record(&r, i);
    insert_record(r);
  }
  assert(get_num_records() == size);
	verify_chksum(get_record_arr(), size, chksum);
  printf("adding %d records took %ld ms.\n", size, end_time(&start));

  for (i = size; i < size + 1000; i++) {
    assert(get_num_records() == size);
    create_uid(uid, i, 0);
    r = search_record_linear(uid);
    if (r.status != INVALID_STATUS) {
			printf("Set the status field to -1 if the record is not present\n");
		}
  }

  start_time(&start);
  for (i = 0; i < size1; i++) {
    create_uid(uid, ((i*13) % size), 0);
    r = search_record_linear(uid);
    assert(r.status != INVALID_STATUS);
  }

  assert(get_num_records() == size);
  printf("linear search %zd records took %ld ms.\n", size1, end_time(&start));

  start_time(&start);
  sort_records_quick();
  assert(get_num_records() == size);
	check_array_is_sorted_by_uid(get_record_arr(), size, chksum);
  printf("quick sort %d records took %ld ms.\n", size, end_time(&start));

  for (i = size; i < size + 1000; i++) {
    assert(get_num_records() == size);
    create_uid(uid, i, 0);
    r = search_record_binary(uid);
    if (r.status != INVALID_STATUS) {
			printf("Set the status field to -1 if the record is not present\n");
		}
  }

  start_time(&start);
  for (i = 0; i < size; i++) {
    create_uid(uid, ((i*23) % size), 0);
    r = search_record_binary(uid);
    assert(r.status != INVALID_STATUS);
  }

  assert(get_num_records() == size);
  printf("binary search %d records took %ld ms.\n", size, end_time(&start));

  delete_all_records();
  assert(get_num_records() == 0);
  verify_memory_leak();

  start_time(&start);
  for (i = 0; i < size; i++) {
    create_record(&r, i);
    insert_record(r);
  }
  assert(get_num_records() == size);
  printf("inserting %d records took %ld ms.\n", size, end_time(&start));

  start_time(&start);
  sort_records_merge();
  assert(get_num_records() == size);
	check_array_is_sorted_by_uid(get_record_arr(), size, chksum);
  printf("merge sort %d records took %ld ms.\n", size, end_time(&start));

  start_time(&start);
  for (i = 0; i < size; i++) {
    create_uid(uid, ((i*23) % size), 0);
    r = search_record_binary(uid);
    assert(r.status != INVALID_STATUS);
  }
  printf("binary search %d records took %ld ms.\n", size, end_time(&start));

  delete_all_records();
  assert(get_num_records() == 0);
  verify_memory_leak();

	chksum = 0;
  start_time(&start);
  for (i = 0; i < size1; i++) {
    create_record(&r, i);
    insert_record(r);
		chksum += r.uid[0];
  }
  assert(get_num_records() == size1);
  printf("inserting %zd records took %ld ms.\n", size1, end_time(&start));

  start_time(&start);
  sort_records_selection();
  assert(get_num_records() == size1);
	check_array_is_sorted_by_uid(get_record_arr(), size1, chksum);
  printf("selection sort %zd records took %ld ms.\n", size1, end_time(&start));

  start_time(&start);
  for (i = 0; i < size1; i++) {
    create_uid(uid, ((i*23) % size1), 0);
    r = search_record_binary(uid);
    assert(r.status != INVALID_STATUS);
  }
  printf("binary search %zd records took %ld ms.\n", size1, end_time(&start));

  delete_all_records();
  assert(get_num_records() == 0);
  verify_memory_leak();

	printf("TEST-2 successful\n\n");
  return 0;
}
