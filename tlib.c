#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <assert.h>

#include <ucontext.h>
#include "tlib.h"

Node *root;
int tlib_init (void)
{
  // queue init edilecek
  // stack ile ilgili bişiyler?????
  // (queuedan sıradan threadler exec edilcek)
  // timer gibi bişiyle root, bir sağa kaydırılcak belirli timeın sonunda

    return (TLIB_ERROR);
}

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


int tlib_create_thread(void (*func)(void *), void *param)
{
    // ?? STUB'ı eklememiz gerekiyor mu?
    Node *in = malloc(sizeof(Node));
    if(!in)
      return(TLIB_NOMEMORY);

    in -> prev = NULL;
    in -> next = NULL;
    in -> state = 0;
    in -> tid = 1;
    return insertToQueue(&in, &root); // not sure here?  sending pointers though?

    /*
        memory yoksa TLIB_NOMEMORY
        başka bi sebepten yaraılamazsa FAILURE
        yaratılınca SUCCESS
        stub stacke pushlancak,
        bi tane thread Idsi generate edilecek param kullanılabilir
        thread Id queue'ya atılcak
        threadId döndürülecek.

    */


}


int tlib_yield(int wantTid)
{
    if(wantTid == root->tid || wantTid == TLIB_SELF)
    {
      //yield self :)
        return(TLIB_SELF);
    }
    Node *temp = searchInQueue(wantTid, &root);
    if(temp)
        return(TLIB_SUCCESS);
  	return (TLIB_ERROR);
}


int tlib_delete_thread(int tid)
{
    if(tid != TLIB_SELF)
    Node *temp = searchInQueue(tid);
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
static int lengthOfQueue(Node *root){
  int length = 0;
  Node *temp = root;
  while(temp){
    lenght++;
    temp = temp->next ;
  }
  return lenght;
}
static int insertToQueue(Node* newNode, Node* root){
    if(!root){
        root = newNode;
        return root -> tid;
    }
    else{
        if(root->prev->tid == TLIB_MAX_THREADS)
          return(TLIB_NOMORE);
        Node *temp = root->prev;
        root->prev = newNode;
        newNode->next = root;
        temp->next = newNode;
        newNode->prev = temp;
        newNode->tid = newNode->prev->tid + 1;
        return newNode -> tid;
    }

}
static bool deleteFromQueue(int tid, Node *root){
  Node *temp = root;
  while(temp){
    if(temp->tid == tid){
      //free the contents of the node
      return true; // delete_thread'de TLIB_SUCCESS dönecek.
    }
    temp = temp->next;
  }
  return false; //delete_thread'de TLIB_FAILED dönecek.


}
static Node* searchInQueue(int tid, Node *root){
 // yaşasın linear search :)
 Node *temp = root;
 while(temp){
   if(temp->tid == tid){
     return temp; //var ise root o thread olacak TLIB_SUCCESS;
   }
   temp = temp->next;
 }
 return NULL; //yoksa TLIB_ERROR;
}
