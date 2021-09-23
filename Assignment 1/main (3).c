#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/random.h>
#include <linux/sched.h>
#include <linux/uaccess.h>        
#include <linux/time.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include "HEADER.h"

#define GOOD 1111

#define DEVICE_NAME "imu_char"

static uint16_t message;
static uint16_t *message_ptr;
static char alignment;

static dev_t first;          //variable for device number
static struct cdev c_dev;    //variable for the character device structure
static struct class *cls;    //varible for the device class

static int my_open(struct inode *i, struct file *f)
{
   printk(KERN_INFO "Mychar : open()\n");
   return 0;
}

static int my_close(struct inode *i, struct file *f)
{
   printk(KERN_INFO "Mychar : close()\n");
   return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
   printk(KERN_INFO "Mychar : read()\n");
    /*
     * No of bytes written to the buffer
     */
    char *b;
    int bytes_read = 0;
    int temp;

#ifdef DEBUG
    printk(KERN_INFO "device_read(%p,%p,%d)\n", file, buf, length);
#endif

    /*
     * put the data into the buffer
     */
    uint16_t random, m,n;
    get_random_bytes(&m, sizeof(m));
    random = m%1023;
    printk(KERN_INFO "random number : %d\n", random);
    message = random;
    copy_to_user(buf, &message, sizeof(message));
   

#ifdef DEBUG
    printk(KERN_INFO "Read %d bytes, %d left\n", bytes_read, length);
#endif
    return 10;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
   printk(KERN_INFO "Mychar : write()\n");
   return len;
}


         // file operations //
static struct file_operations fops =
{
   .owner     = THIS_MODULE,
   .open      = my_open,
   .release   = my_close,
   .read      = my_read,
   .write     = my_write
};




static long device_ioctl(struct file *file,             
                  unsigned int ioctl_num,        /* number and param for ioctl */
                  unsigned long ioctl_param)
{
    int i;
    char *temp;
    char ch;

    /*
     * as per user request
     */
    switch (ioctl_num) {
   
    case IOCTL_XAXIS_GYRO_PITCH:    
          temp = (char *)ioctl_param;
          copy_to_user(temp, &message, sizeof(message));
	

         break;
         
    case IOCTL_YAXIS_GYRO_YAW:  
          
         temp = (char *)ioctl_param;
          copy_to_user(temp, &message, sizeof(message));  
        

         break;
                           
    case IOCTL_ZAXIS_GYRO_ROLL:  
          
         temp = (char *)ioctl_param;
        copy_to_user(temp, &message, sizeof(message));  


         break;
         
    case IOCTL_XAXIS_ACCEL_FB:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   
         break;
         
    case IOCTL_YAXIS_ACCEL_LR:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;  

         break;
                           
    case IOCTL_ZAXIS_ACCEL_UD:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   
         break; 
         
    case IOCTL_XAXIS_COMP_DIRE:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   

         break;
         
    case IOCTL_YAXIS_COMP_DIRE:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   

         break;
                           
    case IOCTL_ZAXIS_COMP_DIRE:    
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   

         break;  
         
    case IOCTL_BARO_PRESS:
         
          temp = (char *)ioctl_param;
          get_user(ch, temp);
	  alignment = ch;   

         break;
        default :  break;

    }

    return GOOD;
}




static int __init mychar_init(void)
{
  printk(KERN_INFO  "IMU CHAR driver registered ");
  
  // <major,minor>
  if(alloc_chrdev_region(&first,0,1,"pilani")<0)
  {
        return -1;
  }
  
   //creating class
  if((cls=class_create(THIS_MODULE,"chardev"))==NULL)   
  {
      unregister_chrdev_region(first,1);
	  return -1;
  }
  
  // creating device node
  if((device_create(cls,NULL,first,NULL,"imu_char"))==NULL)
  {
      class_destroy(cls);
      unregister_chrdev_region(first,1);
	  return -1;
  }
  
  
 // link fops and cdev to device node
  cdev_init(&c_dev,&fops);
  if(cdev_add(&c_dev,first,1)== -1)
  {
      device_destroy(cls,first);
      class_destroy(cls);
      unregister_chrdev_region(first,1);
	  return -1;
  }
  return 0;  
}

static void __exit mychar_exit(void)
{
   cdev_del(&c_dev);
   device_destroy(cls,first);
   class_destroy(cls);
   unregister_chrdev_region(first,1);
   printk(KERN_INFO "Bye:imu_char driver unregistered\n\n");
   
}

module_init(mychar_init);
module_exit(mychar_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("KARTHIK");
MODULE_DESCRIPTION("Assign_1");
