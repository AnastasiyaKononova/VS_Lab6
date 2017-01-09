#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/timer.h>
#include <linux/fs.h>
#define DELAY 3
#define TEXT "Hello, world!"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kononova_Anastasiya");

static unsigned long time = 0;
static unsigned char is_exists_timer = 0;

static int init_func_time(void);
static void exit_func_time(void);

static ssize_t func_show_time(struct kobject *, struct kobj_attribute *, char *);
static ssize_t func_store_time(struct kobject *, struct kobj_attribute *, const char *, size_t);

static struct timer_list list_timer;

static struct kobject *kobj_time = NULL;

static void func_write_text(unsigned long);

static struct kobj_attribute attribute_time =
    __ATTR(inter, 0664, func_show_time, func_store_time);



static ssize_t func_show_time(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf, "%lu\n", time);
}

static ssize_t func_store_time(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
    if (kstrtoul(buf, 10, &time) == -EINVAL) {
        return -EINVAL;
    }

    if (is_exists_timer) {
        del_timer(&list_timer);
    }

    list_timer.data = time;
    list_timer.function = func_write_text;
    list_timer.expires = jiffies + DELAY * HZ;

    is_exists_timer = 1;

    add_timer(&list_timer);

    return count;
}

static void func_write_text(unsigned long arg)
{
    unsigned long i = 0;

    if (!arg) {
        return;
    }

    for (i = 0; i < arg; ++i) {
        printk(KERN_INFO "%s\n", TEXT);
    }

    list_timer.expires = jiffies + DELAY * HZ;

    add_timer(&list_timer);
}


static int __init init_func_time()
{
    init_timer_on_stack(&list_timer);

    kobj_time = kobject_create_and_add("timers", NULL);
    if (!kobj_time) {
        return -ENOMEM;
    }

    if (sysfs_create_file(kobj_time, &attribute_time.attr)) {
        exit_func_time();
        return -EINVAL;
    }

    return 0;
}

static void __exit exit_func_time()
{
    if (is_exists_timer) {
        del_timer(&list_timer);
    }

    if (kobj_time) {
        kobject_put(kobj_time);
    }
}

module_init(init_func_time);
module_exit(exit_func_time);

