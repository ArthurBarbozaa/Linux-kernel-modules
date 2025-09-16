#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>

static int major;
static size_t text_len = 0;
static char text[64];

static ssize_t my_read (struct file *filp, char __user *user_buf, size_t len, loff_t *off)
{
	int not_copied,delta,to_copy;

	if (*off >= sizeof(text))
		return 0;

	to_copy = min(len, text_len - *off);

	pr_info("MY MODULE - read is called, reading: %ld, copying %d.Off %lld\n", len, to_copy, *off);

	not_copied = copy_to_user(user_buf, &text[*off], to_copy);
	
	delta = to_copy - not_copied;

	*off += delta;

	return delta;
}

static ssize_t my_write (struct file *filp,const char __user *user_buf, size_t len, loff_t *off)
{
	int not_copied, delta, to_copy;

	to_copy = min(len,sizeof(text) - *off);

	pr_info("MY MODULE - write is called, wr: %ld, coypying %d.Off %lld\n", len, to_copy, *off);

	if (*off >= sizeof(text))
		return 0;

	not_copied =  copy_from_user(&text[*off],user_buf,to_copy);

	delta = to_copy - not_copied;

	if(not_copied)
		pr_warn("MY MODULE - could only copy %d bytes\n", delta);

	*off += delta;

	if (*off > text_len)
		text_len = *off;

	return delta;
}

int my_open (struct inode *inode, struct file *filp)
{
	pr_info("MY MODULE - File is opened\n");

	return 0;
}

int my_release (struct inode *inode, struct file *filp)
{
	pr_info("MY MODULE - file released\n");

	return 0;
}


static struct file_operations fops = {
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_release,
};

static int __init my_init(void)
{
	major = register_chrdev(0,"teste1", &fops);
	if (major < 0) {
		pr_err("teste_cdev - error registering chrdev!\n");
		return major;
	}

	pr_info("Inicializando meu modulo com Major: %d!\n", major);
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Removendo meu modulo!\n");
	unregister_chrdev(major, "teste1");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arthur Barboza");
MODULE_DESCRIPTION("My first kernel module");
