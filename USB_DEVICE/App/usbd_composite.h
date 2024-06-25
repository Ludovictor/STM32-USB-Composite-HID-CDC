#ifndef __USBD_COMPOSITE_H_
#define __USBD_COMPOSITE_H_

#include "usbd_hid.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"


#define USBD_COMPOSITE_DESC_SIZE    (108)

#define USBD_IAD_DESC_SIZE           0x08
#define USBD_IAD_DESCRIPTOR_TYPE     0x0B

#define USBD_HID_INTERFACE           0  // HID interface index value
#define USBD_CDC_CMD_INTERFACE       1  // CDC CMD interface index value
#define USBD_CDC_DATA_INTERFACE      2  // CDC DATA interface index value

#define HID_INDATA_NUM              (HID_EPIN_ADDR & 0x0F)
#define CDC_INDATA_NUM              (CDC_IN_EP & 0x0F)
#define CDC_OUTDATA_NUM             (CDC_OUT_EP & 0x0F)
#define CDC_OUTCMD_NUM              (CDC_CMD_EP & 0x0F)

extern USBD_CDC_HandleTypeDef *pCDCData;
extern USBD_HID_HandleTypeDef *pHIDData;

extern USBD_ClassTypeDef    USBD_COMPOSITE;
#endif
