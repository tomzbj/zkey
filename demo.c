#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <posix.h>

#include "zkey.h"

void tick_poll(void)
{
    static unsigned long old_msec;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long msec = tv.tv_usec / 1000;

    if(old_msec != msec) {
        zk_poll();
        old_msec = msec;
    }
} 

static int key_read(int key_id)
{
    if(!_kbhit())
        return 0;

    int keys[2] = {'a', 'b'}; 
    printf("%c %d\n", c, key_id);
    if(c == keys[key_id]) {
        printf("###1\n");
        return 1;
    }
    else {
        printf("###0\n");
        return 0;
    }
}

static void key_action(int key_id, zk_action_t action)
{
    if(action == ZK_CLICK) {
        switch(key_id) {
            case 0: printf("KEY0 CLICK\n"); break;
            case 1: printf("KEY1 CLICK\n"); break;
        }
    }
    if(action == ZK_LONGPRESS) {
        switch(key_id) {
            case 0: printf("KEY0 LP\n"); break;
            case 1: printf("KEY1 LP\n"); break;
        }
    }
    if(action == ZK_PRESS) {
        switch(key_id) {
            case 0: printf("KEY0 PRESS\n"); break;
            case 1: printf("KEY1 PRESS\n"); break;
        }
    }
}

void KEY_Config(void)
{
    zk_t zk;
    static int count[2];
    static int state[2];
    zk.read_f = key_read;
    zk.action_f = key_action;
    zk.key_num = 2;
    zk.key_count = count;
    zk.key_state = state;
    zk.longpress_count = 300; 
    zk_init(&zk);
}

int main(void)
{
    KEY_Config(); 
    while(1) {
        tick_poll();
        usleep(500);
    }

    return 0;
}
