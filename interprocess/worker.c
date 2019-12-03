/* 
 * Operating Systems {2INCO} Practical Assignment
 * Interprocess Communication
 *
 * Sonya Zarkova (1034611)
 * Stefan van der Heijden (0910541)
 *
 * Grading:
 * Students who hand in clean code that fully satisfies the minimum requirements will get an 8. 
 * Extra steps can lead to higher marks because we want students to take the initiative. 
 * Extra steps can be, for example, in the form of measurements added to your code, a formal 
 * analysis of deadlock freeness etc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>          // for perror()
#include <unistd.h>         // for getpid()
#include <mqueue.h>         // for mq-stuff
#include <time.h>           // for time()
#include <complex.h>
#include "settings.h"
#include "common.h"
#include "md5s.h"

#define STUDENT_NAME  "SS"
static void rsleep (int t);

static char                 mq_FW[MQ_MAX_MESSAGES];
static char                 mq_WF[MQ_MAX_MESSAGES];


int main (int argc, char * argv[])
{
    // TODO:
    // (see message_queue_test() in interprocess_basic.c)
    //  * open the two message queues (whose names are provided in the arguments)
    mqd_t               mq_fd_request;
    mqd_t               mq_fd_response;
    MQ_REQUEST_MESSAGE  req;
    MQ_RESPONSE_MESSAGE rsp;
    struct mq_attr      attr;

    sprintf (mq_FW, "/mq_request_%s_%d", STUDENT_NAME, getpid());
    sprintf (mq_WF, "/mq_response_%s_%d", STUDENT_NAME, getpid());

    mq_fd_request = mq_open (mq_FW, O_RDONLY | O_EXCL);
    mq_fd_response = mq_open (mq_WF, O_WRONLY | O_EXCL);


   
           
            
    
          
    //  * repeatingly:
    //      - read from a message queue the new job to do
    //      - wait a random amount of time (e.g. rsleep(10000);)
  rsleep (1000);
    //      - do that job 
    //      - write the results to a message queue
    //    until there are no more tasks to do
    //  * close the message queues 

	mq_close (mq_fd_response);
        mq_close (mq_fd_request);
    
    return (0);
}

/*
 * rsleep(int t)
 *
 * The calling thread will be suspended for a random amount of time
 * between 0 and t microseconds
 * At the first call, the random generator is seeded with the current time
 */
static void rsleep (int t)
{
    static bool first_call = true;
    
    if (first_call == true)
    {
        srandom (time (NULL) % getpid ());
        first_call = false;
    }
    usleep (random() % t);
}

