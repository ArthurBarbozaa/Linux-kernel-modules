#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sysinfo.h>
#include <linux/mm.h>
#include <linux/seq_file.h>

static int major;
static size_t text_len = 0;
static char text[128];

ssize_t my_read (struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	struct sysinfo i;
	int not_copied, delta, to_copy;

	si_meminfo(&i);

	unsigned long total = (i.totalram << PAGE_SHIFT) >> 20;
	unsigned long mem = ((si_mem_available()) << PAGE_SHIFT) >> 20;
	unsigned long used = total - mem;
	
	text_len = snprintf(text, sizeof(text),
			"TOTAL RAM:%ldMB, USED:%ldMB, FREE:%ldMB\n",
			total, used, mem);
	
	if (*off >= text_len)
		return 0;	

	to_copy = min(len, text_len - *off);
	not_copied = copy_to_user(user_buf, &text[*off], to_copy);
	delta = to_copy - not_copied;

	*off += delta;

	return delta;
}

static const struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = my_read,
};

static int __init my_init(void)
{
	major = register_chrdev(0,"teste1", &fops);

	if (major < 0) {
		pr_err("teste1 - Error registering the module\n");
		return major;
	}
	
	pr_info("teste1 - Initializing my module! Major:%d\n", major);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("My module is unloaded\n");
	unregister_chrdev(major,"teste1");
}

module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arthur Barboza");
MODULE_DESCRIPTION("Memory information kernel module");
