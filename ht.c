#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "ht.h"

int
__default_hash_fn(struct ht *h, void *data)
{
		int val;
		int hash_value;
		assert(h);

		val = *(int*) data;
		hash_value = val % h->ht_size;

		return hash_value;
}
		

struct ht* ht_create(int ht_size, 
				int (*hash_fn)(struct ht*, void *),
			    char *name)
{
	struct ht *h = NULL;
	int i;

	assert((ht_size > 0));

	h = malloc (sizeof(struct ht) +
		(ht_size * (sizeof(struct ht_entry))));
	if (!h)
			return NULL;

	h->ht_size = ht_size;	
	strncpy(h->name, name, HT_NAME_MAX);

	if (hash_fn) {
			h->ht_hash_fn = hash_fn;
	} else {
			h->ht_hash_fn = &__default_hash_fn;
	}

	for (i = 0; i < h->ht_size; i++) {
			h->ht_body[i].node_count = 0;
			h->ht_body[i].first = NULL;
	}

	return h;
}


int 
ht_add(struct ht *h, void *data)
{
	struct ht_node *node = NULL;
	int pos;

	assert (h);
	assert (data);
	
	node = malloc (sizeof(struct ht_node));
	if (!node)
			return FAILURE_NO_MEMORY;

	node->data = data;
	node->next = NULL;

	pos = (*h->ht_hash_fn)(h, data);
	h->ht_body[pos].node_count++;

	if (!h->ht_body[pos].first)
		h->ht_body[pos].first = node;
	else {
		// add at the beginnning
		node->next = h->ht_body[pos].first;
		h->ht_body[pos].first = node;
	}

	return SUCCESS;
}
		
struct ht_node* 
ht_find_first(struct ht *h, void *data)
{
	int pos;
	assert (h);
	assert (data);
	pos = h->ht_hash_fn (h, data);

	if (!h->ht_body[pos].first)
		return NULL;
	else
		return h->ht_body[pos].first;
}

int ht_del(struct ht *h, void *data)
{
	//TODO
	return 0;
}

