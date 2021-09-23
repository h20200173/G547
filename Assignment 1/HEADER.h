#ifndef CHARDEV_H
#define CHARDEV_H

#include <linux/ioctl.h>

#define MAJOR_NUM 100

#define IOCTL_XAXIS_GYRO_PITCH _IOWR(MAJOR_NUM, 0, char *)

#define IOCTL_YAXIS_GYRO_YAW _IOWR(MAJOR_NUM, 1, char *)

#define IOCTL_ZAXIS_GYRO_ROLL _IOWR(MAJOR_NUM, 2, char *)

#define IOCTL_XAXIS_ACCEL_FB _IOWR(MAJOR_NUM, 3, char *)

#define IOCTL_YAXIS_ACCEL_LR _IOWR(MAJOR_NUM, 4, char *)

#define IOCTL_ZAXIS_ACCEL_UD _IOWR(MAJOR_NUM, 5, char *)

#define IOCTL_XAXIS_COMP_DIRE _IOWR(MAJOR_NUM, 6, char *)

#define IOCTL_YAXIS_COMP_DIRE _IOWR(MAJOR_NUM, 7, char *)

#define IOCTL_ZAXIS_COMP_DIRE _IOWR(MAJOR_NUM, 8, char *)

#define IOCTL_BARO_PRESS _IOWR(MAJOR_NUM, 9, char *)

#define DEVICE_FILE_NAME "/dev/imu_char"

#endif
