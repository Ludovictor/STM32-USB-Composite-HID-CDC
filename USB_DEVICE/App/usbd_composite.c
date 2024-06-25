#include "usbd_composite.h"

USBD_CDC_HandleTypeDef *pCDCData;
USBD_HID_HandleTypeDef *pHIDData;

static uint8_t  USBD_Composite_Init (USBD_HandleTypeDef *pdev,
                            uint8_t cfgidx);
static uint8_t  USBD_Composite_DeInit (USBD_HandleTypeDef *pdev,
                              uint8_t cfgidx);
static uint8_t  USBD_Composite_Setup (USBD_HandleTypeDef *pdev,
                             USBD_SetupReqTypedef *req);
static uint8_t  USBD_Composite_EP0_RxReady(USBD_HandleTypeDef *pdev);
static uint8_t  USBD_Composite_DataIn (USBD_HandleTypeDef *pdev,
                              uint8_t epnum);
static uint8_t  USBD_Composite_DataOut (USBD_HandleTypeDef *pdev,
                               uint8_t epnum);
static uint8_t  *USBD_Composite_GetFSCfgDesc (uint16_t *length);
static uint8_t  *USBD_Composite_GetDeviceQualifierDescriptor (uint16_t *length);

USBD_ClassTypeDef  USBD_COMPOSITE =
{
  USBD_Composite_Init,
  USBD_Composite_DeInit,
  USBD_Composite_Setup,
  NULL, /*EP0_TxSent*/
  USBD_Composite_EP0_RxReady,  //add
  USBD_Composite_DataIn,
  USBD_Composite_DataOut,
  NULL,
  NULL,
  NULL,
  NULL,
  USBD_Composite_GetFSCfgDesc,
  NULL,
  USBD_Composite_GetDeviceQualifierDescriptor,
};



/* USB composite device Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
__ALIGN_BEGIN uint8_t USBD_Composite_CfgFSDesc[USBD_COMPOSITE_DESC_SIZE]  __ALIGN_END =
{
  /* Configuration Descriptor */
  0x09,   /* bLength: Configuation Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,   /* bDescriptorType: Configuration */
  USBD_COMPOSITE_DESC_SIZE,
  0x00,
  USBD_MAX_NUM_INTERFACES ,  /* bNumInterfaces: */
  0x01,   /* BCONFIGURATIONVALUE: 0 Configured value */
  0x00,   /* iConfiguration: 00 string index */
  0x80,   /* bmAttributes:no-bus powered and Dissupport Remote Wake-up*/
  0x32,   /* MaxPower 100 mA  */


  /****************************HID************************************/
  /* Interface Association Descriptor */
  USBD_IAD_DESC_SIZE,                        // BLENGTH IAD Descriptor Size
  USBD_IAD_DESCRIPTOR_TYPE,                  // BDescriptortype IAD Descriptor Type
  0x00,                                      // bfirstInterface interface descriptor is the number starting from 0 in the total configuration descriptor
  0x01,                                      // binterfaceCount interface descriptor quantity
  0x03,                                      // BDeviceClass in BFunctionClass device
  0x00,                                      // BDeviceSubclass in the BFunctionsUbclass device
  0x00,                                      // binterfaceprotocol in the BDeviceProtocol device
  0x00,

  /********************  HID interface ********************/
  /************** Descriptor of Custom HID interface ****************/
  /* 09 */
  0x09,                   /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  USBD_HID_INTERFACE,     /* binterfacenumber: Number of Interface interface number 0 */
  0x00,                   /* BalternateSetting: Alternate Setting Alternate Interface */
  0x01,                   /* BNUMENDPOINTS number 1 */
  0x03,                   /*bInterfaceClass: HID*/
  0x00,                   /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x00,                   /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,                      /*iInterface: Index of string descriptor*/

  /******************** Descriptor of Custom HID ********************/
  /* 18 */
  0x09,                   /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE,    /*bDescriptorType: HID*/
  0x00,                   /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,                   /*bCountryCode: Hardware target country*/
  0x01,                   /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,                   /*bDescriptorType*/
  HID_MOUSE_REPORT_DESC_SIZE,/*wItemLength: Total length of Report descriptor*/
  0x00,
  /******************** Descriptor of TouchScreen endpoint ********************/
  /* 27 */
  0x07,                   /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/

  HID_EPIN_ADDR,          /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,                   /*bmAttributes: Interrupt endpoint*/
  HID_EPIN_SIZE,          /*wMaxPacketSize: 16 Byte max */
  0x00,
  HID_FS_BINTERVAL,       /*bInterval: Polling Interval */
  /* 34 */

  /****************************CDC************************************/
  /* IAD descriptor */
  /* Interface Association Descriptor */
  USBD_IAD_DESC_SIZE,               // bLength
  USBD_IAD_DESCRIPTOR_TYPE,         // bDescriptorType
  0x01,                             // bfirstInterface interface descriptor is the number starting from 0 in the total configuration descriptor 1
  0x02,                             // binterfaceCount interface descriptor number 2
  0x02,                             // bFunctionClass     CDC Control
  0x02,                             // bFunctionSubClass  Abstract Control Model
  0x01,                             // bInterfaceProtocol  AT Commands: V.250 etc
  0x00,                             // iFunction

  /* CDC command interface descriptor */
  /*Interface Descriptor */
  0x09,   /* BLENGTH: Interface Descriptor Size Length */
  USB_DESC_TYPE_INTERFACE,  /* BDEScriptortype: interface number 0x04 */
  /* Interface descriptor type */
  USBD_CDC_CMD_INTERFACE,   /* binterfacenumber: Number of Interface interface number, first interface number 1 */
  0x00,   /* BalternateSetting: Alternate setting interface standby number 0 */
  0x01,   /* BNUMENDPOINTS: One Endpoints Used Number 1 Number 1 CDC interface only uses an interrupt input endpoint */
  0x02,   /* binterfaceclass: Class 0x02 in the Communication Interface Class interface */
  0x02,   /* binterfacesubclass: ABSTRACT Control Model interface used by subclass 0x02 */
  0x01,   /* BinterfaceProtocol: Common At Commands Using the AT Command Protocol */
  0x00,   /* IINTERFACE: Interface string index 0 indicates no */

  /* Class Special Interface Descriptor - Function Descriptor Used to describe the functionality of the interface */
  /*Header Functional Descriptor*/
  0x05,   /* BLENGTH: Endpoint Descriptor size descriptor length is 5 bytes */
  0x24,   /* bdescriptortype: CS_Interface Descriptor Type for class special interface CS_Interface */
  0x00,   /* bdescriptorsubtype: Header Func Desc Sub-class is Header Func DESC, number 0x00 */
  0x10,   /* BCDCDC: SPEC Release Number CDC version */
  0x01,

  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bdescriptortype: CS_Interface Descriptor Type for class special interface CS_Interface */
  0x01,   /* BDEScriptorsubtype: Call Management Func Desc Sub-class Call Management Func DESC Number 0x01 */
  0x00,   /* BMCapabilities: D0 + D1 device yourself does not manage Call Management */
  0x01,   /* BDataInterface: 1 has a data class interface for call management */

  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bdescriptortype: CS_Interface Descriptor Type for class special interface CS_Interface */
  0x02,   /* bdescriptorsubtype: Abstract Control Management Desc Subclass is Abstract Control Management DESC Number 0x02 */
  0x02,   /* BMCapabilities Support SET_CONTROL_LINE_STATE, GET_LINE_CODING Request and Serial_State Notifications */

  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bdescriptortype: CS_Interface Descriptor Type for class special interface CS_Interface */
  0x06,   /* bdescriptorsubtype: UNION FUNC DESC sub-class is UNION FUNC DESC number 0x06 */
  USBD_CDC_CMD_INTERFACE,    /* BMasterInterface: CMMUNICATION CLASS interface number 1 CDC interface */
  USBD_CDC_DATA_INTERFACE,   /* BSLAVEINTERFACE0: Data Class Interface Number 2 Data Class Interface */

  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,   			/* bDescriptorType: Endpoint */
  CDC_CMD_EP,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(CDC_CMD_PACKET_SIZE),    /* wMaxPacketSize: */
  HIBYTE(CDC_CMD_PACKET_SIZE),
  CDC_FS_BINTERVAL,                           /* bInterval: */
  /*---------------------------------------------------------------------------*/

	/* Interface descriptor */
  /*Data class interface descriptor*/
  0x09,   /* BLENGTH: Endpoint Descriptor Size Interface Descriptor Length 9 byte */
  USB_DESC_TYPE_INTERFACE,  /* bdescriptortype: number 0x04 with interface descriptor */
  USBD_CDC_DATA_INTERFACE,   /* binterfacenumber: Number of interface interface number 2 */
  0x00,   /* BalternateSetting: Alternate setting This interface is 0 */
  0x02,   /* BNUMENDPOINTS: TWO Endpoints Used Non 0 End Point Data Device You need to use a pair of batch endpoints, set to 2 */
  0x0A,   /* binterfaceClass: CDC The class data class interface code used by this interface is 0x0a */
  0x00,   /* binterfaceSubclass: The subcaters used by the interface are 0 */
  0x00,   /* binterfaceProtocol: The protocol used by the interface is 0 */
  0x00,   /* IINTERFACE: The character string of the interface, 0 means no */

	/* Endpoint descriptor of the output endpoint */
  /*Endpoint OUT Descriptor*/
  0x07,   /* BLENGTH: Endpoint Descriptor Size Endpoint Descriptor Length 7 bytes */
  USB_DESC_TYPE_ENDPOINT,               /* bdescriptortype: Endpoint endpoint descriptor number is 0x05 */
  CDC_OUT_EP,                           /* BenPointAddress endpoint address 0x02 D7 is the direction */
  0x02,                                 /* BMAttributes: Bulk Batch Transfer */
  LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),  /* WMAXPACKETSIZE: Endpoint's maximum package length 512 bytes */
  HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),
  0x00,                                 /* Binterval: Ignore for Bulk Transfer endpoint query time, invalid for batch endpoints */

	/* Endpoint descriptor of the input end point */
  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,               /* bdescriptortype: Endpoint endpoint descriptor number is 0x05 */
  CDC_IN_EP,                            /* BenPointAddress endpoint address 0x82 D7 is the direction */
  0x02,                                 /* BMAttributes: Bulk Batch Transfer */
  LOBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),  /* WMAXPACKETSIZE: Endpoint's maximum package length 512 bytes */
  HIBYTE(CDC_DATA_HS_MAX_PACKET_SIZE),
  0x00                                  /* Binterval: Ignore for Bulk Transfer endpoint query time, invalid for batch endpoints */
};

/* USB device qualifier descriptor */
/* USB Standard Device Descriptor */
__ALIGN_BEGIN  uint8_t USBD_Composite_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]  __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};

static uint8_t  USBD_Composite_Init (USBD_HandleTypeDef *pdev,
                            uint8_t cfgidx)
{
  uint8_t res = 0;

  pdev->pUserData[0] =  (void*)&USBD_Interface_fops_FS;
  res +=  USBD_CDC.Init(pdev,cfgidx);
  pCDCData = pdev->pClassData;
  /* TODO */
  pdev->pUserData[0] = NULL;
  res +=  USBD_HID.Init(pdev,cfgidx);
  pHIDData = pdev->pClassData;
  return res;
}


static uint8_t  USBD_Composite_DeInit (USBD_HandleTypeDef *pdev,
                              uint8_t cfgidx)
{
  uint8_t res = 0;
	pdev->pClassData = pCDCData;
	pdev->pUserData[0] = &USBD_Interface_fops_FS;
	res +=  USBD_CDC.DeInit(pdev,cfgidx);

	pdev->pClassData = pHIDData;
  /* TODO */
	pdev->pUserData[0] = NULL;
	res +=  USBD_HID.DeInit(pdev,cfgidx);

	return res;
}


static uint8_t  USBD_Composite_EP0_RxReady(USBD_HandleTypeDef *pdev)
{
	pdev->pClassData = pCDCData;
	pdev->pUserData[0] = &USBD_Interface_fops_FS;
  return USBD_CDC.EP0_RxReady(pdev);
}


/**
* @brief  USBD_Composite_Setup
*         Handle the Composite requests
* @param  pdev: device instance
* @param  req: USB request
* @retval status
*/
static uint8_t  USBD_Composite_Setup (USBD_HandleTypeDef *pdev, USBD_SetupReqTypedef *req)
{
  switch (req->bmRequest & USB_REQ_RECIPIENT_MASK)
  {
   case USB_REQ_RECIPIENT_INTERFACE:
     switch(req->wIndex)
      {
         case USBD_CDC_DATA_INTERFACE:
         case USBD_CDC_CMD_INTERFACE:
           pdev->pClassData = pCDCData;
           pdev->pUserData[0] =  &USBD_Interface_fops_FS;
           return(USBD_CDC.Setup(pdev, req));

         case USBD_HID_INTERFACE:
           pdev->pClassData = pHIDData;
           /* TODO */
           pdev->pUserData[0] =  NULL;
           return(USBD_HID.Setup (pdev, req));

         default:
            break;
     }
     break;

   case USB_REQ_RECIPIENT_ENDPOINT:
     switch(req->wIndex)
     {

         case CDC_IN_EP:
         case CDC_OUT_EP:
         case CDC_CMD_EP:
           pdev->pClassData = pCDCData;
           pdev->pUserData[0] =  &USBD_Interface_fops_FS;
           return(USBD_CDC.Setup(pdev, req));

         case HID_EPIN_ADDR:
//         case HID_EPOUT_ADDR:
           pdev->pClassData = pHIDData;
           /* TODO */
           pdev->pUserData[0] =  NULL;
           return(USBD_HID.Setup (pdev, req));

         default:
            break;
     }
     break;
  }
  return USBD_OK;
}

/**
* @brief  USBD_Composite_DataIn
*         handle data IN Stage
* @param  pdev: device instance
* @param  epnum: endpoint index
* @retval status
*/
static uint8_t  USBD_Composite_DataIn (USBD_HandleTypeDef *pdev,
                              uint8_t epnum)
{
  switch(epnum)
  {
      case CDC_INDATA_NUM:
         pdev->pUserData[0] =  &USBD_Interface_fops_FS;
         pdev->pClassData = pCDCData;
         return(USBD_CDC.DataIn(pdev,epnum));
      case HID_INDATA_NUM:
         /* TODO */
         pdev->pUserData[0] = NULL;
         pdev->pClassData = pHIDData;
         return(USBD_HID.DataIn(pdev,epnum));
      default:
         break;
  }
  return USBD_FAIL;
}

/**
* @brief  USBD_Composite_DataOut
*         handle data OUT Stage
* @param  pdev: device instance
* @param  epnum: endpoint index
* @retval status
*/
uint8_t  USBD_Composite_DataOut (USBD_HandleTypeDef *pdev,
                               uint8_t epnum)
{
  switch(epnum)
  {
      case CDC_OUTDATA_NUM:
      case CDC_OUTCMD_NUM:
    	pdev->pClassData = pCDCData; //pdev->pClassDataCmsit[pdev->classId] = pCDCData;
        pdev->pUserData[0] =  &USBD_Interface_fops_FS;
        return(USBD_CDC.DataOut(pdev,epnum));

      default:
         break;
  }
  return USBD_FAIL;
}

/**
* @brief  USBD_Composite_GetHSCfgDesc
*         return configuration descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_Composite_GetFSCfgDesc (uint16_t *length)
{
   *length = sizeof (USBD_Composite_CfgFSDesc);
   return USBD_Composite_CfgFSDesc;
}


/**
* @brief  DeviceQualifierDescriptor
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
uint8_t  *USBD_Composite_GetDeviceQualifierDescriptor (uint16_t *length)
{
  *length = sizeof (USBD_Composite_DeviceQualifierDesc);
  return USBD_Composite_DeviceQualifierDesc;
}
