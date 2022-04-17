#include <stdio.h>
#include <stdlib.h>
#define HEAP_S_ADD 0														//Starting address of the free space or heap
#define HEAP_SIZE  10000													//Total size of the free space or heap
#define HEAP_END_ADD HEAP_S_ADD + HEAP_SIZE - 1								//This is the address of the final block of heap space

struct Node																	//Node for allocation in the heap
{
	int size;																//size required for the allocation
	int  B_Add;
	struct Node *next;
};

struct Node * Head = NULL;													//Global declartion of the head pointer or starting pointer to NULL

/*This function will take the input interger i.e the size required for the allocation and return the base address of the the node allocated to 
from the heap*/
int Malloc_alloc(int size) {										
	int status = 0;
	int ret_val = -1;

	//for the first malloc operation in the heap																			
	if (Head == NULL && size <= HEAP_SIZE)
	{
		status = 1;
		struct Node *pointer = (struct Node *)malloc(sizeof(struct Node));
		pointer->size = size;
		pointer->B_Add = HEAP_S_ADD;
		pointer->next = NULL;
		Head = pointer;
		ret_val = Head->B_Add;
	}
	else
	{
		struct Node *nptr;
		nptr = Head;
		/*if at all starting space of the heap is freed and that free space is available for allocation which is in the range of the
		required size*/
		if (nptr->B_Add != HEAP_S_ADD && (size - 1) < nptr->B_Add)
		{
			status = 1;
			struct Node *pointer = (struct Node *)malloc(sizeof(struct Node));
			pointer->size = size;
			pointer->B_Add = HEAP_S_ADD;
			pointer->next = nptr;
			Head = pointer;
			ret_val = Head->B_Add;
		}
		/*if freed space is available after the first allocated block and that can be reused for allocation which is in the range
		of required size*/
		while (nptr->next != NULL && status == 0)
		{
			if ((nptr->B_Add + nptr->size + size - 1) < (nptr->next->B_Add))
			{
				status = 1;
				struct Node *pointer = (struct Node *)malloc(sizeof(struct Node));
				pointer->size = size;
				pointer->B_Add = nptr->B_Add + nptr->size;
				pointer->next = nptr->next;
				nptr->next = pointer;
				ret_val = pointer->B_Add;
				break;
			}
			nptr = nptr->next;
		}
		
		if ((status == 0) && ((size - 1 + nptr->B_Add + nptr->size) <= HEAP_END_ADD))
		{
			status = 1;
			struct Node *pointer = (struct Node *)malloc(sizeof(struct Node));
			pointer->size = size;
			pointer->B_Add = nptr->B_Add + nptr->size;
			pointer->next = nptr->next;
			nptr->next = pointer;
			ret_val = pointer->B_Add;
		}
	}
	if(status == 0) 
	{
		printf("NO SUFFICIENT SPACE FOR MEMORY ALLOCATION : %d \n",size) ;
		return ret_val;
	}
	else
	{
		printf("ALLOCATION SUCCESSFUL                     : %d \n",size) ;
		return ret_val ;
	}
}
void Free_dealloc(int base_add) 
{
	struct Node *ptr;
	struct Node *prev;
	ptr = Head;
	prev = NULL;
	/*base address of heap is not equal to the given base address*/
	if(Head->B_Add != base_add) 
	{
		while(ptr != NULL)
        {
            if(ptr->B_Add == base_add)
            {
                prev->next = ptr->next;
                break;
            }
            else
            {
                prev = ptr;
                ptr = ptr->next;
            }
        }
	}
    else 
    {
		Head = ptr->next;
    }
    
    if (ptr == NULL)
    {
        printf("THERE IS NO SUCH BASE ADDRESS SO DEALLOCATION FAILED \n");
    }
	else
	{
		printf("DEALLOCATION IS SUCCESSFUL OF BLOCK BASE ADDRESS : %d\n",base_add); 
	}
}
void display() 
{
	struct Node *p = Head;
	while(p != NULL) 
	{
		printf("BASE ADDRESS IS %d ",p->B_Add);
		printf("OF SIZE ----->%d \n",p->size);
		p = p->next;
	}
	printf("-------------------------------------------------------------------------------------------------------------------------\n");
}

int main() 
{
	int p1 = Malloc_alloc(2000);
	display();
	int p2 = Malloc_alloc(1000);	
	display();
	int p3 = Malloc_alloc(500);
	display();
	int p4 = Malloc_alloc(3000);	
	display();
	Free_dealloc(p3);					
	display();
	int p5 = Malloc_alloc(400);	
	display();
	Free_dealloc(p1);					
	display();
	int p6 = Malloc_alloc(1500);
	display();
	int p7 = Malloc_alloc(400);
	display();
	Free_dealloc(p2);						
	display();
	Free_dealloc(p4);					
	display();
	Free_dealloc(p5);					
	display();
	Free_dealloc(p6);					
	display();
	return 0;
}