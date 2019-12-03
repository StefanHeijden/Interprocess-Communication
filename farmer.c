/* 
 * Operating Systems {2INCO} Practical Assignment
 * Interprocess Communication
 *
 * Sonya Zarkova 1034611
 * Stefan van der Heijden 0910541
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
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>    
#include <unistd.h>         // for execlp
#include <mqueue.h>         // for mq

#include "settings.h"
#include "common.h"

#define STUDENT_NAME  "SS"

static char                 mq_FW[MQ_MAX_MESSAGES];
static char                 mq_WF[MQ_MAX_MESSAGES];

int NROF_SENT_MESSAGES = 0;
int NROF_RECEIVED_MESSAGES = 0;
char JOB_CHAR = ALPHABET_START_CHAR; 


int main (int argc, char * argv[])
{
    if (argc != 1)
    {
        fprintf (stderr, "%s: invalid arguments\n", argv[0]);
    }
        
    // TODO:
    //  * create the message queues (see message_queue_test() in interprocess_basic.c)

	    pid_t               processID[NROF_WORKERS];      /* Process ID from fork() */
	    mqd_t               mq_fd_request;
	    mqd_t               mq_fd_response;
	    MQ_REQUEST_MESSAGE  req;
	    MQ_RESPONSE_MESSAGE rsp;
	    struct mq_attr      attr;

	    sprintf (mq_FW, "/mq_request_%s_%d", STUDENT_NAME, getpid());
	    sprintf (mq_WF, "/mq_response_%s_%d", STUDENT_NAME, getpid());

	    attr.mq_maxmsg  = MAX_MESSAGE_LENGTH;
	    attr.mq_msgsize = sizeof (MQ_REQUEST_MESSAGE);
	    mq_fd_request = mq_open (mq_FW, O_WRONLY | O_CREAT | O_EXCL, 0600, &attr);

	    attr.mq_maxmsg  = MAX_MESSAGE_LENGTH;
	    attr.mq_msgsize = sizeof (MQ_RESPONSE_MESSAGE);
	    mq_fd_response = mq_open (mq_WF, O_RDONLY | O_CREAT | O_EXCL, 0600, &attr);

	  
    //  * create the child processes (see process_test() and message_queue_test())

	printf ("parent pid:%d\n", getpid()); //noneed
	for (int i=0; i< NROF_WORKERS; i++){

		processID[i] = fork();

		if (processID[i] < 0)
		    {
			perror("fork() failed");
			exit (1);
		    }
		    else
		    {
			if (processID[i] == 0)
			{
			    printf ("child  pid:%d\n", getpid()); //noneed
			   execlp ("./worker", "./worker", "mq_FW" ,"mq_WF", NULL);
			   		    
			    // we should never arrive here...
			    perror ("execlp() failed");
			}
		    }
	}   

    //  * do the farming
	while(NROF_RECEIVED_MESSAGES < JOBS_NROF){   //repeat for the tottal number of jobs

   //when the num of sent messages is < than the size of the queue && the char of the job is <= the end char of the alphabet we can send messages

		if(NROF_SENT_MESSAGES < MQ_MAX_MESSAGES && JOB_CHAR <= ALPHABET_END_CHAR){  
			
			req.WORD_START_CHAR = JOB_CHAR;
			req.WORD_LENGTH = MAX_MESSAGE_LENGTH;

			mq_send(mq_fd_request, (const char *) &req, sizeof(req), 0);
			++NROF_SENT_MESSAGES;

		}
		
		mq_receive(mq_fd_response, (char *) &rsp, sizeof(rsp), NULL);
		--NROF_SENT_MESSAGES;
		++NROF_RECEIVED_MESSAGES;
	}


	
    //  * wait until the chilren have been stopped (see process_test())

 	for( int i=0; i < NROF_WORKERS; i++){
		waitpid (processID[i], NULL, 0);   // wait for the child 
		printf ("child %d has been finished\n\n", processID[i]);
	}
    //  * clean up the message queues (see message_queue_test())
	    mq_close (mq_fd_response);
            mq_close (mq_fd_request);
            mq_unlink (mq_WF);
            mq_unlink (mq_FW);  
	

    // Important notice: make sure that the names of the message queues contain your
    // student name and the process id (to ensure uniqueness during testing)
    
    return (0);
}
