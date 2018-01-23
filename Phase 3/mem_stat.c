#include <linux/module.h>  //for all kernel modules 
#include <linux/kernel.h> //for kernel_info
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/kthread.h>

struct task_struct *thread_st;
int task_page_number[10000];  //it shows the number of task's page
int change_page_number=0;
int thread_function(void* hichi){
		struct task_struct * task;
		for_each_process(task){
			if(task->mm != NULL){//it checks all of tasks even which terminated
				task_page_number[(int)task->pid] =(int)task->mm->total_vm; //set the task_page_number with a variable that is all of the pages each process allocate at first
			}
		}
		while(!kthread_should_stop()){//returns the flag that indicates the thread should run or stop
			for_each_process(task){//for on every process
				if(task->mm != NULL){
					if(task->mm->total_vm != task_page_number[(int)task->pid]){//if the number of task's pages had be changes
						change_page_number=(int)task->mm->total_vm - task_page_number[(int)task->pid];//calculate the difference of task's pages
						if(change_page_number > 0){		                
								printk(KERN_INFO"%d pages are allocated by %d ", change_page_number, task->pid);//if it has more pages than first it has been sllocated
						}
						else{
								printk(KERN_INFO"%d pages are released by %d" , -change_page_number, task->pid);//if it has less tahn first it released some pages
						}
					}
				}
			}
			ssleep(1);
		}
		return 0;
}

int __init init_thread(void){
	printk(KERN_INFO "creating thread\n");
	thread_st =kthread_run(thread_function,NULL,"mythread");//create a thread and run
	if(thread_st)
		printk(KERN_INFO"Thread created successfully\n");
	else
		printk(KERN_ERR "Thread creation failed\n");
	return 0;
}

void __exit cleanup_thread(void){
	printk(KERN_INFO "cleaning up\n");
	if(thread_st){
		kthread_stop(thread_st);//kill the thread
		printk(KERN_INFO "Thread stopped");
	}
}


MODULE_LICENSE("SABA");
module_init(init_thread);
module_exit(cleanup_thread);

