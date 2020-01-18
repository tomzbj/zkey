# zkey

简单的按键处理库, 参考了murphyzhao的FlexibleButton.

## 简介

murphyzhao的FlexibleButton是一个强大的按键处理库, 链接: https://github.com/murphyzhao/FlexibleButton. 

参考FlexibleButton实现了一个极简版, 主要不同之处:

1. 总共只需要提供两个回调函数, 一个用于读键, 一个用于执行按键操作.
2. 只定义了按下, 短按弹起, 长按弹起这三个事件. 多数简单应用其实有这三个就足够了.
3. 长按阈值为全局设置. (FlexibleButton的每个键可以设置不同的阈值.)

## 使用方法

两个回调函数如下, 这里用PA2和PA3两个GPIO作为按键:

    // 读键
    static int key_read(int key_id)
    {
        unsigned short keys[2] = {GPIO_Pin_2, GPIO_Pin_3};
        if((GPIOA->IDR & keys[key_id]) == 0)
            return 1;
        else
            return 0;
    }

    // 按键事件处理
    static void key_action(int key_id, zk_action_t action)
    {
        if(action == ZK_LONGPRESS) {
            switch(key_id) {
                case 0: printf("key1 longpressed.\n"); break;
                case 1: printf("key2 longpressed.\n"); break;
            }
        }
        if(action == ZK_PRESS) {
            switch(key_id) {
                case 0: printf("key1 press\n"); break;
                case 1: printf("key2 press\n"); break;
            }
        }
        if(action == ZK_CLICK) {
            switch(key_id) {
                case 0: printf("key1 click\n"); break;
                case 1: printf("key2 click\n"); break;
            }
        }
    }

初始化:

    void KEY_Config(void)
    {
        zk_t zk;
        static int count[2];        // 按键计数器, 用户提供
        static int state[2];        // 按键状态记录, 用户提供
        zk.read_f = key_read;
        zk.action_f = key_action;
        zk.key_num = 2;
        zk.key_count = count;
        zk.key_state = state;
        zk.longpress_count = 300;   // 长按阈值为300ms (zt_poll()每1ms执行一次的话)
        zk_init(&zk);
    }

轮询: 每1ms执行一次zk_poll()即可. 如果按键响应处理耗时较长, 则不要放在SysTick中断中执行, 可以用其他调度器来调度zk_poll().    
    
