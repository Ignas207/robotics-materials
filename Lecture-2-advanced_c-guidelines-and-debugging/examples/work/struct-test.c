#include <stdio.h>
#include <string.h>

#define TEXT_LEN 100

typedef struct 
{
    char text[TEXT_LEN];
    int remainingLenght;
} Message;


int main(void)
{
    Message message;
    MessageWrite("Hello", &message);


    return 0;
}

/**
 * @brief Writes the string to our ctx!
 * 
 * @param msg 
 * @param ctx 
 * @return int 
 */
int MessageWrite(char *msg, Message *ctx)
{
    if(msg != NULL)
    {
        //
    }

    // (ctx != NULL)
    // {
    //     ///
    // }

    // ctx->remainingLenght > msgLen.
}