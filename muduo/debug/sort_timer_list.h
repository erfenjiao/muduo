/*
    升序定时器链表
*/
#ifndef LST_TIMER
#define LST_TIMER

#include <time.h>
#include <netinet/in.h>
#define BUFFER_SIZE 64
class util_timer;  // 前向声明

/*
    struct sockaddr_in
  {
    __SOCKADDR_COMMON (sin_);
    in_port_t sin_port;			 Port number.  
    struct in_addr sin_addr;     Internet address.  

    // Pad to size of `struct sockaddr'. 
    unsigned char sin_zero[sizeof (struct sockaddr)
			   - __SOCKADDR_COMMON_SIZE
			   - sizeof (in_port_t)
			   - sizeof (struct in_addr)];
  };

  用户数据结构，客户端socket地址，socket文件描述符，读缓存和定时器
*/
struct client_data{
    sockaddr_in addr;
    int sockfd;
    char buf[BUFFER_SIZE];
    util_timer* timer;
};

/*
    定时器类
*/
class util_timer{
public:
    util_timer() :prev(NULL), next(NULL) {}

public:
    time_t expire;                    // 任务的超时时间
    void (*cb_func) (client_data*);   // 任务回调函数
    /*

    */
    client_data* client_data;
    util_timer* prev;
    util_timer* next;
};

/*
    定时器链表,升序，双向链表，且带有头节点和尾节点
*/
class sort_timer_list{
public:
    sort_timer_list() : head(NULL), tail(NULL) {}
    /* 链表被销毁时， 删除其中所有的定时器 */
    ~sort_timer_list() {
        util_timer* tmp = head;
        while(tmp) {
            head = tmp->next;
            delete tmp;
            tmp = head;
        }
    }

    /* 将目标定时器 timer 添加到链表中 */
    void add_timer(util_timer* timer) {
        if(!timer) {
            return ;
        }
        if(!head) {
            head = tail = timer;
            return;
        }
        /*
            如果 timer 的超时时间小于当前链表中所有定时器的超时时间，则把该定时器插入链表头部，作为链表的头节点
            否则就需要调用重载函数 add_timer(util_timer* timer, util_timer* lst_head)，插入到合适位置
        */
        if(timer->expire < head->expire){
            timer->next = head;
            head->prev = timer;
            head = timer;
            return ;
        }
        add_timer(timer, head);
    }

    /*
        当某个定时任务发生变化时，调整对应的定时器在链表中的位置。
        这个函数只考虑被调整的定时器的超时时间延长的情况，即往尾部移动
    */
    void adjust_timer(util_timer* timer) {
        if(!timer) {
            return ;
        }
        util_timer* tmp = timer->next;
        /*
            不用调整的情况：

        */
        if((timer->expire < tmp->expire) || !tmp) {
            return;
        }
        /*
            如果目标定时器是头节点，则
        */
        if(timer == head) {
            head = head->next;
            head->prev = NULL;
            timer->next =NULL;
            add_timer(timer, head);
        }
        /*
            不是头节点，则取出    
        */
        else{
            timer->prev->next = timer->next;
            timer->next->prev = timer->prev;
            add_timer(timer, timer->next);
        }
    }
    
    /*
        将目标定时器 timer 从链表中删除
    */
    void del_timer(util_timer* timer) {
        if(!timer){
            return ;
        }
        /*
            下面这个条件成立表示链表中只有一个定时器，即目标定时器
        */
        if((timer == head) && (timer == tail)) {
            delete timer;
            head = NULL;
            tail = NULL;
            return ;
        }
        /*
            如果链表中至少有两个定时器，且目标定时器是头节点，
            则将链表的
        */

        
        /*
            如果链表中至少有两个定时器，且目标定时器是尾节点
        */

        /*
            如果处于中间
        */

    }



    /*  */
    void del_timer(util_timer* timer){
        if(!timer){
            return ;
        }
        if((timer == head) && (timer == tail)){
            delete timer;
            head = NULL;
            tail = NULL;
            return ;
        }
        if( timer == head) {

        }
        if(timer == tail) {

        }

    }

    /*

    */
    void tick(){
        if(!head) {
            return;
        }

    }


private:
    /*
        一个重要的辅助函数，被公有的函数和函数调用，该函数表示将目标定时器 timer 添加到节点 lst_head 之后的部分链表中
    */
   void add_timer(util_timer* timer, util_timer* lst_head) {
        util_timer* prev = lst_head;
        util_timer* tmp  = prev->next; 
        while(tmp) {
            if(timer->expire < tmp->expire){
                prev->next  = timer;
                timer->next = tmp;
                tmp->prev   = timer;
                timer->prev = prev;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        /* */
        if(!tmp) {
            prev->next  = timer;
            timer->prev = prev;
            timer->next = NULL;
            tail        = timer;
        }
   }

private:
    util_timer* head;
    util_timer* tail;
};

#endif