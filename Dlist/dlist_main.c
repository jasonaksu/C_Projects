#include "macros.h" //needs to be before any use of LOG

#include "dlist.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>



#ifdef LOG
#include "logger.h"
extern log_t logger; //the global variable logger used here. "extern" means that this variable is defined elsewhere. This makes the compiler happy, although the linker would need to find it.
#endif

int main()
{
  list *l = init();
  int i,j;

  srand(100); //set the seed of the random number generator

  int size = 1000;

  //generate random numbers between 0 and 10000 and add them to the list
  for (i=0;i<size;i+=1) {
    int num = rand()%1000;
    add_back(l,num);
  }

  //find the average of the random numbers
#ifdef LOG
  logger_reset();
#endif
  float average = 0.0f;
  for (i=0;i<size;i+=1) {
    average += get(l,i);
  }
  average/=size;

#ifdef LOG
  printf("Total steps taken for average: %d\n",logger.num_steps);
#endif

#ifdef LOG
  logger_reset();
#endif
  //find the standard deviation of the random numbers using the average
  float stddev = 0.0f;
  for (i=0;i<size;i+=1) {
    stddev += (get(l,i)-average)*(get(l,i)-average);
  }
  stddev = sqrt(stddev/size);

#ifdef LOG
  printf("Total steps taken for standard deviation: %d\n",logger.num_steps);
#endif

#ifdef LOG
  logger_reset();
#endif
  
    
  //sort the linked list using bubble sort
  for (i=size-1;i>1;i-=1) {
    for (j=0;j<i;j+=1) {
      if (get(l,j)>get(l,j+1)) {
	//swap them
	int el = get(l,j);
	set(l,j,get(l,j+1));
	set(l,j+1,el);
      }
    }
  }

#ifdef LOG
  printf("Total steps taken for sorting: %d\n",logger.num_steps);
#endif

#ifdef LOG
  logger_reset();
#endif

  //verify that the list is sorted
  for (i=0;i<size-1;i+=1) {
    if (get(l,i)>get(l,i+1)) {
      printf("List was not sorted\n");
      break;
    }
  }
#ifdef LOG
  printf("Total steps taken to verify sorting: %d\n",logger.num_steps);
#endif

#ifdef LOG
  logger_reset();
#endif

  //now remove the last size/2 elements
  for (i=0;i<size/2;i+=1) {
    remove_back(l);
  }

#ifdef LOG
  printf("Total steps taken to remove the last half of the list: %d\n",logger.num_steps);
#endif
  destroy(l);
}
