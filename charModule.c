#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include <linux/slab.h> 
#include <linux/cdev.h>
#include <linux/device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Puyuan Zhang");
MODULE_DESCRIPTION("PA2 Simple device diver");

#define ClassName "classname"
#define MajorN 500
#define MinorN 0
#define DeviceName "PA2"
#define DeviceBuffSize 1024


char* buff = NULL; 
//struct class*  DeviceClass  = NULL;
//struct device* Device = NULL;
struct cdev my_device;

dev_t deviceID = MKDEV(MajorN, MinorN);
int openNum = 0;
int closeNum = 0;

int     DevOpen  (struct inode *fileObj, struct file *fileStatus);
int     DevClose (struct inode *fileObj, struct file *fileStatus);
ssize_t DevRead  (struct file *fileStatus, char __user *userBuff, size_t userBuffSize, loff_t *offset);
ssize_t DevWrite (struct file *fileStatus, const char __user *userBuff, size_t userBuffSize, loff_t *offset);
loff_t  DevSeek  (struct file *fileStatus, loff_t offset, int idx);


struct file_operations fileOper = {
    .owner   = THIS_MODULE,
    .open    = DevOpen,
    .release = DevClose,
    .read    = DevRead,
    .write   = DevWrite,
    .llseek  = DevSeek
};

int     DevOpen  (struct inode *fileObj, struct file *fileStatus)
{
    openNum++;
    return 0;
}
int     DevClose (struct inode *fileObj, struct file *fileStatus)
{
    closeNum++;
    return 0;
}
ssize_t DevRead  (struct file *fileStatus, char __user *userBuff, size_t userBuffSize, loff_t *offset)
{
    int temp = 0;
    if (DeviceBuffSize - *offset >= userBuffSize)
        temp = userBuffSize;
    else
        temp = DeviceBuffSize - *offset;

    printk(" device received IO request read with offset %lld and the buff size is %d.", *offset, temp);
    
    copy_to_user(userBuff, &buff[*offset], temp);
    *offset += temp;
    return temp;
}
ssize_t DevWrite (struct file *fileStatus,const char __user *userBuff, size_t userBuffSize, loff_t *offset)
{
    int temp = 0;
    if (DeviceBuffSize - *offset >= userBuffSize)
        temp = userBuffSize;
    else
        temp = DeviceBuffSize - *offset;

    printk(" device received IO request write with offset %lld and the buff size is %d.", *offset, temp);
    
    copy_from_user(&buff[*offset], userBuff, temp);
    *offset += temp;
    return temp;
}
loff_t  DevSeek  (struct file *fileStatus, loff_t offset, int idx)
{
    loff_t temp = -1;

    if (idx == SEEK_SET)
        temp = offset;

    else if (idx == SEEK_CUR)
        temp = fileStatus->f_pos + offset;

    else
        temp = DeviceBuffSize + offset;
    
    if (temp < 0 || temp == DeviceBuffSize)
        return -1;
    
    fileStatus->f_pos = temp;
    return temp;
}

int driverInit(void)
{


    buff = kmalloc(DeviceBuffSize, GFP_KERNEL);
    memset(buff, 0, DeviceBuffSize);
/*
    register_chrdev(MajorN, DeviceName, &fileOper);
    DeviceClass = class_create(THIS_MODULE, ClassName);
    Device = device_create(DeviceClass, NULL, deviceID, NULL, DeviceName);
*/

    my_device.owner = THIS_MODULE;
    cdev_init(&my_device, &fileOper);

    if (register_chrdev_region(deviceID, 1, DeviceName) < 0)
    {
        printk(KERN_WARNING "Device Identity conflict detected\n");
        alloc_chrdev_region(&deviceID, 0, 1, DeviceName);
    }

    cdev_add(&my_device, deviceID, 1);

    printk("successful add device %s with major %d and minor %d", DeviceName,MajorN, MinorN);
    return 0;
}


void driveExit(void)
{
/*
    device_unregister(Device);
    device_destroy(DeviceClass, deviceID);
    class_unregister(DeviceClass);
    class_destroy(DeviceClass);
    unregister_chrdev(MajorN,DeviceName);
*/
    unregister_chrdev_region(deviceID, 1);
    cdev_del(&my_device);
    kfree(buff);

    printk("successful remove device %s with major %d and minor %d", DeviceName,MajorN, MinorN);
    return;
}

module_init(driverInit);
module_exit(driveExit);
