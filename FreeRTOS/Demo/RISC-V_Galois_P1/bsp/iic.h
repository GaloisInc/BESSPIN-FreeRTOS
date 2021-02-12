#ifndef __IIC_H__
#define __IIC_H__

#include "bsp.h"
#include "xiic.h"
#include "semphr.h"

/* Device driver for IIC peripheral */
struct IicDriver
{
    XIic Device; /* Xilinx IIC driver */
    /* Counters used to determine when buffer has been send and received */
    volatile int TotalErrorCount;
    volatile int Errors;
    int trans_len;            /* Length of the transaction */
    SemaphoreHandle_t mutex;  /* Mutex for bus acquisition */
    TaskHandle_t task_handle; /* handle for task that initiated a transaction */
};

enum iic_error {
    IIC_TIMEOUT = -1,
    IIC_SLAVE_NO_ACK = -2,
    IIC_MASTER_SEND_ERROR = -3,
    IIC_MASTER_RECV_ERROR = -4,
    IIC_BUS_IS_BUSY = -5,
};

int iic_transmit(struct IicDriver *Iic, uint8_t addr, uint8_t *tx_data, uint8_t tx_len);
int iic_receive(struct IicDriver *Iic, uint8_t addr, uint8_t *rx_data, uint8_t rx_len);

#if BSP_USE_IIC0
extern struct IicDriver Iic0;
void iic0_init(void);
void iic0_stop(void);
int iic0_transmit(uint8_t addr, uint8_t *tx_data, uint8_t tx_len);
int iic0_receive(uint8_t addr, uint8_t *rx_data, uint8_t rx_len);
#endif

#endif