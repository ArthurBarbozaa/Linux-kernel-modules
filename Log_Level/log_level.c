#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{
	printk(KERN_INFO "log level - this is a info\n");
	printk(KERN_WARNING "log level - this is a warning\n");
	printk(KERN_ALERT "log level - this is a alter\n");
	printk(KERN_NOTICE "log level - this is a notice\n");
	
	return 0;
}

static void __exit my_exit(void)
{
	pr_emerg("log level - module is unloaded!\n");
	pr_err("log level - error!!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arthur Barboza");
MODULE_DESCRIPTION("A example of kernel logging with printk");
