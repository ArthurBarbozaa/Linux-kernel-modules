#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{
	printk("my module - Hello World from kernel\n");
	return 0;
}

static void __exit my_exit(void)
{
	printk("my module - Goodbye Kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arthur Barboza");
MODULE_DESCRIPTION("A simple Hello World linux kernel module");
