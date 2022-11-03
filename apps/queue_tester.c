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
    // done
	fprintf(stderr, "*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue/Dequeue */
void test_enqueue_dequeue(void)
{
    // done
	int data = 3, *ptr;
    void **ptr2 = NULL;
    char *null_test = NULL;
	queue_t q,q2;

	fprintf(stderr, "*** TEST enqueue and dequeue ***\n");

    // given test cases 
	q = queue_create();
    TEST_ASSERT(queue_dequeue(q, (void**)&ptr) == -1);
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);

    // testing NULL Inputs
    q2 = NULL;
    TEST_ASSERT(queue_enqueue(q, (void**)null_test) == -1);
    TEST_ASSERT(queue_enqueue(q2, &data) == -1);
    TEST_ASSERT(queue_dequeue(q2, (void**)&ptr2) == -1);
    queue_enqueue(q, &data);
    TEST_ASSERT(queue_dequeue(q, ptr2) == -1);
}

void test_delete(void)
{
    fprintf(stderr, "*** TEST delete ***\n");

    queue_t q1;
    q1 = NULL;
    int data = 1;
    TEST_ASSERT(queue_delete(q1, &data) == -1); 
    q1 = queue_create();
    queue_enqueue(q1, &data);
    TEST_ASSERT(queue_delete(q1, &data) == 0);

}

// Functions to pass in for func in test_iterator functions
static void iterator_mul(queue_t q, void *data)
{
    if(queue_length(q)!= 1){

        queue_delete(q, data);
    }
    else{
        int *a = (int*)data;
        *a *= 4;
    }
    
}

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

    fprintf(stderr, "*** TEST iterate ***\n");

    queue_t q,q2;
    int data[] = {1, 2, 3, 4, 5, 42, 6, 7, 8, 9};
    int data2[] = {3, 3, 3, 3, 3, 3};
    size_t i;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    q2 = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);
    for (i = 0; i < sizeof(data2) / sizeof(data2[0]); i++)
        queue_enqueue(q2, &data2[i]);

    /* Increment every item of the queue, delete item '42' */
    queue_iterate(q, iterator_inc);
    TEST_ASSERT(data[0] == 2);
    TEST_ASSERT(queue_length(q) == 9);

    // in q2 delete items until length is equal to 3, then multiply remaining items by 2
    TEST_ASSERT(queue_length(q2) == 6);
    queue_iterate(q2, iterator_mul);
    TEST_ASSERT(queue_length(q2) == 1);
    TEST_ASSERT(data2[5] == 12);
}

void test_destroy(void)
{
    // done
    fprintf(stderr, "*** TEST destroy ***\n");

    queue_t q,q2;
    int data = 21, *ptr;

    q = queue_create();
    queue_enqueue(q, &data);
    TEST_ASSERT(queue_destroy(q) == -1);

    queue_dequeue(q, (void**)&ptr);
    TEST_ASSERT(queue_destroy(q) == 0);

    q2 = NULL;
    TEST_ASSERT(queue_destroy(q2) == -1);
}

void test_length(void)
{
    // done
    fprintf(stderr, "*** TEST length ***\n");
    queue_t q,q1;
    int d1 = 4;
    char c1 = 'l', *ptr;

    q = queue_create();
    queue_enqueue(q, &d1);
    queue_enqueue(q, &c1);
    TEST_ASSERT(queue_length(q) == 2);
    queue_dequeue(q, (void**)&ptr);
    TEST_ASSERT(queue_length(q) == 1);

    q1 = NULL;
    TEST_ASSERT(queue_length(q1) == -1);

}

int main(void)
{
	test_create();
	test_enqueue_dequeue();
    test_delete();
    test_iterator();
    test_destroy();
    test_length();

	return 0;
}
