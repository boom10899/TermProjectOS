#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>

/* This function is called when the module is loaded. */
void dfs_tree(struct task_struct *task) {	
	struct task_struct *task_next;
	struct list_head *list;

	list_for_each(list, &task->children) {
		task_next = list_entry(list, struct task_struct, sibling);

		printk(KERN_INFO "[%d]%s(%ld)\n", task_next->pid, task_next->comm, task_next->state);
	}
}

int project_init(void) {
        printk(KERN_INFO "Loading Module\n");

        struct task_struct *task;
        struct list_head *list;

	list_for_each(list, &(init_task.children)) {
                task = list_entry(list, struct task_struct, sibling);

                printk(KERN_INFO "Children of [%d]%s(%ld)\n", task->pid, task->comm, task->state);
		dfs_tree(task);
        }     	

        return 0;
}


/* This function is called when the module is removed. */ 
void project_exit(void) {
	printk(KERN_INFO "Removing Module\n"); 
}

/* Macros for registering module entry and exit points. */ 
module_init(project_init);
module_exit(project_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Project 2 - Linux Kernel Module for Listing Tasks Part II"); 
MODULE_AUTHOR("WASSAPON");
