/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/sched.h>

/* This function is called when the module is loaded. */
int simple_init(void)
{
	struct task_struct *task;
	printk(KERN_INFO "Loading pcbSimple\n");
	/*loop through task struct linked list and print pid, process name, state, and one more*/
	for_each_process(task){
		//print the name
		if(strlen(task->comm) < 8)
			printk("%s \t\t", task->comm);
		else
			printk("%s \t", task->comm);
		//print pid
		printk("%d \t", task->pid);
		//print the state
		printk("%ld \t", task->state);
		//print one more
		printk("%d \n", task->flags);
	}

	return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
	printk(KERN_INFO "Removing Module pcbSimple\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module to print PCB block");
MODULE_AUTHOR("Nathaniel Taylor");

