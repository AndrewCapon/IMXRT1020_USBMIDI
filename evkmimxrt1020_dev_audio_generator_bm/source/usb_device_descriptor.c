/*
 * Copyright (c) 2015 - 2016, Freescale Semiconductor, Inc.
 * Copyright 2016 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "usb_device_config.h"
#include "usb.h"
#include "usb_device.h"

#include "usb_device_class.h"
//#include "usb_device_midi.h"
#include "usb_audio_config.h"
#include "usb_device_descriptor.h"
#include "audio_generator.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/
/* Audio generator stream endpoint information */
//usb_device_endpoint_struct_t g_UsbDeviceAudioGeneratorEndpoints[USB_AUDIO_STREAM_ENDPOINT_COUNT] = {
//    /* Audio generator ISO IN pipe */
//    {
//        USB_AUDIO_STREAM_ENDPOINT | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT),
//        USB_ENDPOINT_ISOCHRONOUS, FS_ISO_IN_ENDP_PACKET_SIZE,
//    },
//};

/* Audio generator control endpoint information */
usb_device_endpoint_struct_t g_UsbDeviceAudioControlEndpoints[USB_AUDIO_CONTROL_ENDPOINT_COUNT] = {
    {
        USB_AUDIO_CONTROL_ENDPOINT | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT),
        USB_ENDPOINT_INTERRUPT, FS_INTERRUPT_IN_PACKET_SIZE,
    },
};

usb_device_endpoint_struct_t g_UsbDeviceAudioMIDI_STEREAM_Endpoints[2] = {
    {
        (2) | (USB_IN << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT),
        USB_ENDPOINT_BULK,
		64,
    },
	{
	      (2) | (USB_OUT << USB_DESCRIPTOR_ENDPOINT_ADDRESS_DIRECTION_SHIFT),
	      USB_ENDPOINT_BULK,
		  64,
	 }

};



/* Audio generator entity struct */
//usb_device_audio_entity_struct_t g_UsbDeviceAudioEntity[] = {
//    {
//        USB_AUDIO_CONTROL_INPUT_TERMINAL_ID, USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_INPUT_TERMINAL, 0U,
//    },
//    {
//        USB_AUDIO_CONTROL_FEATURE_UNIT_ID, USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_FEATURE_UNIT, 0U,
//    },
//    {
//        USB_AUDIO_CONTROL_OUTPUT_TERMINAL_ID, USB_DESCRIPTOR_SUBTYPE_AUDIO_CONTROL_OUTPUT_TERMINAL, 0U,
//    },
//};
//
///* Audio generator entity information */
//usb_device_audio_entities_struct_t g_UsbDeviceAudioEntities = {
//    g_UsbDeviceAudioEntity, sizeof(g_UsbDeviceAudioEntity) / sizeof(usb_device_audio_entity_struct_t),
//};

/* Audio generator control interface information */
usb_device_interface_struct_t g_UsbDeviceAudioControInterface[] = {{
    0U,
    {
        0, g_UsbDeviceAudioControlEndpoints,
    },
    NULL,
}};

/* Audio generator stream interface information */
//usb_device_interface_struct_t g_UsbDeviceAudioStreamInterface[] = {
//    {
//        0U,
//        {
//            0U, NULL,
//        },
//        NULL,
//    },
//    {
//        1U,
//        {
//            USB_AUDIO_STREAM_ENDPOINT_COUNT, g_UsbDeviceAudioGeneratorEndpoints,
//        },
//        NULL,
//    },
//};

usb_device_interface_struct_t g_UsbDeviceAudioMIDIStreamingInterface[] = {

	{
	    0U,
	    {
	    	2, g_UsbDeviceAudioMIDI_STEREAM_Endpoints,
	    },
	    NULL,
	}

};


/* Define interfaces for audio generator */
usb_device_interfaces_struct_t g_UsbDeviceAudioInterfaces[USB_AUDIO_GENERATOR_INTERFACE_COUNT] = {
    {
        USB_AUDIO_CLASS,                   /* Audio class code */
        USB_SUBCLASS_AUDIOCONTROL,         /* Audio control subclass code */
        USB_AUDIO_PROTOCOL,                /* Audio protocol code */
        USB_AUDIO_CONTROL_INTERFACE_INDEX, /* The interface number of the Audio control */
        g_UsbDeviceAudioControInterface,   /* The handle of Audio control */
        sizeof(g_UsbDeviceAudioControInterface) / sizeof(usb_device_interfaces_struct_t),
    },
    {
        USB_AUDIO_CLASS,                  /* Audio class code */
        0x03,         /* Audio stream subclass code */
        USB_AUDIO_PROTOCOL,               /* Audio protocol code */
        (0x01), /* The interface number of the Audio control */
        g_UsbDeviceAudioMIDIStreamingInterface,  /* The handle of Audio stream */
        sizeof(g_UsbDeviceAudioMIDIStreamingInterface) / sizeof(usb_device_interfaces_struct_t),
    }

};

/* Define configurations for audio generator */
usb_device_interface_list_t g_UsbDeviceAudioInterfaceList[USB_DEVICE_CONFIGURATION_COUNT] = {
    {
        USB_AUDIO_GENERATOR_INTERFACE_COUNT, g_UsbDeviceAudioInterfaces,
    },
};

/* Define class information for audio generator */
usb_device_class_struct_t g_UsbDeviceAudioClass = {
    g_UsbDeviceAudioInterfaceList, kUSB_DeviceClassTypeAudio, USB_DEVICE_CONFIGURATION_COUNT,
};

/* Define device descriptor */
USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
uint8_t g_UsbDeviceDescriptor[] = {
    USB_DESCRIPTOR_LENGTH_DEVICE, /* Size of this descriptor in bytes */
    USB_DESCRIPTOR_TYPE_DEVICE,   /* DEVICE Descriptor Type */
    USB_SHORT_GET_LOW(USB_DEVICE_SPECIFIC_BCD_VERSION),
    USB_SHORT_GET_HIGH(USB_DEVICE_SPECIFIC_BCD_VERSION), /* USB Specification Release Number in
                                                            Binary-Coded Decimal (i.e., 2.10 is 210H). */
    USB_DEVICE_CLASS,                                    /* Class code (assigned by the USB-IF). */
    USB_DEVICE_SUBCLASS,                                 /* Subclass code (assigned by the USB-IF). */
    USB_DEVICE_PROTOCOL,                                 /* Protocol code (assigned by the USB-IF). */
    USB_CONTROL_MAX_PACKET_SIZE,                         /* Maximum packet size for endpoint zero
                                                            (only 8, 16, 32, or 64 are valid) */
    0xC9U, 0x1FU,                                        /* Vendor ID (assigned by the USB-IF) */
    0x97U, 0x00U,                                        /* Product ID (assigned by the manufacturer) */
    USB_SHORT_GET_LOW(USB_DEVICE_DEMO_BCD_VERSION),
    USB_SHORT_GET_HIGH(USB_DEVICE_DEMO_BCD_VERSION), /* Device release number in binary-coded decimal */
    0x01U,                                           /* Index of string descriptor describing manufacturer */
    0x02U,                                           /* Index of string descriptor describing product */
    0x00U,                                           /* Index of string descriptor describing the
                                                        device's serial number */
    USB_DEVICE_CONFIGURATION_COUNT,                  /* Number of possible configurations */
};

USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
uint8_t g_UsbDeviceConfigurationDescriptor[] = {
		/*--------------------------------------- Configuration Descriptor--------------------------------*/
		/*wTotalLengthは全体のディスクリプタ長さなのですべて記述後再計算して修正する。*/
		 USB_DESCRIPTOR_LENGTH_CONFIGURE, /* Size of this descriptor in bytes */
		    USB_DESCRIPTOR_TYPE_CONFIGURE,   /* CONFIGURATION Descriptor Type */
			0x65U,0x00U,
		    USB_AUDIO_GENERATOR_INTERFACE_COUNT,                    /* Number of interfaces supported by this configuration */
		    USB_AUDIO_GENERATOR_CONFIGURE_INDEX,                    /* Value to use as an argument to the
		                                                               SetConfiguration() request to select this configuration */
		    0x00U, /* Index of string descriptor describing this configuration */

		    (USB_DESCRIPTOR_CONFIGURE_ATTRIBUTE_D7_MASK) |
		        (USB_DEVICE_CONFIG_SELF_POWER << USB_DESCRIPTOR_CONFIGURE_ATTRIBUTE_SELF_POWERED_SHIFT) |
		        (USB_DEVICE_CONFIG_REMOTE_WAKEUP << USB_DESCRIPTOR_CONFIGURE_ATTRIBUTE_REMOTE_WAKEUP_SHIFT),
		    /* Configuration characteristics
		       D7: Reserved (set to one)
		       D6: Self-powered
		       D5: Remote Wakeup
		       D4...0: Reserved (reset to zero)
		    */
		    USB_DEVICE_MAX_POWER, /* Maximum power consumption of the USB
		                           * device from the bus in this specific
		                           * configuration when the device is fully
		                           * operational. Expressed in 2 mA units
		                           *  (i.e., 50 = 100 mA).
		                           */





			/*--------------------------------------- Audio Class Standard  Interface Descriptor--------------------------------*/
		    USB_DESCRIPTOR_LENGTH_INTERFACE,   /* Size of this descriptor in bytes */
		    USB_DESCRIPTOR_TYPE_INTERFACE,     /* INTERFACE Descriptor Type */
		    USB_AUDIO_CONTROL_INTERFACE_INDEX, /* Number of this interface. */
		    0x00U,                             /* Value used to select this alternate setting
		                                          for the interface identified in the prior field */
		    0x00U,                             /* Number of endpoints used by this
		                                          interface (excluding endpoint zero). */
		    USB_AUDIO_CLASS,                   /*The interface implements the Audio Interface class  */
		    USB_SUBCLASS_AUDIOCONTROL,         /*The interface implements the AUDIOCONTROL Subclass  */
		    0x00U,                             /*The interface doesn't use any class-specific protocols  */
		    0x00U,                             /* The device doesn't have a string descriptor describing this iInterface  */






			/*--------------------------------------- Audio Class Specific  Interface Descriptor--------------------------------*/
		    USB_AUDIO_CONTROL_INTERFACE_HEADER_LENGTH,   /* Size of the descriptor, in bytes  */
		    0x24,      /* CS_INTERFACE Descriptor Type   */
		    0x01, /* HEADER descriptor subtype   */
		    0x00U, 0x01U, /* Audio Device compliant to the USB Audio specification version 1.00  */
		    0x09U, 0x00U,  /* Total number of bytes returned for the class-specific AudioControl interface descriptor.
		                     Includes the combined length of this descriptor header and all Unit and Terminal
		                     descriptors. */
		    0x01U,        /* The number of AudioStreaming and MIDIStreaming interfaces in the Audio Interface Collection to
		                     which this AudioControl interface belongs   */
		    0x01U,        /* The number of AudioStreaming and MIDIStreaming interfaces in the Audio Interface baNumber */





			/*---------------------------------------Standard MS Interface Descriptor--------------------------------*/
			0x09,//bLength
			0x04,//bDescriptorType			:インターフェイスなので0x04
			0x01,//bInterfaceNumber		:このインターフェイスの番号
			0x00,//bAlternateSetting
			0x02,//bNumEndpoints    		:エンドポイントの数（デフォルトパイプを含まない）
			0x01,//bInterfaceClass     		:Audio Class
			0x03,//bInterfaceSubClass
			0x00,//bInterfaceProtocol
			0x00,//iInferface



			/*---------------------------------------Class-specific MS Interface Descriptor--------------------------------*/
			/*クラス固有インターフェイスディスクリプタのwTotalLengthはこのクラスの長さを含むCSディスクリプタの長さを入れる。
			 *外部ジャック、内部ジャックの設定が変わるときはwTotalLengthが変わるので注意する。
			 *この場合
			 *MIDI IN Jack Descriptor Embedded(6)
			 *MIDI IN Jack Descriptor external(6)
			 *MIDI OUT Jack Descriptor Embedded(9)
			 *MIDI MIDI OUT Jack Descriptor External(9)
			 *自身のbLength(7)を加えて37byteになるので0x25
			 * */
			0x07,      //bLength
			0x24,      //bDescriptorType
			0x01,	   //bDescriptorSubType
			0x00,0x01, //bcdMSC
			0x25,0x00, //wTotalLength

			/*MIDI IN Jack Descriptor Embedded*/
			0x06,//bLength
			0x24,//bDescriptorType
			0x02,//bDescriptorSubType
			0x01,//bJackType
			0x01,//bJackID
			0x00,//iJack

			/*MIDI IN Jack Descriptor external*/
			0x06,//bLength
			0x24,//bDescriptorType
			0x02,//bDescriptorSubType
			0x02,//bJackType
			0x02,//bJackID
			0x00,//iJack

			/*MIDI OUT Jack Descriptor Embedded*/
			0x09,//bLength
			0x24,//bDescriptorType
			0x03,//bDescriptorSubType
			0x01,//bJackType
			0x03,//bJackID
			0x01,//bNrInputPins
			0x02,//baSourceID(1)
			0x01,//baSourcePin(1)
			0x00,//iJack

			/*MIDI OUT Jack Descriptor External*/
			0x09,//bLength
			0x24,//bDescriptorType
			0x03,//bDescriptorSubType
			0x02,//bJackType
			0x04,//bJackID
			0x01,//bNrInputPins
			0x01,//baSourceID(1)
			0x01,//baSourcePin(1)
			0x00,//iJack



			/*-----------------------------------------------Endpoint Descriptor--------------------------------------------------------------------*/
			/*MIDI Adapter Standard Bulk OUT Endpoint Descriptor*/
			0x09,//blength
			0x05,//bDescripterType    : ENDPOINT
			0x02,//bEndpointAddress   :
			0x02,//bmAttributes       : Bulk endpoint
			0x40,//wMaxPacketSize     : 0x0040 -> care endian(0x40,0x00)
			0x00,
			0x00,//bInterval          : No use(bulk endpoint)
			0x00,//bRefresh           : No use
			0x00,//bSynchAddress      : No use

			/*MIDI Adapter Class-specific Bulk OUT Endpoint Descriptor*/
			0x05,//blength
			0x25,//bDescripterType    : CS_ENDPOINT
			0x01,//bDescriptorSubType : MS_GENERAL
			0x01,//bNumEmbMIDIJack    : Number of Embedded MIDI jack
			0x01,//baAssocJack        : ID of the last Embedded Jack that is associated with this endpoint

			/* MIDI Adapter Standard Bulk IN Endpoint Descriptor*/
			0x09,//bLength
			0x05,//bDescripterType    : ENDPOINT
			0x82,//bEndpointAddress   :
			0x02,//bmAttributes       : Bulk endpoint
			0x40,//wMaxPacketSize     : 0x0040 -> care endian(0x40,0x00)
			0x00,//
			0x00,//bInterval          : No use(bulk endpoint)
			0x00,//bRefresh           : No use
			0x00,//bSynchAddress      : No use

			/*MIDI Adapter Class-specific Bulk IN Endpoint Descriptor*/
			0x05,//blength
			0x25,//bDescripterType    : CS_ENDPOINT
			0x01,//bDescriptorSubType : MS_GENERAL
			0x01,//bNumEmbMIDIJack    : Number of Embedded MIDI jack
			0x03,//baAssocJack        : ID of the last Embedded Jack that is associated with this endpoint

			/*Audio Class Specific Descriptor Types(bDescripterType)*/
			/*Reference from USB Device Class Definition for Audio Devices PDF page 99 Appendix A*/
			//0x20 -> CS_UNDIFINED
			//0x21 -> CS_DEVICE
			//0x22 -> CS_CONFIGURATION
			//0x23 -> CS_STRING
			//0x24 -> CS_INTERFACE
			//0x25 -> CS_ENDPOINT

			/*MS Class-Specific Interface Descriptor Subtypes(bDescriptorSubType)*/
			/*Reference from USB Device Class Definition for MIDI Devices PDF page 36 Appendix A*/
			//0x00 -> MS_DESCRIPTOR_UNDEFINED
			//0x01 -> MS_HEADER
			//0x02 -> MIDI_IN_JACK
			//0x03 -> MIDI_OUT_JACK
			//0x04 -> ELEMENT

			/*MS Class-Specific Endpoint Descriptor Subtypes(bDescriptorSubType)*/
			/*Reference from USB Device Class Definition for MIDI Devices PDF page 36 Appendix A*/
			//0x00 -> DESCRIPTOR_UNDEFINED
			//0x01 -> MS_GENERAL

			/*MS MIDI IN and OUT Jack types(bJackType)*/
			/*Reference from USB Device Class Definition for MIDI Devices PDF page 36 Appendix A*/
			//0x00 -> JACK_TYPE_UNDEFINED
			//0x01 -> EMBEDDED
			//0x02 -> EXTERNAL

			/*MIDI Adapter Standard Bulk Endpoint Address(bEndpointAddress)*/

			/*D7   : Direction*/
			//	0  : OUT endpoint
			//  1  : IN  endpoint
			/*D6..4 : Reserved , reset to zero*/
			/*D3..0 : The endpoint number ,determined by the designer.*/
			//for example 0x81(0b10000001) Direction is IN , endpoint number is 1 (IN EP 1)
};

/* Define string descriptor */
USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
uint8_t g_UsbDeviceString0[] = {
    2U + 2U, USB_DESCRIPTOR_TYPE_STRING, 0x09U, 0x04U,
};

USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
uint8_t g_UsbDeviceString1[] = {
    2U + 2U * 18U, USB_DESCRIPTOR_TYPE_STRING,
    'N',           0x00U,
    'X',           0x00U,
    'P',           0x00U,
    ' ',           0x00U,
    'S',           0x00U,
    'E',           0x00U,
    'M',           0x00U,
    'I',           0x00U,
    'C',           0x00U,
    'O',           0x00U,
    'N',           0x00U,
    'D',           0x00U,
    'U',           0x00U,
    'C',           0x00U,
    'T',           0x00U,
    'O',           0x00U,
    'R',           0x00U,
    'S',           0x00U,
};

USB_DMA_INIT_DATA_ALIGN(USB_DATA_ALIGN_SIZE)
uint8_t g_UsbDeviceString2[] = {
    2U + 2U * 14U, USB_DESCRIPTOR_TYPE_STRING,
    'U',           0x00U,
    'S',           0x00U,
    'B',           0x00U,
    ' ',           0x00U,
    'A',           0x00U,
    'U',           0x00U,
    'D',           0x00U,
    'I',           0x00U,
    'O',           0x00U,
    ' ',           0x00U,
    'D',           0x00U,
    'E',           0x00U,
    'M',           0x00U,
    'O',           0x00U,
};

uint32_t g_UsbDeviceStringDescriptorLength[USB_DEVICE_STRING_COUNT] = {
    sizeof(g_UsbDeviceString0), sizeof(g_UsbDeviceString1), sizeof(g_UsbDeviceString2),
};

uint8_t *g_UsbDeviceStringDescriptorArray[USB_DEVICE_STRING_COUNT] = {
    g_UsbDeviceString0, g_UsbDeviceString1, g_UsbDeviceString2,
};

usb_language_t g_UsbDeviceLanguage[USB_DEVICE_LANGUAGE_COUNT] = {{
    g_UsbDeviceStringDescriptorArray, g_UsbDeviceStringDescriptorLength, (uint16_t)0x0409U,
}};

usb_language_list_t g_UsbDeviceLanguageList = {
    g_UsbDeviceString0, sizeof(g_UsbDeviceString0), g_UsbDeviceLanguage, USB_DEVICE_LANGUAGE_COUNT,
};

/*******************************************************************************
* Code
******************************************************************************/
/*!
 * @brief USB device get device descriptor function.
 *
 * This function gets the device descriptor of the USB device.
 *
 * @param handle The USB device handle.
 * @param deviceDescriptor The pointer to the device descriptor structure.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceGetDeviceDescriptor(usb_device_handle handle,
                                           usb_device_get_device_descriptor_struct_t *deviceDescriptor)
{
    deviceDescriptor->buffer = g_UsbDeviceDescriptor;
    deviceDescriptor->length = USB_DESCRIPTOR_LENGTH_DEVICE;
    return kStatus_USB_Success;
}

/*!
 * @brief USB device get configuration descriptor function.
 *
 * This function gets the configuration descriptor of the USB device.
 *
 * @param handle The USB device handle.
 * @param configurationDescriptor The pointer to the configuration descriptor structure.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceGetConfigurationDescriptor(
    usb_device_handle handle, usb_device_get_configuration_descriptor_struct_t *configurationDescriptor)
{
    if (USB_AUDIO_GENERATOR_CONFIGURE_INDEX > configurationDescriptor->configuration)
    {
        configurationDescriptor->buffer = g_UsbDeviceConfigurationDescriptor;
        configurationDescriptor->length = USB_DESCRIPTOR_LENGTH_CONFIGURATION_ALL;
        return kStatus_USB_Success;
    }
    return kStatus_USB_InvalidRequest;
}

/*!
 * @brief USB device get string descriptor function.
 *
 * This function gets the string descriptor of the USB device.
 *
 * @param handle The USB device handle.
 * @param stringDescriptor The pointer to the string descriptor structure.
 *
 * @return A USB error code or kStatus_USB_Success.
 */
usb_status_t USB_DeviceGetStringDescriptor(usb_device_handle handle,
                                           usb_device_get_string_descriptor_struct_t *stringDescriptor)
{
    if (stringDescriptor->stringIndex == 0U)
    {
        stringDescriptor->buffer = (uint8_t *)g_UsbDeviceLanguageList.languageString;
        stringDescriptor->length = g_UsbDeviceLanguageList.stringLength;
    }
    else
    {
        uint8_t languageId = 0U;
        uint8_t languageIndex = USB_DEVICE_STRING_COUNT;

        for (; languageId < USB_DEVICE_LANGUAGE_COUNT; languageId++)
        {
            if (stringDescriptor->languageId == g_UsbDeviceLanguageList.languageList[languageId].languageId)
            {
                if (stringDescriptor->stringIndex < USB_DEVICE_STRING_COUNT)
                {
                    languageIndex = stringDescriptor->stringIndex;
                }
                break;
            }
        }

        if (USB_DEVICE_STRING_COUNT == languageIndex)
        {
            return kStatus_USB_InvalidRequest;
        }
        stringDescriptor->buffer = (uint8_t *)g_UsbDeviceLanguageList.languageList[languageId].string[languageIndex];
        stringDescriptor->length = g_UsbDeviceLanguageList.languageList[languageId].length[languageIndex];
    }
    return kStatus_USB_Success;
}

/* Due to the difference of HS and FS descriptors, the device descriptors and configurations need to be updated to match
 * current speed.
 * As the default, the device descriptors and configurations are configured by using FS parameters for both EHCI and
 * KHCI.
 * When the EHCI is enabled, the application needs to call this function to update device by using current speed.
 * The updated information includes endpoint max packet size, endpoint interval, etc. */
usb_status_t USB_DeviceSetSpeed(usb_device_handle handle, uint8_t speed)
{
    if (USB_SPEED_HIGH == speed)
    {
        //g_UsbDeviceAudioSpeakerEndpoints[0].maxPacketSize = (HS_ISO_OUT_ENDP_PACKET_SIZE);
    	g_UsbDeviceAudioMIDI_STEREAM_Endpoints[0].maxPacketSize = 512;
    	g_UsbDeviceAudioMIDI_STEREAM_Endpoints[1].maxPacketSize = 512;
        }
    else
    {
        //g_UsbDeviceAudioSpeakerEndpoints[0].maxPacketSize = (FS_ISO_OUT_ENDP_PACKET_SIZE);
    	g_UsbDeviceAudioMIDI_STEREAM_Endpoints[0].maxPacketSize = 64;
    	g_UsbDeviceAudioMIDI_STEREAM_Endpoints[1].maxPacketSize = 64;
    }
    return kStatus_USB_Success;
}
