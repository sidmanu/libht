#include "ht.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct my_data {
		int id;
		char name[20];
};


int 
main(int argc, char *argv[])
{
		struct ht *my_ht;
		struct ht_node *n; 
		int i;
		int ret;
		struct my_data a[20];

		my_ht = ht_create(5, NULL, "My HashTable");
		if (!my_ht) {
				printf("couldn't create ht!");
				exit (1);
		}

		for (i = 0; i < 20; i++) {
			a[i].id = i;
			sprintf(a[i].name, "H%d\n", i);
			ret = ht_add(my_ht, &a[i]); 
			if (ret != SUCCESS) {
					printf("Error in adding node!");
					exit(1);
			}
		}
		
		n = ht_find_first(my_ht, &a[5]);

		if (n) 
				printf("Found it!!! name: %s",
								((struct my_data *)n->data)->name);

		return 0;

}
