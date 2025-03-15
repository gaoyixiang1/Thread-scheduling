#include "task.h"
#include "analog_interrupt.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include "init.h"  

typedef struct {
    void (*func)(void *args);
    void *args;
    int priority;
} TaskInfo;


// 比较函数，用于按优先级排序
int compare_priority(const void *a, const void *b)
{
    TaskInfo *taskA = (TaskInfo *)a;
    TaskInfo *taskB = (TaskInfo *)b;
    return taskB->priority - taskA->priority;  // 从大到小排序
}



// 定义任务函数
void test(void *args)
{
    printf("task1 start:----------\n");
    task_exit(current_task);
}
void test1(void *args)
{
    printf("task2 start:----------\n");
    task_exit(current_task);
}

void test2(void *args)
{
    printf("task3 start:----------\n");
    task_exit(current_task);
}
void test3(void *args)
{
    printf("task4 start:----------\n");
    task_exit(current_task);
}

void test4(void *args)
{
    printf("task5 start:----------\n");
    task_exit(current_task);
}
void test5(void *args)
{
    printf("task6 start:----------\n");
    task_exit(current_task);
}



int main()
{
    init();

    TaskInfo tasks[] = {
        {test1, NULL, 31},   // task1
        {test2, NULL, 2},    // task2
        {test3, NULL, 22} ,   // task3
        {test4, NULL, 10}  ,  // task4
        {test5, NULL, 28}    // task5
    };
    int num_tasks = sizeof(tasks) / sizeof(tasks[0]);



    qsort(tasks, num_tasks, sizeof(TaskInfo), compare_priority);

   
    // 启动任务
    for (int i = 0; i < num_tasks; i++)
    {
        task_start("task", tasks[i].priority, tasks[i].func, tasks[i].args);
    }

    // 打印当前任务信息
    print_task_info(current_task);
    struct task_struct *ptask;
    ptask = tid2task(2);
    print_task_info(ptask);
    ptask = tid2task(3);
    print_task_info(ptask);
    ptask = tid2task(4);
    print_task_info(ptask);
    ptask = tid2task(5);
    print_task_info(ptask);
    ptask = tid2task(6);
    print_task_info(ptask);

    interrupt_enable();

    while (1)
    {
        pause();
    }

    return 0;
}

