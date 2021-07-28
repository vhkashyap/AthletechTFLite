#include "mbed.h"
#include "mbed-trace/mbed_trace.h"
#include "mbedtls/debug.h"
#include <stdio.h>

#include "stm32l475e_iot01_tsensor.h"
#include "stm32l475e_iot01_hsensor.h"
#include "stm32l475e_iot01_psensor.h"
#include "stm32l475e_iot01_accelero.h"
#include "stm32l475e_iot01_gyro.h"
#include "stm32l475e_iot01_magneto.h"
#include "BNO055.h"
//#include "core/cloud.h"
#include "tensorflow/lite/micro/examples/hello_world/main_functions.h"
//#define AWS_IOT_UPDATE_FREQUENCY    1

DigitalOut led(LED1);

Ticker time_int;

Timer t;
float timer_data1;
float timer_data2;
//RawSerial ser(D1, D0);

Serial pc(USBTX, USBRX);
BNO055 imu1(I2C_SDA,I2C_SCL,(0x28<<1));
BNO055 imu2(I2C_SDA,I2C_SCL,(0x29<<1));

#define BUFFER_SIZE 512

int buf_size = BUFFER_SIZE;

//char buf[BUFFER_SIZE] = {0};


struct data_point {
    float gyro[3];
    int16_t acce[3];
    int16_t mag[3];
};

#define MAX_Q_SIZE  64

struct data_point *point_arr;

volatile int q_in = 0;
volatile int q_out = 0;

extern volatile int flag;
extern volatile int value;

/*
    Blinks or not
    val         1 = blink, 0 = don't
*/
void blink(int val){
    if(val == -1){
        for(int x=0; x<4; x++){
            led = 1;
            wait(0.8);
            led = 0;
            wait(0.8);
        }
    }

    if(val == 0){
        led = 0;
        wait(0.5);
    }

    if(val == 1){
        led = 1;
        wait(0.5);
    }
}

/* connect services */
int connect(){
    int result = 0;

    //int cloud_status = cloud_connect();
    //if(cloud_status == 1){
      //  result = 1;
    //}

    //return result;
    return 0;
}

void collect_samples() {
    //struct data_point *point = &point_arr[q_in];
   // BSP_ACCELERO_AccGetXYZ(point->acce);
 //  LSM6DSL_AccReadXYZ(point->acce);
 //   BSP_GYRO_GetXYZ(point->gyro);
 //LSM6DSL_GyroReadXYZAngRate(point->gyro);
  //  BSP_MAGNETO_GetXYZ(point->mag);
   // LIS3MDL_MagReadXYZ(point->mag);
    //imu.setmode(OPERATION_MODE_NDOF);
//        imu.get_calib();
//        imu.get_angles();
//    timer_data=t.read();
//    q_in++;
//    if (q_in == MAX_Q_SIZE) {
//        q_in = 0;
//    }
}

/* just the funky start */
int main(){
    mbed_trace_init();
    pc.baud(115200);
    pc.printf("BNO055 Hello World\r\n\r\n");
    printf("IoT device starting\r\n");
   setup();
    /* define sensor vars */
    int count=0;

    int status1 = 0;
    int status2 = 0;
    int status=0;
    int status_rec=0;

    imu1.reset();
    imu2.reset();
    //struct data_point *point = NULL;

    //GYRO_InitTypeDef LSM6DSL_InitStructure;
//    LSM6DSL_InitStructure.Power_Mode = 0;
//    LSM6DSL_InitStructure.Output_DataRate = LSM6DSL_ODR_52Hz;
//    LSM6DSL_InitStructure.Axes_Enable = 0;
//    LSM6DSL_InitStructure.Band_Width = 0;
//    LSM6DSL_InitStructure.BlockData_Update = LSM6DSL_BDU_BLOCK_UPDATE;
//    LSM6DSL_InitStructure.Endianness = 0;
//    LSM6DSL_InitStructure.Full_Scale = LSM6DSL_GYRO_FS_2000;

    /* initalise sensors */
    //BSP_TSENSOR_Init();
    //BSP_HSENSOR_Init();
    //BSP_PSENSOR_Init();
   // BSP_ACCELERO_Init();
    //BSP_GYRO_Init();
 // LSM6DSL_GyroInit(0x38);
    //BSP_MAGNETO_Init();
   //
//    ser.baud(115200);
//    ser.format(8, SerialBase::None, 1);

  //  while(1) {
//        printf("Sending\n");
//        ser.puts("Hello from the other side\n");
//        wait(2);
//    }
//
//    while(1) {
//        ;
//    }
    /* init cloud (connect wifi) */
    //cloud_init();

    /* connect to network */
    //int connected = connect();
    int connected =1;
   // point_arr = (struct data_point *)malloc(MAX_Q_SIZE * sizeof(struct data_point));
//    if (point_arr == NULL) {
//        printf("Malloc failed\n");
//    }
//
//    memset(point_arr, 0, MAX_Q_SIZE * sizeof(struct data_point));
    //if(flag == 1)
//    {
//        time_int.attach(&collect_samples, value);
//        }
//        else
//        {
         // time_int.attach(&collect_samples, 0.04);
          t.start();
//    }
    while(1) {
        if(connected == 1){
            /* all good here */
            //blink(1);

            /* get current sensor data */
            //temperature = BSP_TSENSOR_ReadTemp();
            //humidity = BSP_HSENSOR_ReadHumidity();
            //pressure = BSP_PSENSOR_ReadPressure();

            /* send message to cloud */

            //wait(0.02);
           // while (q_in == q_out) {
//                ;
//            }

            //point = &point_arr[q_out];
            imu1.setmode(OPERATION_MODE_NDOF);
            imu1.get_calib();
            imu1.get_accel();
            imu1.get_gyro();
            imu1.get_mag();
            imu1.get_angles();
            timer_data1=t.read();
            imu2.setmode(OPERATION_MODE_NDOF);
            imu2.get_calib();
            imu2.get_accel();
            imu2.get_gyro();
            imu2.get_mag();
            imu2.get_angles();
            timer_data2=t.read();
            count++;
            // printf("roll: %f,pitch: %f,yaw: %f,\n",
            //                          imu2.euler.roll,imu2.euler.pitch,imu2.euler.yaw);
            //loop();
            // printf("roll: %f,pitch: %f,yaw: %f,\n",
            //                          imu2.euler.roll,imu2.euler.pitch,imu2.euler.yaw);
          //  pc.printf("roll:%f\n pitch:%f\n yaw: %f\r\n",imu1.euler.roll,imu1.euler.pitch,imu1.euler.yaw);
            // sprintf("%.2f %.2f %.2f\n",0.04,0.08,0.09);
             //int ret = sprintf(buf, "{\"roll\":%f,\"pitch\":%f,\"yaw\":%f}",imu1.euler.roll,imu1.euler.pitch,imu1.euler.yaw);
             //if(ret < 0) {
             //printf("ERROR: snprintf() returns %d.", ret);
             //}
           //  printf ("[%s] is a string %d chars long\n",buf,ret);
            // status1 = cloud_send_1(imu1.accel.x,imu1.accel.y,imu1.accel.z,imu1.gyro.x,imu1.gyro.y,imu1.gyro.z,imu1.mag.x,imu1.mag.y,imu1.mag.z, count,timer_data,imu1.euler.roll,imu1.euler.pitch,imu1.euler.yaw);
            //timer_data=t.read();
          //  status2 = cloud_send_2(imu1.accel.x,imu1.accel.y,imu1.accel.z,imu1.gyro.x,imu1.gyro.y,imu1.gyro.z,imu1.mag.x,imu1.mag.y,imu1.mag.z, count,timer_data1,imu1.euler.roll,imu1.euler.pitch,imu1.euler.yaw,imu2.accel.x,imu2.accel.y,imu2.accel.z,imu2.gyro.x,imu2.gyro.y,imu2.gyro.z,imu2.mag.x,imu2.mag.y,imu2.mag.z,timer_data2,imu2.euler.roll,imu2.euler.pitch,imu2.euler.yaw);
            // if (status2<0) {
            //     wait(1);
            //     printf("Inside reconnect \n");
            //     //HAL_NVIC_SystemReset();
            //     cloud_init();
            //     status = connect();
            //     if (status == 1) {
            //         continue;
            //     }
            // }
            //q_out++;
           // if (q_out == MAX_Q_SIZE) {
//                q_out = 0;
//            }
        }else{
            /* give it time */
            wait(2);

            /* network is off */
            blink(-1);
        }
        //status_rec=cloud_receive();
       // if(status_rec<0){
//            printf("\nreceive failed");
//            }
//        if(flag == 1)
//    {
       // time_int.attach(&collect_samples, value);
//        flag=0;
       // }
      //  else
//        {
//    time_int.attach(&collect_samples, 0.04);
//    }
     wait(0.04);

    }
    t.stop();
}
