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
  char name[MAX_LEN];
  struct timeval start;
	size_t iter;
	size_t size1 = size;
	size_t chksum = 0;
	int num_elem;
	int num_elem1;

	if (size > 20000) {
		size1 = 20000;
	}
	
	printf("\nRunning TEST3 for %d inputs\n", size);

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
    create_name(name, (i % size));
		name[1] = 'x';
		num_elem = get_num_records_with_name_linear(name);
		assert(num_elem == 0);
  }

  start_time(&start);
  for (i = 0; i < size1; i++) {
    assert(get_num_records() == size);
    create_name(name, ((i*13) % size));
		num_elem = get_num_records_with_name_linear(name);
    assert(num_elem > 0);
  }

  assert(get_num_records() == size);
  printf("linear search %zd records took %ld ms.\n", size1, end_time(&start));

  start_time(&start);
  rearrange_data();
  assert(get_num_records() == size);
	check_array_is_sorted_by_name(get_record_arr(), size, chksum);
  printf("quick sort %d records took %ld ms.\n", size, end_time(&start));

  for (i = size; i < size + 1000; i++) {
    assert(get_num_records() == size);
    create_name(name, i % size);
		name[1] = 'x';
		num_elem = get_num_records_with_name_binary(name);
    assert(num_elem == 0);
  }

  start_time(&start);
  for (i = 0; i < size; i++) {
    assert(get_num_records() == size);
    create_name(name, ((i*23) % size));
		num_elem = get_num_records_with_name_binary(name);
    assert(num_elem > 0);
  }

  assert(get_num_records() == size);
  printf("binary search %d records took %ld ms.\n", size, end_time(&start));

  for (i = 0; i < 1000; i++) {
    assert(get_num_records() == size);
    create_name(name, ((i*23) % size));
		num_elem = get_num_records_with_name_binary(name);
		num_elem1 = get_num_records_with_name_linear(name);
    assert(num_elem == num_elem1);
  }

  delete_all_records();
  assert(get_num_records() == 0);
  verify_memory_leak();

	printf("TEST-3 successful\n\n");
  return 0;
}
