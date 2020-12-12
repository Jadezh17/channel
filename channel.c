#include "channel.h"
#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <string.h>

int pipefds[2];

void channel_init(struct receiver* recv, struct sender* sender,
  size_t msg_sz)
  {
    if(recv  == NULL || sender == NULL || msg_sz == 0)
    {
      return;
    }
    //creating pipe
    int return_status;
    return_status = pipe(pipefds);
    //setting the size of each
    recv->size = msg_sz;
    sender->size = msg_sz;

    if (return_status == -1)
    {
      return;
    }
  }

void channel_get(struct receiver* channel, void* data)
{

  if(channel == NULL)
  {
    return;
  }
  // read from pipe given size, if no data it would block
  int result = read(pipefds[0], data, channel->size);
  // if result <= 0 meaning it failed to read
  if(result <=0 || data == NULL)
  {
    return;
  }

}

void channel_send(struct sender* channel, void* data)
{
  // data is nothing or channel not exist
  if(data == NULL || channel == NULL)
  {
    return;
  }
  int result = write(pipefds[1], data, channel->size);
  //if result written is less than 0
  if(result <=0)
  {
    return;
  }
}

void sender_dup(struct sender* dest, struct sender* src)
{
  //dest is the copy
  //src original
  if(dest == NULL || src == NULL)
  {
    return;
  }
  // copy the size of the sender
  size_t size = src->size;
  dest->size = size;

}

void channel_destroy(struct receiver* recv, struct sender* sender)
{
  //nothing is malloced during init
  return;
}
