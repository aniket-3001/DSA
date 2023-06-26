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
	size_t chksum = 0;

	printf("\nRunning TEST1 for %d inputs\n", size);

  start_time(&start);
  for (i = 0; i < size; i++) {
    create_uid_new(uid, i);
		chksum += uid[0];
  }
  printf("Creating %d uids took %ld ms.\n", size, end_time(&start));

  start_time(&start);
  for (i = 0; i < size; i++) {
    assert(get_num_records() == i);
    if (i > 4) {
      verify_size_insert(get_record_arr(), i);
    }
    create_record(&r, i);
    insert_record(r);
  }
  assert(get_num_records() == size);
	verify_chksum(get_record_arr(), size, chksum);
  printf("adding %d records took %ld ms.\n", size, end_time(&start));

  for (i = size; i < size + 1000; i++) {
    assert(get_num_records() == size);
    create_uid(uid, i, 0);
    r = delete_record(uid);
    if (r.status != INVALID_STATUS) {
			printf("if the record is not present: set status to -1\n");
			assert(0);
		}
  }

  start_time(&start);
  for (i = 0; i < size; i++) {
    assert(get_num_records() == size - i);
    if (i > 4) {
      verify_size_delete(get_record_arr(), size - i);
    }
    create_uid(uid, i, 0);
    r = delete_record(uid);
    assert(r.status != INVALID_STATUS);
		if (i < 1000) {
			chksum -= uid[0];
			verify_chksum(get_record_arr(), size-i-1, chksum);
		}
  }
  assert(get_num_records() == 0);
  printf("deleting %d records took %ld ms.\n", size, end_time(&start));

  verify_memory_leak();

	printf("TEST-1 successful\n\n");
  return 0;
}
