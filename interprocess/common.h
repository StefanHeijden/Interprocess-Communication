/* 
 * Operating Systems {2INCO} Practical Assignment
 * Interprocess Communication
 *
 * Contains definitions which are commonly used by the farmer and the workers
 *
 */

#ifndef COMMON_H
#define COMMON_H


// maximum size for any message in the tests
#define MAX_MESSAGE_LENGTH	6
 

// TODO: put your definitions of the datastructures here

typedef struct
{
    char A_START_CHAR;
    char A_END_CHAR;
    char WORD_START_CHAR;
    int WORD_LENGTH;
    uint128_t MD5;
} MQ_REQUEST_MESSAGE;       // would need change maybe

typedef struct
{
    
} MQ_RESPONSE_MESSAGE; //would need change maybe

#endif
