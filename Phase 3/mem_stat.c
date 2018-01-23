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
			if(task->mm != NULL){
				task_page_number[(int)task->pid] =(int)task->mm->total_vm;
			}
		}
		while(!kthread_should_stop()){
			for_each_process(task){
				if(task->mm != NULL){
					if(task->mm->total_vm != task_page_number[(int)task->pid]){
						change_page_number=(int)task->mm->total_vm - task_page_number[(int)task->pid];
						if(change_page_number > 0){		                
								printk(KERN_INFO"%d pages are allocated by %d ", change_page_number, task->pid);
						}
						else{
								printk(KERN_INFO"%d pages are released by %d" , -change_page_number, task->pid);
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
	thread_st =kthread_run(thread_function,NULL,"mythread");
	if(thread_st)
		printk(KERN_INFO"Thread created successfully\n");
	else
		printk(KERN_ERR "Thread creation failed\n");
	return 0;
}

void __exit cleanup_thread(void){
	printk(KERN_INFO "cleaning up\n");
	if(thread_st){
		kthread_stop(thread_st);
		printk(KERN_INFO "Thread stopped");
	}
}


MODULE_LICENSE("SABA");
module_init(init_thread);
module_exit(cleanup_thread);

