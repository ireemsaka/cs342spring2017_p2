#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <assert.h>

#include <ucontext.h>
#include "tlib.h"


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
  /*
      memory yoksa TLIB_NOMEMORY
      başka bi sebepten yaraılamazsa FAILURE
      yaratılınca SUCCESS
      stub stacke pushlancak,
      bi tane thread Idsi generate edilecek param kullanılabilir
      thread Id queue'ya atılcak
      threadId döndürülecek.

  */
    return (TLIB_ERROR);
}


int tlib_yield(int wantTid)
{
    //root pointerı sağa kaydır.
  	return (TLIB_ERROR);
}


int tlib_delete_thread(int tid)
{
    /*
        stackten stubı sil.
        queuedan node'u sil

    */
    return (TLIB_ERROR);
}
