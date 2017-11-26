#include<linux/module.h>   //for all of modules this library is needed
#include<linux/kernel.h>   // this library is needed for kernel's info



int init_module(void){
	printk(KERN_INFO "Hello World!\n");  //  This line print Hello World in dmesg
	return 0;
}
void cleanup_module(void){
	printk(KERN_INFO "GoodBye World!\n");//This line print Goodbye World in dmesg
}

