#ifndef __HT_H_
#define __HT_H_

#define HT_NAME_MAX 30

enum codes{
		SUCCESS = 0,
		FAILURE,
		FAILURE_NO_MEMORY,
		FAILURE_NO_DATA
};

struct ht_node {
	void *data;
	struct ht_node *next;
};

struct ht_entry {
		struct ht_node *first;
		int node_count;
};

struct ht {
		int ht_size;
		char name[HT_NAME_MAX];
		int (*ht_hash_fn)(struct ht*, void*);
		struct ht_entry ht_body[0];
};

/* API */
struct ht* ht_create(int size, int (*hash_fn)(struct ht*, void *),
				char *name);

int ht_add(struct ht *h, void *data);
struct ht_node* ht_find_first(struct ht *h, void *data);
int ht_del(struct ht *h, void *data);

#endif /* __HT_H_ */
