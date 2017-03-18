#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <assert.h>
#include <ucontext.h>
#include "tlib.h"

TCB *head = NULL;
TCB *end = NULL;
static int running = 0;
static int returnTid = 0;
static int queuedTid = 0;
static int numOfThreads = 0;
static int tids=0;


/* implementation of stub is already given below */
void stub (void (*tstartf)(void *), void *arg)
{

	 tstartf (arg); /* calling thread start function to execute */
    /*
        We are done with executing the application specified thread start
        function. Hence we can now terminate the thread
    */
	  tlib_delete_thread(TLIB_SELF);
    exit(0);
}



int tlib_init (void)
{
  // queue init edilecek
  // stack ile ilgili bişiyler?????
  // (queuedan sıradan threadler exec edilcek)
  // timer gibi bişiyle root, bir sağa kaydırılcak belirli timeın sonunda

    return (TLIB_ERROR);
}



int tlib_create_thread(void (*func)(void *), void *param)
{

		if(numOfThreads > 1024)
			return TLIB_NOMORE;
    TCB *in = (TCB*)malloc(sizeof(TCB));
		in -> context = (ucontext_t *)malloc(sizeof(ucontext_t));
		if(!in || !in->context)
      return(TLIB_NOMEMORY);

		getcontext(&in->threadContext);
		in -> context -> uc_stack.ss_sp = (char *)malloc(TLIB_MIN_STACK);
		in -> context -> uc_stack.ss_size = TLIB_MIN_STACK;
		if(!in -> context -> uc_stack.ss_sp )
		return(TLIB_NOMEMORY);
		//makecontext without using makecontext :)
		in -> tid = ++universalthread;
		numOfThreads++;

		//push to queue

    return in -> tid;
}


int tlib_yield(int wantTid)
{
    if(wantTid == root->tid || wantTid == TLIB_SELF)
    {
      //yield self :)
        return(TLIB_SELF);
    }
    TCB *temp = searchInQueue(wantTid, &root);
    if(temp)
        return(TLIB_SUCCESS);
  	return (TLIB_ERROR);
}


int tlib_delete_thread(int tid)
{
    if(tid != TLIB_SELF)
    TCB *temp = searchInQueue(tid);
    //how do we delete itself lan.
    if(temp){
      temp->prev->next = temp->next;
      temp->next->prev = temp ->prev;
      free(temp);
      return TLIB_SUCCESS;
      /*
        stackten silme???!?!?!?
      */
    }

    return (TLIB_ERROR);
}
static int lengthOfQueue(TCB *root){
  int length = 0;
  TCB *temp = root;
  while(temp){
    lenght++;
    temp = temp->next ;
  }
  return lenght;
}
static int insertToQueue(TCB* newTCB, TCB* root){
    if(!root){
        root = newTCB;
        return root -> tid;
    }
    else{
        if(root->prev->tid == TLIB_MAX_THREADS)
          return(TLIB_NOMORE);
        TCB *temp = root->prev;
        root->prev = newTCB;
        newTCB->next = root;
        temp->next = newTCB;
        newTCB->prev = temp;
        newTCB->tid = newTCB->prev->tid + 1;
        return newTCB -> tid;
    }

}
static bool deleteFromQueue(int tid, TCB *root){
  TCB *temp = root;
  while(temp){
    if(temp->tid == tid){
      //free the contents of the TCB
      return true; // delete_thread'de TLIB_SUCCESS dönecek.
    }
    temp = temp->next;
  }
  return false; //delete_thread'de TLIB_FAILED dönecek.


}
static TCB* searchInQueue(int tid, TCB *root){
 // yaşasın linear search :)
 TCB *temp = root;
 while(temp){
   if(temp->tid == tid){
     return temp; //var ise root o thread olacak TLIB_SUCCESS;
   }
   temp = temp->next;
 }
 return NULL; //yoksa TLIB_ERROR;
}
