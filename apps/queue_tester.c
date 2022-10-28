#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <queue.h>

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
// outputs 0 when running correctly, -1 when an error occurs
void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue/Dequeue simple */
void test_queue_simple(void)
{
	int data = 3, *ptr;
	queue_t q;

	fprintf(stderr, "*** TEST enqueue and dequeue ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);
}



// Functions to pass in for func in test_iterator functions
static void iterator_inc(queue_t q, void *data)
{
    int *a = (int*)data;

    if (*a == 42)
        queue_delete(q, data);
    else
        *a += 1;
}
/////////////////////////////////////////////

void test_iterator(void)
{

    fprintf(stderr, "*** TEST queue_iterate ***\n");

    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
    size_t i;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Increment every item of the queue, delete item '42' */
    queue_iterate(q, iterator_inc);
    assert(data[0] == 2);
    assert(queue_length(q) == 9);

    TEST_ASSERT(data[0] == 2);
    TEST_ASSERT(queue_length(q) == 9);
}

void test_destroy(void)
{
//**** Must we dequeue all items in queue before destroying? 
// Must our destroy function give an error if we try to destroy a queue with items still in it?

    fprintf(stderr, "*** TEST destroy ***\n");
    queue_t q;
    int data = 21, *ptr;

    q = queue_create();
    queue_enqueue(q, &data);
    TEST_ASSERT(queue_destroy(q) == -1);

    queue_dequeue(q, (void**)&ptr);
    TEST_ASSERT(queue_destroy(q) == 0);
}

int main(void)
{
	test_create();
	test_queue_simple();
    test_iterator();
    test_destroy();

	return 0;
}
