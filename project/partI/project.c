#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

/* This function is called when the module is loaded. */ 
int project_init(void)
{
	printk(KERN_INFO "Loading Module\n"); 
	
	struct task_struct *task;
	
	for_each_process(task) {
		printk(KERN_INFO "(%ld)%s[%d]\n", task->state, task->comm, task->pid);
	}
	
	return 0;
}

/* This function is called when the module is removed. */ 
void project_exit(void)
{
	printk(KERN_INFO "Removing Module\n"); 
}

/* Macros for registering module entry and exit points. */ 
module_init(project_init);
module_exit(project_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Project 2 - Linux Kernel Module for Listing Tasks"); 
MODULE_AUTHOR("WASSAPON");
