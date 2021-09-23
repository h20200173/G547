#include "HEADER.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>              /* open */
#include <unistd.h>             /* exit */
#include <sys/ioctl.h>          /* ioctl */


/*
 * ioctl calls function definitions
 */
u_int16_t buffer;

int ioctl_xaxis_gyro_pitch (int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_XAXIS_GYRO_PITCH, message);

    if (ret_val == 0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_yaxis_gyro_yaw(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_YAXIS_GYRO_YAW, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_zaxis_gyro_roll(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_ZAXIS_GYRO_ROLL, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_xaxis_accel_fb(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_XAXIS_ACCEL_FB, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_yaxis_accel_lr(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_YAXIS_ACCEL_LR, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_zaxis_accel_ud(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_ZAXIS_ACCEL_UD, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_xaxis_comp_dire(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_XAXIS_COMP_DIRE, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_yaxis_comp_dire(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_YAXIS_COMP_DIRE, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

int ioctl_zaxis_comp_dire(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_ZAXIS_COMP_DIRE, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}


int ioctl_baro_press(int file_desc, char *message)
{
    int ret_val;
    ret_val = ioctl(file_desc, IOCTL_BARO_PRESS, message);

    if (ret_val ==  0) {
        printf("ioctl_get_msg failed:%d\n", ret_val);
        exit(-1);
    }
    return 0;
}

/* Main */
int main()
{
    int count,select;
    int file_desc, ret_val;
    char *msg = "Message passed by ioctl\n";

    file_desc = open(DEVICE_FILE_NAME, 0);
    if (file_desc < 0) {
        printf("Cannot open the device file: %s\n", DEVICE_FILE_NAME);
        exit(-1);
    }

    printf("Select from the below options: \n  ");
    printf("1. Pitch obtained from the Gyroscope \n  2. Yaw obtained from the Gyroscope \n   3. Roll obtained from the gyroscope \n  ");
    printf("4. Forward/Backward acceleration obtained from the accelerometer  \n  5. Left/ Right acceleration obtained from the accelerometer \n  6. Up/Down acceleration obtained from the accelerometer \n  ");
    printf("7. Xaxis-direction obtained from the Compass  \n  8. Yaxis-direction obtained from the Compass \n  9. Zaxis-direction obtained from the Compass \n  ");
    printf("10. Pressure obtained from the Barometer(pascals) \n");
    scanf("%d",&select);
     
     switch(select)
     {
          case 1: ioctl_xaxis_gyro_pitch(file_desc,"1");
                  break;
          case 2: ioctl_yaxis_gyro_yaw(file_desc,"2");
                  break;
          case 3: ioctl_zaxis_gyro_roll(file_desc,"3");
                  break;
          case 4: ioctl_xaxis_accel_fb(file_desc,"4");
                  break;
          case 5: ioctl_yaxis_accel_lr(file_desc,"5");
                  break;
          case 6: ioctl_zaxis_accel_ud(file_desc,"6");
                  break;
          case 7: ioctl_xaxis_comp_dire(file_desc,"7");
                  break;
          case 8: ioctl_yaxis_comp_dire(file_desc,"8");
                  break;
          case 9: ioctl_zaxis_comp_dire(file_desc,"9");
                  break;
          case 10: ioctl_baro_press(file_desc,"10");
                  break;
          default: printf("Not defined. please choose again ");
                  break;
     }  
 
    count = read(file_desc, &buffer, sizeof(buffer));
    printf("output:10-bit: \n");
    printf("%d\n", select);
    close(file_desc);
    return 0;
}
