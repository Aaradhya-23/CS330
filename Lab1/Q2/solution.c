#include <stdio.h>
#include <stdlib.h>
#include "buffer_api.h"

int main(int argc, char* argv[]) {
	if(argc != 2){
		perror("usage: ./solution <testcase number>");
		return -1;
	}
	buffer_init(atoi(argv[1]));
	const struct ring_buffer *rb = buffer_get_base();

	/* ------ YOUR CODE ENDS HERE ------*/
	
	/* print formats */
	// printf("0x%...."); // to print sample addresses
	// printf("number of lost records: %....");
	// printf("unknown size: %....");

	if(!rb){
		return -1;
	}

	u64 tail = rb->data_tail;
	u64 head = rb->data_head;
	u64 size = rb->data_size;
	char* base = rb->data_base;

	u64 lost_cnt = 0;
	u64 find_size = 0;

	while(tail < head){
		u64 pos = tail & (size-1);
		struct perf_event_header *hdr = (struct perf_event_header*)(base + pos);
		if(hdr -> type == PERF_RECORD_SAMPLE){
			struct sample_event *ev = (struct sample_event*)hdr;
		       printf("0x%lx\n",ev->addr);	
		}
		else if(hdr->type == PERF_RECORD_LOST){
			struct lost_event *rl = (struct lost_event*)hdr;
			lost_cnt += rl->lost;
		}
		else{
			find_size += hdr->size;
		}
		tail += hdr->size;
	}
	printf("number of lost records: %lu\n", lost_cnt);
	printf("unknown size: %lu\n", find_size);
	buffer_exit();
	return 0;
}

