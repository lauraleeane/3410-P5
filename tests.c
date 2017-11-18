#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "heaplib.h"

#define HEAP_SIZE 1024
#define NUM_TESTS 24
#define NPOINTERS 100

// TODO: Add test descriptions as you add more tests...
const char* test_descriptions[] = {
    /* our SPEC tests */
    /* 0 */ "single init, should return without error",
    /* 1 */ "single init then single alloc, should pass",
    /* 2 */ "single alloc which should fail b/c heap is not big enough",
    /* 3 */ "multiple allocs, verifying no hard-coded block limit",
    /* your SPEC tests */
    /* 4  */ "if alloc doesn't have space to make a new block, return failure",
    /* 5  */ "if block memory extends off the heap, fails",
    /* 6  */ "resizing should not affect other blocks, if it does, return failure",
    /* 7  */ "tests that alloc and ressize addresses are 8-byte alligned, if not fails",
    /* 8  */ "if there isn't enough space to resize a block, move to resize, if not fails",
    /* 9  */ "tests that contents don't change when resizing from bigger to smaller, if not failure",
    /* 10 */ "tests that contents don't change when resizing from smaller to bigger, if not failure",
    /* 11 */ "if the block is null, resize should act like an allocate",
    /* 12 */ "if the block if null, release should act like a nop",
    /* 13 */ "after a release, an allocate should be able to successfuly occur",
    /* 14 */ "if there are already five blocks, alloc should not be able to allocate a new block",
    /* 15 */ "your description here",
    /* STRESS tests */
    /* 16 */ "alloc & free, stay within heap limits",
    /* 17 */ "your description here",
    /* 18 */ "your description here",
    /* 19 */ "your description here",
    /* 20 */ "your description here",
    /* 21 */ "your description here",
    /* 22 */ "your description here",
    /* 23 */ "your description here",
};

/* ------------------ COMPLETED SPEC TESTS ------------------------- */

/* THIS TEST IS COMPLETE AND WILL NOT BE INCOPORATED INTO YOUR GRADE.
 *
 * FUNCTIONS BEING TESTED: init
 * SPECIFICATION BEING TESTED:
 * hl_init should successfully complete (without producing a seg
 * fault) for a HEAP_SIZE of 1024 or more.
 *
 * MANIFESTATION OF ERROR:
 * A basic test of hl_init.  If hl_init has an eggregious programming
 * error, this simple call would detect the problem for you by
 * crashing.
 *
 * Note: this shows you how to create a test that should succeed.
 */
int test00() {

    // simulated heap is just a big array
    char heap[HEAP_SIZE];

    hl_init(heap, HEAP_SIZE);

    return SUCCESS;
}

/* THIS TEST IS COMPLETE AND WILL NOT BE INCOPORATED INTO YOUR GRADE.
 *
 * FUNCTIONS BEING TESTED: init & alloc
 * SPECIFICATION BEING TESTED:
 * If there is room in the heap for a request for a block, hl_alloc
 * should sucessfully return a pointer to the requested block.
 *
 * MANIFESTATION OF ERROR:
 * The call to hl_alloc will return NULL if the library cannot find a
 * block for the user (even though the test is set up such that the
 * library should be able to succeed).
 */
int test01() {

    // simulated heap is just a big array
    char heap[HEAP_SIZE];

    hl_init(heap, HEAP_SIZE);

    // if this returns null, test21 returns FAILURE (==0)
    return (hl_alloc(heap, HEAP_SIZE/2) != NULL);
}

/* THIS TEST IS COMPLETE AND WILL NOT BE INCOPORATED INTO YOUR GRADE.
 *
 * FUNCTIONS BEING TESTED: init & alloc
 * SPECIFICATION BEING TESTED:
 * If there is not enough room in the heap for a request for a block,
 * hl_alloc should return NULL.
 *
 * MANIFESTATION OF ERROR:
 * This test is designed to request a block that is definitely too big
 * for the library to find. If hl_alloc returns a pointer, the library is flawed.
 *
 * Notice that heaplame's hl_alloc does NOT return NULL. (This is one
 * of many bugs in heaplame.)
 *
 * Note: this shows you how to create a test that should fail.
 *
 * Surely it would be a good idea to test this SPEC with more than
 * just 1 call to alloc, no? 
 */
int test02() {

    // simulated heap is just an array
    char heap[HEAP_SIZE];

    hl_init(heap, HEAP_SIZE);

    // if this returns NULL, test22 returns SUCCESS (==1)
    return !hl_alloc(heap, HEAP_SIZE*2);

}

/* THIS TEST IS COMPLETE AND WILL NOT BE INCOPORATED INTO YOUR GRADE.
 *
 * FUNCTIONS BEING TESTED: init & alloc
 * SPECIFICATION BEING TESTED:
 * There should be no hard-coded limit to the number of blocks heaplib
 * can support. So if the heap gets larger, so should the number of
 * supported blocks.
 *
 * MANIFESTATION OF ERROR:
 * See how many blocks are supported with heap size N. This number should
 * increase with heap size 2N. Otherwise fail!
 *
 * Note: unless it is fundamentally changed, heaplame will always fail
 * this test. That is fine. The test will have more meaning when run on
 * your heaplib.c
 */
int test03() {

    // now we simulate 2 heaps, once 2x size of the first
    char heap[HEAP_SIZE], heap2[HEAP_SIZE*2];
    int num_blocks = 0;
    int num_blocks2 = 0;

    hl_init(heap, HEAP_SIZE);

    while(true) {
        int *array = hl_alloc(heap, 8);
        if (array)
            num_blocks++;
        else
            break;
    }

    hl_init(heap2, HEAP_SIZE*2);

    while(true) {
        int *array = hl_alloc(heap2, 8);
        if (array)
            num_blocks2++;
        else
            break;
    }
#ifdef PRINT_DEBUG
    printf("%d blocks (n), then %d blocks (2n) allocated\n", num_blocks, num_blocks2);
#endif

    // hoping to return SUCCESS (==1)
    return (num_blocks2 > num_blocks);
}

/* ------------------ YOUR SPEC TESTS ------------------------- */

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
  * FUNCTIONS BEING TESTED: *hl_alloc
 * SPECIFICATION BEING TESTED: if enough space is taken up by other blocks that a new block can't be added, function should return null
 *
 *
 * MANIFESTATION OF ERROR:
 *  if hl_alloc returns a pointer, the library is flawed.
 */
int test04() {
    // simulated heap is just an array
    char heap[HEAP_SIZE];

    hl_init(heap, HEAP_SIZE);
    hl_alloc(heap, HEAP_SIZE/2+1);
    // if this returns NULL, test22 returns SUCCESS (==1)
    return !hl_alloc(heap, HEAP_SIZE/2);
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
  * FUNCTIONS BEING TESTED: hl_release, hl_alloc
 * SPECIFICATION BEING TESTED: block memory does not extend off of the heap
 *
 *
 * MANIFESTATION OF ERROR: if the block memory extends off of the heap, then there will be a memory location in 
 * one of the blocks that is greater than heap+HEAP_SIZE 
 *
 */
int test05() {
    char heap[HEAP_SIZE];

    hl_init(heap, HEAP_SIZE);
    int* first_block = hl_alloc(heap, 8);
    int* second_block = hl_alloc(heap, 8);
    //set all of the values in the second block to 10
    int i;
    for(i=0; i<8; i++){
        second_block[i]=10;
    }
    //release the first block
    hl_release(heap, first_block);
    //create a new first block, and set all of its values to 20
    int* new_first_block = hl_alloc(heap, 64);
    int j;
    new_first_block[0]=20;
    for(j=0; j<8; j++){
	new_first_block[j]=20;
    }
    //if any of the second values were changed and are no longer 10, library is faulty
    int k;
    for(k=0; k<8; k++){
	if(second_block[k]!=10){return FAILURE;}
    }
    return SUCCESS;
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
 * FUNCTIONS BEING TESTED: hl_resize
 * SPECIFICATION BEING TESTED:resizing one block does not affect the data in other blocks.
 *
 *
 * MANIFESTATION OF ERROR:if the data in one block is changed by resizing another block, the library is faulty
 *
 */
int test06() {
    char heap[HEAP_SIZE];
    hl_init(heap, HEAP_SIZE);
    int* first_block = hl_alloc(heap, 8);
    int* second_block = hl_alloc(heap, 8);
    //set all of the values in the second block to 10
    int i;
    for(i=0; i<8; i++){
        second_block[i]=10;
    }
    //resize the first block to a larger size, and fill it with 20 in each space
    hl_resize(heap, first_block, 64);
    int j;
    for (j=0; j<8; j++){
	first_block[j]=20;
    }
    //recheck the second block: if any of the values have changed, the library is faulty
    int k;
    for (k=0; k<8; k++){
	if(second_block[k]!=10){return FAILURE;}
    }
    return SUCCESS;
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
 * FUNCTIONS BEING TESTED: hl_alloc, hl_resize
 * SPECIFICATION BEING TESTED: the block that is returned is 8 byte aligned
 *
 *
 * MANIFESTATION OF ERROR: if the block is not 8-byte aligned, then the memory address will not be divisible by 8.
 *
 */
int test07() {

    char heap[HEAP_SIZE];
    hl_init(heap, HEAP_SIZE);
    int* pointer = hl_alloc(heap, 10);
    bool alloc8 = ((uintptr_t)pointer%8==0);
    int* pointer2 = hl_resize(heap, pointer,20);
    bool resize8 = ((uintptr_t)pointer2%8==0);
    if(alloc8 && resize8){return SUCCESS;} 
    return FAILURE;
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
 * FUNCTIONS BEING TESTED: resize
 * SPECIFICATION BEING TESTED: if there is not enough room in to resize a block in place, 
 * it should move the block to somewhere it can resize to. 
 *
 * MANIFESTATION OF ERROR: If the new block is resized where it should not be able to (hitting another block), it should return failure
 *
 */
int test08() {

	char heap[HEAP_SIZE];

	hl_init(heap, HEAP_SIZE);

	int* firstblock=hl_alloc(heap,8);
	int* secondblock=hl_alloc(heap,8);

	int* newfirstblock= hl_resize(heap,firstblock,16);

	int shift=0;
	if(firstblock + 8 >= secondblock){
		shift=1;
	}

	if(shift==1 && firstblock==newfirstblock){
		return FAILURE;
	}

    return SUCCESS;
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
 * FUNCTIONS BEING TESTED: resize
 * SPECIFICATION BEING TESTED: ensure contents doesn't change when resizing from smaller to bigger
 *
 *
 * MANIFESTATION OF ERROR: if the contents change, return failure
 *
 */
int test09() {

    char heap[HEAP_SIZE];

	hl_init(heap, HEAP_SIZE);

	int* block=hl_alloc(heap,8);

	int i;
	int original[8];
	for(i=0; i<8; i++){
		block[i]=rand() % 100 +1;
		original[i]=block[i];
	}

	i=0;
	int* newblock = hl_resize(heap,block,16);

	for(i=0;i<8;i++){
		if(original[i]!=newblock[i]){
			return FAILURE;
		}
	}


    return SUCCESS;
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
 * FUNCTIONS BEING TESTED: resize
 * SPECIFICATION BEING TESTED: ensure contents doesn't change when resizing from larger to smaller
 *
 *
 * MANIFESTATION OF ERROR: if the contents change, return failure
 *
 */
int test10() {

    char heap[HEAP_SIZE];

	hl_init(heap,HEAP_SIZE);

	int* block=hl_alloc(heap,24);
	int i;
	int original[24];
	for(i=0;i<24;i++){
		block[i]=rand() % 100 +1;
		original[i]=block[i];
	}
	i=0;
	int* newblock = hl_resize(heap,block,8);

	for(i=0;i<8;i++){
		if(original[i]!=newblock[i]){
			return FAILURE;
		}
	}

    return SUCCESS;
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
 * FUNCTIONS BEING TESTED: resize
 * SPECIFICATION BEING TESTED: if block is null, then resize should behave like alloc
 *
 *
 * MANIFESTATION OF ERROR: if resize does not return a block with the specified size
 *
 */
int test11() {

	char heap[HEAP_SIZE];

	hl_init(heap,HEAP_SIZE);

	int* blocknull=NULL;

	int* newblock=hl_resize(heap,blocknull,8);

    if(newblock==NULL){
        return FAILURE;
    }
	/*if(newblock.block_size!=8){
		return FAILURE;
	}*/


    return SUCCESS;
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
 * FUNCTIONS BEING TESTED: release
 * SPECIFICATION BEING TESTED: release should act like a nop if block is null
 *
 *
 * MANIFESTATION OF ERROR: if any of the previously allocated blocks change, tests fail
 *
 */
int test12() {

	char heap[HEAP_SIZE];

	hl_init(heap,HEAP_SIZE);

	int* firstblock=hl_alloc(heap,8);
	int* secondblock=hl_alloc(heap,8);
	int* thirdblock=hl_alloc(heap,8);
	int* fourthblock=hl_alloc(heap,8);
	int* fifthblock=hl_alloc(heap,8);
	int* nullblock=NULL;
	int i;
	for(i=0;i<8;i++){
		firstblock[i]=i;
		secondblock[i]=i;
		thirdblock[i]=i;
		fourthblock[i]=i;
		fifthblock[i]=i;
	}

	hl_release(heap,nullblock);

	i=0;
	for(i=0;i<8;i++){
		if(firstblock[i]!=i || secondblock[i]!=i || thirdblock[i]!=i || fourthblock[i]!=i || fifthblock[i]!=i){
			return FAILURE;
		}
	}

    return SUCCESS;
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
 * FUNCTIONS BEING TESTED: release
 * SPECIFICATION BEING TESTED: Once the heap is filled and something is released, it should be able to allocate again
 *
 *
 * MANIFESTATION OF ERROR:
 *
 */
int test13() {

	char heap[HEAP_SIZE];
	hl_init(heap,HEAP_SIZE);

	int* firstblock=hl_alloc(heap,8);
	int* secondblock=hl_alloc(heap,8);
	int* thirdblock=hl_alloc(heap,8);
	int* fourthblock=hl_alloc(heap,8);
	int* fifthblock=hl_alloc(heap,8);
	int i;
	for(i=0;i<8;i++){
		firstblock[i]=i;
		secondblock[i]=i;
		thirdblock[i]=i;
		fourthblock[i]=i;
		fifthblock[i]=i;
	}

	hl_release(heap, secondblock);

	int* newblock=hl_alloc(heap,16);

	if(newblock==NULL){
		return FAILURE;
	}


    return SUCCESS;
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
 * FUNCTIONS BEING TESTED: alloc
 * SPECIFICATION BEING TESTED: should return null if it cannot allocate the specified block
 *
 *
 * MANIFESTATION OF ERROR:
 *
 */
int test14() {
    char heap[HEAP_SIZE];

    hl_init(heap,HEAP_SIZE);

    int* blocknull=NULL;

    int* newblock=hl_resize(heap,blocknull,8);

    bool aligned=((uintptr_t)newblock%8==0);

    if(aligned){
        return SUCCESS;
    }

    return FAILURE;
}

/* Find something that you think heaplame does wrong. Make a test
 * for that thing!
 *
 * FUNCTIONS BEING TESTED:
 * SPECIFICATION BEING TESTED:
 *
 *
 * MANIFESTATION OF ERROR:
 *
 */
int test15() {

    char heap[HEAP_SIZE];
    hl_init(heap,HEAP_SIZE);

   // heap=heap+1;

#ifdef PRINT_DEBUG
    printf("%s heap\n", heap);
#endif

    int* block=hl_alloc(heap,8);
    bool aligned = ((uintptr_t)block%8==0);

    if(aligned){
        return SUCCESS;
    }


    return FAILURE;
}

/* ------------------ STRESS TESTS ------------------------- */

/* THIS TEST IS NOT FINISHED. It is a stress test, but it does not
 * actually test to see whether the library or the user writes 
 * past the heap. You are encouraged to complete this test.
 * 
 * FUNCTIONS BEING TESTED: alloc, free
 * SPECIFICATION BEING TESTED:
 * The library should not give user "permission" to write off the end
 * of the heap. Nor should the library ever write off the end of the heap.
 *
 * MANIFESTATION OF ERROR:
 * If we track the data on each end of the heap, it should never be
 * written to by the library or a good user.
 *
 */
int test16() {
    int n_tries    = 10000;
    int block_size = 16;

    // 1024 bytes of padding
    // --------------------
    // 1024 bytes of "heap"
    // --------------------  <-- heap_start
    // 1024 bytes of "padding"
    char memarea[HEAP_SIZE*3];

    char *heap_start = &memarea[1024]; // heap will start 1024 bytes in
    char *pointers[NPOINTERS];

    // zero out the pointer array
    memset(pointers, 0, NPOINTERS*sizeof(char *));

    hl_init(heap_start, HEAP_SIZE);
    srandom(0);
    for (int i = 0; i < n_tries; i++) {
        int index = random() % NPOINTERS;
        if (pointers[index] == 0) {
            pointers[index] = hl_alloc(heap_start,  block_size);
        }
        else{
            hl_release(heap_start, pointers[index]);
            pointers[index] = 0;
        }
    }
    return SUCCESS;
}

/* Stress the heap library and see if you can break it!
 *
 * FUNCTIONS BEING TESTED:
 * INTEGRITY OR DATA CORRUPTION?
 *
 * MANIFESTATION OF ERROR:
 *
 */
int test17() {

    return FAILURE;
}

/* Stress the heap library and see if you can break it!
 *
 * FUNCTIONS BEING TESTED:
 * INTEGRITY OR DATA CORRUPTION?
 *
 * MANIFESTATION OF ERROR:
 *
 */
int test18() {

    return FAILURE;
}

/* Stress the heap library and see if you can break it!
 *
 * FUNCTIONS BEING TESTED:
 * INTEGRITY OR DATA CORRUPTION?
 *
 * MANIFESTATION OF ERROR:
 *
 */
int test19() {

    return FAILURE;
}


/* Stress the heap library and see if you can break it!
 *
 * FUNCTIONS BEING TESTED:
 * INTEGRITY OR DATA CORRUPTION?
 *
 * MANIFESTATION OF ERROR:
 *
 */
int test20() {

    return FAILURE;
}


/* Stress the heap library and see if you can break it!
 *
 * FUNCTIONS BEING TESTED:
 * INTEGRITY OR DATA CORRUPTION?
 *
 * MANIFESTATION OF ERROR:
 *
 */
int test21() {

    return FAILURE;
}


/* Stress the heap library and see if you can break it!
 *
 * FUNCTIONS BEING TESTED:
 * INTEGRITY OR DATA CORRUPTION?
 *
 * MANIFESTATION OF ERROR:
 *
 */
int test22() {

    return FAILURE;
}


/* Stress the heap library and see if you can break it!
 *
 * FUNCTIONS BEING TESTED:
 * INTEGRITY OR DATA CORRUPTION?
 *
 * MANIFESTATION OF ERROR:
 *
 */
int test23() {

    return FAILURE;
}
