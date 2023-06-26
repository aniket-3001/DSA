#include "pa3.h"

#define MAX_ITER 32

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Usage ./test1 <problem-size>\n");
		return 0;
	}
	static struct record *record_arr = NULL;
	unsigned size = atoi(argv[1]);
	unsigned i, j;
	struct record r;
	char uid[MAX_LEN];
	struct timeval start;
	char msg[MAX_MSG_LEN];
	size_t mem_usage;
	size_t size_msg = 0;
	size_t checksum = 0;
	int ret, vid, iter;
	size_t *vid_arr = NULL;

	enable_pa3();
	record_arr = (struct record*)malloc(size * sizeof(struct record));
	assert(record_arr);

	vid_arr = (size_t*)malloc(size * sizeof(size_t));
	assert(vid_arr);
	memset(vid_arr, 0, size * sizeof(size_t));

	start_time(&start);
	for (i = 0; i < size; i++) {
		create_uid_new(uid, i);
	}
	printf("Creating %d uids took %ld ms.\n", size, end_time(&start));

	start_time(&start);

	for (i = 0; i < size; i++) {
		create_record(&record_arr[i], i);
	}
	printf("adding %d records took %ld ms.\n", size, end_time(&start));

	start_time(&start);

	mem_usage = get_alloc_size();

	for (j = 0; j < MAX_ITER; j++) {
		for (i = 0; i < size; i++) {
			vid = create_msg(msg, i, size, j);
			assert(vid < size);
			size_msg += strlen(msg);
			post_a_msg(msg, &record_arr[i]);
			vid_arr[vid] += record_arr[i].uid[0];
		}
	}
	mem_usage = get_alloc_size() - mem_usage;

	if (size >= 10000 && size_msg < mem_usage) {
		printf("memory usage is too high size_msg:%zd, mem_usage:%zd\n",
				size_msg, mem_usage);
		exit(0);
	}

	printf("Inserting %d messages took %ld ms.\n", size * MAX_ITER, end_time(&start));

	start_time(&start);
	for (i = 0; i < size; i++) {
		iter = get_rand(i, MAX_ITER);
		for (j = 0; j < iter; j++) {
			ret = read_latest_post(&record_arr[i], msg);
			assert(ret == 1);
			int vid = read_vid(msg);
			ret = delete_latest_post(&record_arr[i]);
			assert(ret == 1);
			vid_arr[vid] -= record_arr[i].uid[0];
		}
	}
	printf("Deleting took %ld ms.\n", end_time(&start));

	start_time(&start);
	for (i = 0; i < size; i++) {
		vid = create_msg(msg, i, size, 0);
		struct list_events *e = get_clean_history(msg);
		checksum = 0;
		while (e != NULL) {
			checksum += e->record->uid[0];
			e = e->next;
		}
		assert(checksum == vid_arr[vid]);
	}
	printf("Clean history took %ld ms.\n", end_time(&start));

	start_time(&start);
	for (i = 0; i < size; i++) {
		delete_all_posts(&record_arr[i]);
	}
	printf("Deleting all took %ld ms.\n", end_time(&start));
	free(record_arr);
	free(vid_arr);
	destroy_trie();

	verify_memory_leak();

	printf("Test-case-3 passed\n");

	return 0;
}
