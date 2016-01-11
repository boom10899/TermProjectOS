#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);

int birthday_init(void) {
	int i = 0;
	struct birthday *person;
	for(i = 0; i < 5; i++) {
		person = kmalloc(sizeof(*person), GFP_KERNEL);
		person->day = 2+i+i;
		person->month = 1+i;
		person->year = 1995+i+i+i;

		INIT_LIST_HEAD(&person->list);
		
		list_add_tail(&person->list, &birthday_list);
	}	
	
	printk(KERN_INFO "Birthday adding\n");

	list_for_each_entry(person, &birthday_list, list) {
		printk(KERN_INFO "Add Date %d Month %d Year %d\n", person->day, person->month, person->year);
	}

	printk(KERN_INFO "Add Complete\n");

	return 0;
}

void birthday_exit(void) {
	struct birthday *person, *next;
	
	printk(KERN_INFO "Birthday removing\n");

	list_for_each_entry_safe(person, next, &birthday_list, list) {
		printk(KERN_INFO "Remove Date %d Month %d Year %d\n", person->day, person->month, person->year);
		list_del(&person->list);
		kfree(person);
	}

	printk(KERN_INFO "Remove Complete\n");
}

module_init(birthday_init);
module_exit(birthday_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linked List Sample"); 
MODULE_AUTHOR("WASSAPON");
