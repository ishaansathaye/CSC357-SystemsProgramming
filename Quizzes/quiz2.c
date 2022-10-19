#include <stdlib.h>
#include <stdio.h>

int *add_arr(int arr1[], int arr2[], int len1, int len2) {
	int new_len = len1 + len2;
	int *arr3 = malloc(new_len * sizeof(int));
	int temp_idx;
	for (temp_idx = 0; temp_idx < len1; temp_idx++) {
		arr3[temp_idx] = arr1[temp_idx];
	}
	for (temp_idx = 0; temp_idx < len2; temp_idx++) {
		arr3[temp_idx + len1] = arr2[temp_idx];
	}
	return arr3;
}

void test_add_arr() {
	int arr1[] = {1,2,3};
	int arr2[] = {4,5,6};
	int *arr3;
	arr3 = add_arr(arr1, arr2, 3, 3);
	int i;
	for (i = 0; i < 6; i++) {
		printf("%d ", arr3[i]);
	}
}

struct node {
	int val;
	struct node *next;
};

struct list {
	struct node *head;
};

struct node *search_node(struct list *list, int idx) {
	if ((list->head) == NULL) {
		return NULL;
	}
	struct node *curr_node;
	curr_node = list->head;
	int temp_idx = 0;
	while (temp_idx < idx && curr_node->next != NULL) {
		curr_node = curr_node->next;
		temp_idx++;
	}
	if (curr_node->next == NULL && temp_idx < idx) {
		return NULL;
	} else {
		return curr_node;
	}
}

void test_search_node() {
	struct list *list = malloc(sizeof(struct list));
	struct node *node1 = malloc(sizeof(struct node));
	struct node *node2 = malloc(sizeof(struct node));
	struct node *node3 = malloc(sizeof(struct node));
	node1->val = 1;
	node2->val = 2;
	node3->val = 3;
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	list->head = node1;

	struct node *node = search_node(list, 2);
	if (node == NULL) {
		printf("NULL");
	} else {
		printf("%d\n", node->val);
	}
}

int main() {
	test_add_arr();
	printf("\n");
	test_search_node();
	return 0;
}

