#include "sjf.h"

#include <stdio.h>
#include <stdlib.h>

#include "msg.h"
#include <unistd.h>

void sjf_scheduler(uint32_t current_time_ms, queue_t *rq, pcb_t **cpu_task){
    if (*cpu_task) {
      (*cpu_task)->ellapsed_time_ms += TICKS_MS;

     if((*cpu_task)->ellapsed_time_ms >= (*cpu_task)->time_ms){

       msg_t msg = {
         .pid = (*cpu_task)->pid,
         .request = PROCESS_REQUEST_DONE,
         .time_ms = current_time_ms
     };
         if (write((*cpu_task)->sockfd, &msg, sizeof(msg_t)) != sizeof(msg_t)) {
             perror("write");
         }
         free((*cpu_task));
         (*cpu_task) = NULL;
     }
    }

    if (*cpu_task == NULL) {            // If CPU is idle
        *cpu_task = dequeue_shortest_pcb(rq);
    }
}