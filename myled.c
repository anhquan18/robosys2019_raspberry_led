/*
 * myled.c
 *
 * Copyright (C) 2019 Nguyen Anh Quan <quan20191218@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#define LED_NUMBER 9

MODULE_AUTHOR("Nguyen Anh Quan");
MODULE_DESCRIPTION("LED driver for Raspberry Pi 3B");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.2");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;
static int led_gpio_list[LED_NUMBER] = {26,19, 6, 13, 5, 21, 20, 16, 12};

static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos)
{
    char c;
    int i;
    if(copy_from_user(&c, buf, sizeof(char))){
        return -EFAULT;
    }
    if(c == '1') gpio_base[7] = 1 << led_gpio_list[0];
    if(c == '2') gpio_base[7] = 1 << led_gpio_list[1];
    if(c == '3') gpio_base[7] = 1 << led_gpio_list[2];
    if(c == '4') gpio_base[7] = 1 << led_gpio_list[3];
    if(c == '5') gpio_base[7] = 1 << led_gpio_list[4];
    if(c == '6') gpio_base[7] = 1 << led_gpio_list[5];
    if(c == '7') gpio_base[7] = 1 << led_gpio_list[6];
    if(c == '8') gpio_base[7] = 1 << led_gpio_list[7];
    if(c == '9') gpio_base[7] = 1 << led_gpio_list[8];

    if(c == 'F'){
        for(i = 0; i < LED_NUMBER; i++){
            gpio_base[10] = 1 << led_gpio_list[i];
        }
    }
    return 1;
}

static struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write
};

static int __init init_mod(void)
{
    int retval, i;
    retval =  alloc_chrdev_region(&dev, 0, 1, "myled");
    if(retval < 0){
        printk(KERN_ERR "alloc_chrdev_region failed.\n");
        return retval;
    }
    printk(KERN_INFO "%s is loaded.\n",__FILE__);

    cdev_init(&cdv, &led_fops);
    retval = cdev_add(&cdv, dev, 1);
    if(retval < 0){
        printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
        return retval;
    }

    cls = class_create(THIS_MODULE,"myled");
    if(IS_ERR(cls)){
        printk(KERN_ERR "class_create failed.");
        return PTR_ERR(cls);
    }
    device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));
    gpio_base = ioremap_nocache(0x3f200000, 0xA0);
    for(i = 0; i < LED_NUMBER; i++){
        const u32 led = led_gpio_list[i];
        const u32 index = led / 10;
        const u32 shift = (led % 10) * 3;
        const u32 mask = ~(0x7 << shift);
        gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
    }
    return 0;
}

static void __exit cleanup_mod(void)
{
    cdev_del(&cdv);
    device_destroy(cls, dev);
    class_destroy(cls);
    unregister_chrdev_region(dev, 1);
    printk(KERN_INFO "%s is unloaded.\n",__FILE__);
}

module_init(init_mod);
module_exit(cleanup_mod);
