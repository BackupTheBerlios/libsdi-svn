/**************************************************************************

Module Name:

   SDI.H

Abstract:
   
   This file contains constants and data structure definitions used by
   drivers that support the SAS Driver Interface specification for SAS
   or SATA in either the Windows or Linux.

   This should be considered as a reference implementation
   only. Changes may be necessary to accommodate a specific build
   environment or target OS.

**************************************************************************/

#ifndef _SDI_H_
#define _SDI_H_



// SDI Specification Revision, the intent is that all versions of the
// specification will be backward compatible after the 1.00 release.
// Major revision number, corresponds to xxxx. of SDI specification
// Minor revision number, corresponds to .xxxx of SDI specification
#define SDI_MAJOR_REVISION    0
#define SDI_MINOR_REVISION    82

/*************************************************************************/
/* TARGET OS LINUX SPECIFIC CODE                                         */
/*************************************************************************/

#ifdef __linux
// Linux base types
#include <linux/types.h>

#ifndef __i8
#define __i8 __s8
#endif

// pack definition

#define SDI_BEGIN_PACK(x)    pack(x)
#define SDI_END_PACK         pack()

// IOCTL Control Codes
// used as the ioctl() request parameter
// Control Codes requiring SDI_ALL_SIGNATURE

#define CC_SDI_GET_DRIVER_INFO    0xCC770001
#define CC_SDI_GET_CNTLR_CONFIG   0xCC770002
#define CC_SDI_GET_CNTLR_STATUS   0xCC770003
#define CC_SDI_FIRMWARE_DOWNLOAD  0xCC770004

// Control Codes requiring SDI_RAID_SIGNATURE
#define CC_SDI_GET_RAID_INFO      0xCC77000A
#define CC_SDI_GET_RAID_CONFIG    0xCC77000B

// Control Codes requiring SDI_SIGNATURE
#define CC_SDI_GET_PHY_INFO       0xCC770014
#define CC_SDI_SET_PHY_INFO       0xCC770015
#define CC_SDI_GET_LINK_ERRORS    0xCC770016
#define CC_SDI_SMP_PASSTHROUGH    0xCC770017
#define CC_SDI_SSP_PASSTHROUGH    0xCC770018
#define CC_SDI_STP_PASSTHROUGH    0xCC770019
#define CC_SDI_GET_SATA_SIGNATURE 0xCC770020
#define CC_SDI_GET_SCSI_ADDRESS   0xCC770021
#define CC_SDI_GET_DEVICE_ADDRESS 0xCC770022
#define CC_SDI_TASK_MANAGEMENT    0xCC770023
#define CC_SDI_GET_CONNECTOR_INFO 0xCC770024

// Control Codes requiring SDI_PHY_SIGNATURE
#define CC_SDI_PHY_CONTROL        0xCC77003C

#pragma SDI_BEGIN_PACK(8)

// IOCTL_HEADER
typedef struct _IOCTL_HEADER {
   __u32 IOControllerNumber;// FIXFIX add a space
__u32 Length;
__u32 ReturnCode;
__u32 Timeout;
__u16 Direction;
} IOCTL_HEADER, *PIOCTL_HEADER;
#pragma SDI_END_PACK

#endif  //# linux

/*************************************************************************/
/* TARGET OS WINDOWS SPECIFIC CODE                                        */
/*************************************************************************/

#ifdef _WIN32

// windows IOCTL definitions

#ifndef _NTDDSCSIH_
#include <ntddscsi.h>
#endif

// pack definition

#if defined _MSC_VER
   #define SDI_BEGIN_PACK(x)    pack(push,x)
   #define SDI_END_PACK         pack(pop)
#elif defined __BORLANDC__
   #define SDI_BEGIN_PACK(x)    option -a##x
   #define SDI_END_PACK         option -a.
#else
   #error "SDISAS.H - Must externally define a pack compiler designator."
#endif

// base types

#define __u8    unsigned char
#define __u32   unsigned long
#define __u16   unsigned short

#define __i8    char

// IOCTL Control Codes
// (IoctlHeader.ControlCode)

// Control Codes requiring SDI_ALL_SIGNATURE
#define CC_SDI_GET_DRIVER_INFO     1
#define CC_SDI_GET_CNTLR_CONFIG    2
#define CC_SDI_GET_CNTLR_STATUS    3
#define CC_SDI_FIRMWARE_DOWNLOAD   4

// Control Codes requiring SDI_RAID_SIGNATURE
#define CC_SDI_GET_RAID_INFO       10
#define CC_SDI_GET_RAID_CONFIG     11

// Control Codes requiring SDI_SIGNATURE
#define CC_SDI_GET_PHY_INFO        20
#define CC_SDI_SET_PHY_INFO        21
#define CC_SDI_GET_LINK_ERRORS     22
#define CC_SDI_SMP_PASSTHROUGH     23
#define CC_SDI_SSP_PASSTHROUGH     24
#define CC_SDI_STP_PASSTHROUGH     25
#define CC_SDI_GET_SATA_SIGNATURE  26
#define CC_SDI_GET_SCSI_ADDRESS    27
#define CC_SDI_GET_DEVICE_ADDRESS  28
#define CC_SDI_TASK_MANAGEMENT     29
#define CC_SDI_GET_CONNECTOR_INFO  30

// Control Codes requiring SDI_PHY_SIGNATURE
#define CC_SDI_PHY_CONTROL         60

#define IOCTL_HEADER SRB_IO_CONTROL
#define PIOCTL_HEADER PSRB_IO_CONTROL

#endif //# _WIN32

/*************************************************************************/
/* TARGET OS NOT DEFINED ERROR                                           */
/*************************************************************************/

#if (!_WIN32 && !__linux)
   #error "Unknown target OS."
#endif

/*************************************************************************/
/* OS INDEPENDENT CODE                                                   */
/*************************************************************************/

/* * * * * * * * * * Class Independent IOCTL Constants * * * * * * * * * */

// Return codes for all IOCTL's regardless of class
// (IoctlHeader.ReturnCode)

#define SDI_STATUS_SUCCESS              0
#define SDI_STATUS_FAILED               1
#define SDI_STATUS_BAD_CNTL_CODE        2
#define SDI_STATUS_INVALID_PARAMETER    3
#define SDI_STATUS_WRITE_ATTEMPTED      4

// Signature value
// (IoctlHeader.Signature)

#define SDI_ALL_SIGNATURE    "SDIALL"

// Timeout value default of 60 seconds
// (IoctlHeader.Timeout)

#define SDI_ALL_TIMEOUT      60

// Direction values for data flow on this IOCTL
// (IoctlHeader.Direction, Linux only)
#define SDI_DATA_READ     0
#define SDI_DATA_WRITE    1

// I/O Bus Types
// ISA and EISA bus types are not supported
// (bIoBusType)

#define SDI_BUS_TYPE_PCI        3
#define SDI_BUS_TYPE_PCMCIA     4

// Controller Status
// (uStatus)

#define SDI_CNTLR_STATUS_GOOD      1
#define SDI_CNTLR_STATUS_FAILED    2
#define SDI_CNTLR_STATUS_OFFLINE   3
#define SDI_CNTLR_STATUS_POWEROFF  4

// Offline Status Reason

// (uOfflineReason)
#define SDI_OFFLINE_REASON_NO_REASON             0
#define SDI_OFFLINE_REASON_INITIALIZING          1
#define SDI_OFFLINE_REASON_BACKSIDE_BUS_DEGRADED 2
#define SDI_OFFLINE_REASON_BACKSIDE_BUS_FAILURE  3

// Controller Class
// (bControllerClass)

#define SDI_CNTLR_CLASS_HBA     5

// Controller Flag bits
// (uControllerFlags)

#define SDI_CNTLR_SAS_HBA    0x00000001
#define SDI_CNTLR_SAS_RAID   0x00000002
#define SDI_CNTLR_SATA_HBA   0x00000004
#define SDI_CNTLR_SATA_RAID  0x00000008

// for firmware download
#define SDI_CNTLR_FWD_SUPPORT   0x00010000
#define SDI_CNTLR_FWD_ONLINE    0x00020000
#define SDI_CNTLR_FWD_SRESET    0x00040000
#define SDI_CNTLR_FWD_HRESET    0x00080000
#define SDI_CNTLR_FWD_RROM      0x00100000

// Download Flag bits
// (uDownloadFlags)
#define SDI_FWD_VALIDATE        0x00000001
#define SDI_FWD_SOFT_RESET      0x00000002
#define SDI_FWD_HARD_RESET      0x00000004

// Firmware Download Status
// (usStatus)
#define SDI_FWD_SUCCESS         0
#define SDI_FWD_FAILED          1
#define SDI_FWD_USING_RROM      2
#define SDI_FWD_REJECT          3
#define SDI_FWD_DOWNREV         4

// Firmware Download Severity
// (usSeverity>
#define SDI_FWD_INFORMATION     0
#define SDI_FWD_WARNING         1
#define SDI_FWD_ERROR           2
#define SDI_FWD_FATAL           3

/* * * * * * * * * * SAS RAID Class IOCTL Constants * * * * * * * * */

// Return codes for the RAID IOCTL's regardless of class
// (IoctlHeader.ControlCode)

#define SDI_RAID_SET_OUT_OF_RANGE       1000

// Signature value
// (IoctlHeader.Signature)

#define SDI_RAID_SIGNATURE     "SDIARY"

// Timeout value default of 60 seconds
// (IoctlHeader.Timeout)

#define SDI_RAID_TIMEOUT       60

// RAID Types
// (bRaidType)
#define SDI_RAID_TYPE_NONE      0
#define SDI_RAID_TYPE_0         1
#define SDI_RAID_TYPE_1         2
#define SDI_RAID_TYPE_10        3
#define SDI_RAID_TYPE_5         4
#define SDI_RAID_TYPE_15        5
#define SDI_RAID_TYPE_6         6
#define SDI_RAID_TYPE_OTHER     255

// RAID Status
// (bStatus)
#define SDI_RAID_SET_STATUS_OK          0
#define SDI_RAID_SET_STATUS_DEGRADED    1
#define SDI_RAID_SET_STATUS_REBUILDING  2
#define SDI_RAID_SET_STATUS_FAILED      3

// RAID Drive Status
// (bDriveStatus)
#define SDI_DRIVE_STATUS_OK           0
#define SDI_DRIVE_STATUS_REBUILDING   1
#define SDI_DRIVE_STATUS_FAILED       2
#define SDI_DRIVE_STATUS_DEGRADED     3

// RAID Drive Usage
// (bDriveUsage)
#define SDI_DRIVE_CONFIG_NOT_USED   0
#define SDI_DRIVE_CONFIG_MEMBER     1
#define SDI_DRIVE_CONFIG_SPARE      2

/* * * * * * * * * * SAS HBA Class IOCTL Constants * * * * * * * * * */

// Return codes for SAS IOCTL's
// (IoctlHeader.ReturnCode)
#define SDI_PHY_INFO_CHANGED             SDI_STATUS_SUCCESS
#define SDI_PHY_INFO_NOT_CHANGEABLE      2000
#define SDI_LINK_RATE_OUT_OF_RANGE       2001
#define SDI_PHY_DOES_NOT_EXIST           2002
#define SDI_PHY_DOES_NOT_MATCH_PORT      2003
#define SDI_PHY_CANNOT_BE_SELECTED       2004
#define SDI_SELECT_PHY_OR_PORT           2005
#define SDI_PORT_DOES_NOT_EXIST          2006
#define SDI_PORT_CANNOT_BE_SELECTED      2007
#define SDI_CONNECTION_FAILED            2008

#define SDI_NO_SATA_DEVICE               2009
#define SDI_NO_SATA_SIGNATURE            2010
#define SDI_SCSI_EMULATION               2011
#define SDI_NOT_AN_END_DEVICE            2012
#define SDI_NO_SCSI_ADDRESS              2013
#define SDI_NO_DEVICE_ADDRESS            2014

// Signature value
// (IoctlHeader.Signature)
#define SDI_SIGNATURE     "SDISAS"

// Timeout value default of 60 seconds
// (IoctlHeader.Timeout)

#define SDI_TIMEOUT       60

// Device types
// (bDeviceType)
#define SDI_PHY_UNUSED                0x00
#define SDI_NO_DEVICE_ATTACHED        0x00
#define SDI_END_DEVICE                0x10
#define SDI_EDGE_EXPANDER_DEVICE      0x20
#define SDI_FANOUT_EXPANDER_DEVICE    0x30

// Protocol options
// (bInitiatorPortProtocol,  bTargetPortProtocol)
#define SDI_PROTOCOL_SATA    0x01
#define SDI_PROTOCOL_SMP     0x02
#define SDI_PROTOCOL_STP     0x04
#define SDI_PROTOCOL_SSP     0x08

// Negotiated and hardware link rates
// (bNegotiatedLinkRate, bMinimumLinkRate, bMaximumLinkRate)
#define SDI_LINK_RATE_UNKNOWN   0x00
#define SDI_PHY_DISABLED        0x01
#define SDI_LINK_RATE_FAILED    0x02
#define SDI_SATA_SPINUP_HOLD    0x03
#define SDI_SATA_PORT_SELECTOR  0x04
#define SDI_LINK_RATE_1_5_GBPS  0x08
#define SDI_LINK_RATE_3_0_GBPS  0x09
#define SDI_LINK_VIRTUAL        0x10

// Discover state
// (bAutoDiscover)
#define SDI_DISCOVER_NOT_SUPPORTED    0x00
#define SDI_DISCOVER_NOT_STARTED      0x01
#define SDI_DISCOVER_IN_PROGRESS      0x02
#define SDI_DISCOVER_COMPLETE         0x03
#define SDI_DISCOVER_ERROR            0x04

// Programmed link rates
// (bMinimumLinkRate, bMaximumLinkRate)
// (bProgrammedMinimumLinkRate, bProgrammedMaximumLinkRate)
#define SDI_PROGRAMMED_LINK_RATE_UNCHANGED 0x00
#define SDI_PROGRAMMED_LINK_RATE_1_5_GBPS  0x08
#define SDI_PROGRAMMED_LINK_RATE_3_0_GBPS  0x09

// Link rate
// (bNegotiatedLinkRate in SDI_SET_PHY_INFO)
#define SDI_LINK_RATE_NEGOTIATE       0x00
#define SDI_LINK_RATE_PHY_DISABLED    0x01

// Signal class
// (bSignalClass in SDI_SET_PHY_INFO)
#define SDI_SIGNAL_CLASS_UNKNOWN      0x00
#define SDI_SIGNAL_CLASS_DIRECT       0x01
#define SDI_SIGNAL_CLASS_SERVER       0x02
#define SDI_SIGNAL_CLASS_ENCLOSURE    0x03

// Link error reset
// (bResetCounts)
#define SDI_LINK_ERROR_DONT_RESET_COUNTS   0x00
#define SDI_LINK_ERROR_RESET_COUNTS        0x01

// Phy identifier
// (bPhyIdentifier)
#define SDI_USE_PORT_IDENTIFIER    0xFF

// Port identifier
// (bPortIdentifier)
#define SDI_IGNORE_PORT            0xFF

// Programmed link rates
// (bConnectionRate)
#define SDI_LINK_RATE_NEGOTIATED   0x00
#define SDI_LINK_RATE_1_5_GBPS     0x08
#define SDI_LINK_RATE_3_0_GBPS     0x09

// Connection status
// (bConnectionStatus)
#define SDI_OPEN_ACCEPT                          0
#define SDI_OPEN_REJECT_BAD_DESTINATION          1
#define SDI_OPEN_REJECT_RATE_NOT_SUPPORTED       2
#define SDI_OPEN_REJECT_NO_DESTINATION           3
#define SDI_OPEN_REJECT_PATHWAY_BLOCKED          4
#define SDI_OPEN_REJECT_PROTOCOL_NOT_SUPPORTED   5
#define SDI_OPEN_REJECT_RESERVE_ABANDON          6
#define SDI_OPEN_REJECT_RESERVE_CONTINUE         7
#define SDI_OPEN_REJECT_RESERVE_INITIALIZE       8
#define SDI_OPEN_REJECT_RESERVE_STOP             9
#define SDI_OPEN_REJECT_RETRY                    10
#define SDI_OPEN_REJECT_STP_RESOURCES_BUSY       11
#define SDI_OPEN_REJECT_WRONG_DESTINATION        12

// SSP Flags
// (uFlags)
#define SDI_SSP_READ                           0x00000001
#define SDI_SSP_WRITE                          0x00000002
#define SDI_SSP_UNSPECIFIED                    0x00000004
#define SDI_SSP_TASK_ATTRIBUTE_SIMPLE          0x00000000
#define SDI_SSP_TASK_ATTRIBUTE_HEAD_OF_QUEUE   0x00000010
#define SDI_SSP_TASK_ATTRIBUTE_ORDERED         0x00000020
#define SDI_SSP_TASK_ATTRIBUTE_ACA             0x00000040

// SSP Data present
// (bDataPresent)
#define SDI_SSP_NO_DATA_PRESENT          0x00
#define SDI_SSP_RESPONSE_DATA_PRESENT    0x01
#define SDI_SSP_SENSE_DATA_PRESENT       0x02

// STP Flags
// (uFlags)
#define SDI_STP_READ            0x00000001
#define SDI_STP_WRITE           0x00000002
#define SDI_STP_UNSPECIFIED     0x00000004
#define SDI_STP_PIO             0x00000010
#define SDI_STP_DMA             0x00000020
#define SDI_STP_PACKET          0x00000040
#define SDI_STP_DMA_QUEUED      0x00000080
#define SDI_STP_EXECUTE_DIAG    0x00000100
#define SDI_STP_RESET_DEVICE    0x00000200

// Task Management Flags
// (uFlags)
#define SDI_TASK_IU                0x00000001
#define SDI_HARD_RESET_SEQUENCE    0x00000002
#define SDI_SUPPRESS_RESULT        0x00000004

// Task Management Functions
// (bTaskManagement)
#define SDI_SSP_ABORT_TASK            0x01
#define SDI_SSP_ABORT_TASK_SET        0x02
#define SDI_SSP_CLEAR_TASK_SET        0x04
#define SDI_SSP_LOGICAL_UNIT_RESET    0x08
#define SDI_SSP_CLEAR_ACA             0x40
#define SDI_SSP_QUERY_TASK            0x80

// Task Management Information
// (uInformation)
#define SDI_SSP_TEST            1
#define SDI_SSP_EXCEEDED        2
#define SDI_SSP_DEMAND          3
#define SDI_SSP_TRIGGER         4

// Connector Pinout Information
// (uPinout)
#define SDI_CON_UNKNOWN               0x00000001
#define SDI_CON_SFF_8482              0x00000002
#define SDI_CON_SFF_8470_LANE_1       0x00000100
#define SDI_CON_SFF_8470_LANE_2       0x00000200
#define SDI_CON_SFF_8470_LANE_3       0x00000400
#define SDI_CON_SFF_8470_LANE_4       0x00000800
#define SDI_CON_SFF_8484_LANE_1       0x00010000
#define SDI_CON_SFF_8484_LANE_2       0x00020000
#define SDI_CON_SFF_8484_LANE_3       0x00040000
#define SDI_CON_SFF_8484_LANE_4       0x00080000

// Connector Location Information
// (bLocation)

// same as uPinout above...
// #define SDI_CON_UNKNOWN                0x01
#define SDI_CON_INTERNAL               0x02
#define SDI_CON_EXTERNAL               0x04
#define SDI_CON_SWITCHABLE             0x08
#define SDI_CON_AUTO                   0x10
#define SDI_CON_NOT_PRESENT            0x20
#define SDI_CON_NOT_CONNECTED          0x80

/* * * * * * * * SAS Phy Control Class IOCTL Constants * * * * * * * * */

// Return codes for SAS Phy Control IOCTL's
// (IoctlHeader.ReturnCode)

// Signature value
// (IoctlHeader.Signature)
#define SDI_PHY_SIGNATURE     "SDIPHY"

// Phy Control Functions
// (bFunction)

// values 0x00 to 0xFF are consistent in definition with the SMP PHY CONTROL
// function defined in the SAS spec
#define SDI_PC_NOP                     0x00000000
#define SDI_PC_LINK_RESET              0x00000001
#define SDI_PC_HARD_RESET              0x00000002
#define SDI_PC_PHY_DISABLE             0x00000003
// 0x04 to 0xFF reserved...
#define SDI_PC_GET_PHY_SETTINGS        0x00000100

// Link Flags
#define SDI_PHY_ACTIVATE_CONTROL       0x00000001
#define SDI_PHY_UPDATE_SPINUP_RATE     0x00000002
#define SDI_PHY_AUTO_COMWAKE           0x00000004

// Device Types for Phy Settings
// (bType)
#define SDI_UNDEFINED  0x00
#define SDI_SATA       0x01
#define SDI_SAS        0x02

// Transmitter Flags
// (uTransmitterFlags)
#define SDI_PHY_PREEMPHASIS_DISABLED      0x00000001

// Receiver Flags
// (uReceiverFlags)
#define SDI_PHY_EQUALIZATION_DISABLED     0x00000001

// Pattern Flags
// (uPatternFlags)
// #define SDI_PHY_ACTIVATE_CONTROL      0x00000001
#define SDI_PHY_DISABLE_SCRAMBLING       0x00000002
#define SDI_PHY_DISABLE_ALIGN            0x00000004
#define SDI_PHY_DISABLE_SSC              0x00000008
#define SDI_PHY_FIXED_PATTERN            0x00000010
#define SDI_PHY_USER_PATTERN             0x00000020

// Fixed Patterns
// (bFixedPattern)
#define SDI_PHY_CJPAT                    0x00000001
#define SDI_PHY_ALIGN                    0x00000002

// Type Flags
// (bTypeFlags)
#define SDI_PHY_POSITIVE_DISPARITY       0x01
#define SDI_PHY_NEGATIVE_DISPARITY       0x02
#define SDI_PHY_CONTROL_CHARACTER        0x04

// Miscellaneous
#define SLOT_NUMBER_UNKNOWN   0xFFFF

/*************************************************************************/
/* DATA STRUCTURES                                                       */
/*************************************************************************/

/* * * * * * * * * * Class Independent Structures * * * * * * * * * */

#pragma SDI_BEGIN_PACK(8)

// CC_SDI_DRIVER_INFO
typedef struct _SDI_DRIVER_INFO {
   __u8 szName[81];
   __u8 szDescription[81];
   __u16 usMajorRevision;
   __u16 usMinorRevision;
   __u16 usBuildRevision;
   __u16 usReleaseRevision;
   __u16 usSDIMajorRevision;
   __u16 usSDIMinorRevision;
} SDI_DRIVER_INFO, *PSDI_DRIVER_INFO;

typedef struct _SDI_DRIVER_INFO_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_DRIVER_INFO Information;
} SDI_DRIVER_INFO_BUFFER, *PSDI_DRIVER_INFO_BUFFER;

// CC_SDI_CNTLR_CONFIGURATION
typedef struct _SDI_PCI_BUS_ADDRESS {
   __u8 bBusNumber;
   __u8 bDeviceNumber;
   __u8 bFunctionNumber;
   __u8 bReserved;
} SDI_PCI_BUS_ADDRESS, *PSDI_PCI_BUS_ADDRESS;

typedef union _SDI_IO_BUS_ADDRESS {
   SDI_PCI_BUS_ADDRESS PciAddress;
   __u8 bReserved[32];
} SDI_IO_BUS_ADDRESS, *PSDI_IO_BUS_ADDRESS;

typedef struct _SDI_CNTLR_CONFIG {
   __u32 uBaseIoAddress;
   struct {
      __u32 uLowPart;
      __u32 uHighPart;
   } BaseMemoryAddress;
   __u32 uBoardID;
   __u16 usSlotNumber;
   __u8 bControllerClass;
   __u8 bIoBusType;
   SDI_IO_BUS_ADDRESS BusAddress;
   __u8 szSerialNumber[81];
   __u16 usMajorRevision;
   __u16 usMinorRevision;
   __u16 usBuildRevision;
   __u16 usReleaseRevision;
   __u16 usBIOSMajorRevision;
   __u16 usBIOSMinorRevision;
   __u16 usBIOSBuildRevision;
   __u16 usBIOSReleaseRevision;
   __u32 uControllerFlags;
   __u16 usRromMajorRevision;
   __u16 usRromMinorRevision;
   __u16 usRromBuildRevision;
   __u16 usRromReleaseRevision;
   __u16 usRromBIOSMajorRevision;
   __u16 usRromBIOSMinorRevision;
   __u16 usRromBIOSBuildRevision;
   __u16 usRromBIOSReleaseRevision;
   __u8 bReserved[7];
} SDI_CNTLR_CONFIG, *PSDI_CNTLR_CONFIG;

typedef struct _SDI_CNTLR_CONFIG_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_CNTLR_CONFIG Configuration;
} SDI_CNTLR_CONFIG_BUFFER, *PSDI_CNTLR_CONFIG_BUFFER;

// CC_SDI_CNTLR_STATUS
typedef struct _SDI_CNTLR_STATUS {
   __u32 uStatus;
   __u32 uOfflineReason;
   __u8 bReserved[28];
} SDI_CNTLR_STATUS, *PSDI_CNTLR_STATUS;

typedef struct _SDI_CNTLR_STATUS_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_CNTLR_STATUS Status;
} SDI_CNTLR_STATUS_BUFFER, *PSDI_CNTLR_STATUS_BUFFER;

// CC_SDI_FIRMWARE_DOWNLOAD
typedef struct _SDI_FIRMWARE_DOWNLOAD {
   __u32 uBufferLength;
   __u32 uDownloadFlags;
   __u8 bReserved[32];
   __u16 usStatus;
   __u16 usSeverity;
} SDI_FIRMWARE_DOWNLOAD,   *PSDI_FIRMWARE_DOWNLOAD;

typedef struct _SDI_FIRMWARE_DOWNLOAD_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_FIRMWARE_DOWNLOAD Information;
   __u8 bDataBuffer[1];
} SDI_FIRMWARE_DOWNLOAD_BUFFER, *PSDI_FIRMWARE_DOWNLOAD_BUFFER;

// CC_SDI_RAID_INFO
typedef struct _SDI_RAID_INFO {
   __u32 uNumRaidSets;
   __u32 uMaxDrivesPerSet;
   __u8 bReserved[92];
} SDI_RAID_INFO, *PSDI_RAID_INFO;

typedef struct _SDI_RAID_INFO_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_RAID_INFO Information;
} SDI_RAID_INFO_BUFFER, *PSDI_RAID_INFO_BUFFER;

// CC_SDI_GET_RAID_CONFIG
typedef struct _SDI_RAID_DRIVES {
   __u8 bModel[40];
   __u8 bFirmware[8];
   __u8 bSerialNumber[40];
   __u8 bSASAddress[8];
   __u8 bSASLun[8];
   __u8 bDriveStatus;
   __u8 bDriveUsage;
   __u8 bReserved[30];
} SDI_RAID_DRIVES,    *PSDI_RAID_DRIVES;

typedef struct _SDI_RAID_CONFIG {
   __u32 uRaidSetIndex;
   __u32 uCapacity;
   __u32 uStripeSize;
   __u8 bRaidType;
   __u8 bStatus;
   __u8 bInformation;
   __u8 bDriveCount;
   __u8 bReserved[20];
   SDI_RAID_DRIVES Drives[1];
} SDI_RAID_CONFIG,    *PSDI_RAID_CONFIG;

typedef struct _SDI_RAID_CONFIG_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_RAID_CONFIG Configuration;
} SDI_RAID_CONFIG_BUFFER, *PSDI_RAID_CONFIG_BUFFER;

/* * * * * * * * * * SAS HBA Class Structures * * * * * * * * * */

// CC_SDI_GET_PHY_INFO
typedef struct _SDI_IDENTIFY {
   __u8 bDeviceType;
   __u8 bRestricted_Byte1;
   __u8 bInitiatorPortProtocol;
   __u8 bTargetPortProtocol;
   __u8 bRestricted_Bytes4to11[8];
   __u8 bSASAddress[8];
   __u8 bPhyIdentifier;
   __u8 bSignalClass;
   __u8 bReserved_Bytes22to27[6];
} SDI_IDENTIFY, *PSDI_IDENTIFY;

typedef struct _SDI_PHY_ENTITY {
   SDI_IDENTIFY Identify;
   __u8 bPortIdentifier;
   __u8 bNegotiatedLinkRate;
   __u8 bMinimumLinkRate;
   __u8 bMaximumLinkRate;
   __u8 bPhyChangeCount;
   __u8 bAutoDiscover;
   __u8 bReserved[2];
   SDI_IDENTIFY Attached;
} SDI_PHY_ENTITY, *PSDI_PHY_ENTITY;

typedef struct _SDI_PHY_INFO {
   __u8 bNumberOfPhys;
   __u8 bReserved[3];
   SDI_PHY_ENTITY Phy[32];
} SDI_PHY_INFO, *PSDI_PHY_INFO;

typedef struct _SDI_PHY_INFO_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_PHY_INFO Information;
} SDI_PHY_INFO_BUFFER, *PSDI_PHY_INFO_BUFFER;

// CC_SDI_SET_PHY_INFO
typedef struct _SDI_SET_PHY_INFO {
   __u8 bPhyIdentifier;
   __u8 bNegotiatedLinkRate;
   __u8 bProgrammedMinimumLinkRate;
   __u8 bProgrammedMaximumLinkRate;
   __u8 bSignalClass;
   __u8 bReserved[3];
} SDI_SET_PHY_INFO, *PSDI_SET_PHY_INFO;

typedef struct _SDI_SET_PHY_INFO_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_SET_PHY_INFO Information;
} SDI_SET_PHY_INFO_BUFFER, *PSDI_SET_PHY_INFO_BUFFER;

// CC_SDI_GET_LINK_ERRORS
typedef struct _SDI_LINK_ERRORS {
   __u8 bPhyIdentifier;
   __u8 bResetCounts;
   __u8 bReserved[2];
   __u32 uInvalidDwordCount;
   __u32 uRunningDisparityErrorCount;
   __u32 uLossOfDwordSyncCount;
   __u32 uPhyResetProblemCount;
} SDI_LINK_ERRORS, *PSDI_LINK_ERRORS;

typedef struct _SDI_LINK_ERRORS_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_LINK_ERRORS Information;
} SDI_LINK_ERRORS_BUFFER, *PSDI_LINK_ERRORS_BUFFER;

// CC_SDI_SMP_PASSTHROUGH
typedef struct _SDI_SMP_REQUEST {
   __u8 bFrameType;
   __u8 bFunction;
   __u8 bReserved[2];
   __u8 bAdditionalRequestBytes[1016];
} SDI_SMP_REQUEST, *PSDI_SMP_REQUEST;

typedef struct _SDI_SMP_RESPONSE {
   __u8 bFrameType;
   __u8 bFunction;
   __u8 bFunctionResult;
   __u8 bReserved;
   __u8 bAdditionalResponseBytes[1016];
} SDI_SMP_RESPONSE, *PSDI_SMP_RESPONSE;

typedef struct _SDI_SMP_PASSTHROUGH {
   __u8 bPhyIdentifier;
   __u8 bPortIdentifier;
   __u8 bConnectionRate;
   __u8 bReserved;
   __u8 bDestinationSASAddress[8];
   __u32 uRequestLength;
   SDI_SMP_REQUEST Request;
   __u8 bConnectionStatus;
   __u8 bReserved2[3];
   __u32 uResponseBytes;
   SDI_SMP_RESPONSE Response;
} SDI_SMP_PASSTHROUGH, *PSDI_SMP_PASSTHROUGH;

typedef struct _SDI_SMP_PASSTHROUGH_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_SMP_PASSTHROUGH Parameters;
} SDI_SMP_PASSTHROUGH_BUFFER, *PSDI_SMP_PASSTHROUGH_BUFFER;

// CC_SDI_SSP_PASSTHROUGH
typedef struct _SDI_SSP_PASSTHROUGH {
   __u8 bPhyIdentifier;
   __u8 bPortIdentifier;
   __u8 bConnectionRate;
   __u8 bReserved;
   __u8 bDestinationSASAddress[8];
   __u8 bLun[8];
   __u8 bCDBLength;
   __u8 bAdditionalCDBLength;
   __u8 bReserved2[2];
   __u8 bCDB[16];
   __u32 uFlags;
   __u8 bAdditionalCDB[24];
   __u32 uDataLength;
} SDI_SSP_PASSTHROUGH,  *PSDI_SSP_PASSTHROUGH;

typedef struct _SDI_SSP_PASSTHROUGH_STATUS {
   __u8 bConnectionStatus;
   __u8 bReserved[3];
   __u8 bDataPresent;
   __u8 bStatus;
   __u8 bResponseLength[2];
   __u8 bResponse[256];
} SDI_SSP_PASSTHROUGH_STATUS, *PSDI_SSP_PASSTHROUGH_STATUS;

typedef struct _SDI_SSP_PASSTHROUGH_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_SSP_PASSTHROUGH Parameters;
   SDI_SSP_PASSTHROUGH_STATUS Status;
   __u32 uDataBytes;
   __u8 bDataBuffer[1];
} SDI_SSP_PASSTHROUGH_BUFFER, *PSDI_SSP_PASSTHROUGH_BUFFER;

// CC_SDI_STP_PASSTHROUGH
typedef struct _SDI_STP_PASSTHROUGH {
   __u8 bPhyIdentifier;
   __u8 bPortIdentifier;
   __u8 bConnectionRate;
   __u8 bReserved;
   __u8 bDestinationSASAddress[8];
   __u8 bReserved2[4];
   __u8 bCommandFIS[20];
   __u32 uFlags;
   __u32 uDataLength;
} SDI_STP_PASSTHROUGH, *PSDI_STP_PASSTHROUGH;

typedef struct _SDI_STP_PASSTHROUGH_STATUS {
   __u8 bConnectionStatus;
   __u8 bReserved[3];
   __u8 bStatusFIS[20];
   __u32 uSCR[16];
} SDI_STP_PASSTHROUGH_STATUS, *PSDI_STP_PASSTHROUGH_STATUS;

typedef struct _SDI_STP_PASSTHROUGH_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_STP_PASSTHROUGH Parameters;
   SDI_STP_PASSTHROUGH_STATUS Status;
   __u32 uDataBytes;
   __u8 bDataBuffer[1];
} SDI_STP_PASSTHROUGH_BUFFER, *PSDI_STP_PASSTHROUGH_BUFFER;

// CC_SDI_GET_SATA_SIGNATURE
typedef struct _SDI_SATA_SIGNATURE {
   __u8 bPhyIdentifier;
   __u8 bReserved[3];
   __u8 bSignatureFIS[20];
} SDI_SATA_SIGNATURE, *PSDI_SATA_SIGNATURE;

typedef struct _SDI_SATA_SIGNATURE_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_SATA_SIGNATURE Signature;
} SDI_SATA_SIGNATURE_BUFFER, *PSDI_SATA_SIGNATURE_BUFFER;

// CC_SDI_GET_SCSI_ADDRESS
typedef struct _SDI_GET_SCSI_ADDRESS_BUFFER {
   IOCTL_HEADER IoctlHeader;
   __u8 bSASAddress[8];
   __u8 bSASLun[8];
   __u8 bHostIndex;
   __u8 bPathId;
   __u8 bTargetId;
   __u8 bLun;
} SDI_GET_SCSI_ADDRESS_BUFFER,    *PSDI_GET_SCSI_ADDRESS_BUFFER;

// CC_SDI_GET_DEVICE_ADDRESS
typedef struct _SDI_GET_DEVICE_ADDRESS_BUFFER {
   IOCTL_HEADER IoctlHeader;
   __u8 bHostIndex;
   __u8 bPathId;
   __u8 bTargetId;
   __u8 bLun;
   __u8 bSASAddress[8];
   __u8 bSASLun[8];
} SDI_GET_DEVICE_ADDRESS_BUFFER, *PSDI_GET_DEVICE_ADDRESS_BUFFER;

// CC_SDI_TASK_MANAGEMENT
typedef struct _SDI_SSP_TASK_IU {
   __u8 bHostIndex;
   __u8 bPathId;
   __u8 bTargetId;
   __u8 bLun;
   __u32 uFlags;
   __u32 uQueueTag;
   __u32 uReserved;
   __u8 bTaskManagementFunction;
   __u8 bReserved[7];
   __u32 uInformation;
} SDI_SSP_TASK_IU, *PSDI_SSP_TASK_IU;

typedef struct _SDI_SSP_TASK_IU_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_SSP_TASK_IU Parameters;
   SDI_SSP_PASSTHROUGH_STATUS Status;
} SDI_SSP_TASK_IU_BUFFER, *PSDI_SSP_TASK_IU_BUFFER;

// CC_SDI_GET_CONNECTOR_INFO
typedef struct _SDI_GET_CONNECTOR_INFO {
   __u32 uPinout;
   __u8 bConnector[16];
   __u8 bLocation;
   __u8 bReserved[15];
} SDI_CONNECTOR_INFO, *PSDI_CONNECTOR_INFO;

typedef struct _SDI_CONNECTOR_INFO_BUFFER {
   IOCTL_HEADER IoctlHeader;
   SDI_CONNECTOR_INFO Reference[32];
} SDI_CONNECTOR_INFO_BUFFER,   *PSDI_CONNECTOR_INFO_BUFFER;

// CC_SDI_PHY_CONTROL
typedef struct _SDI_CHARACTER {
   __u8 bTypeFlags;
   __u8 bValue;
} SDI_CHARACTER, *PSDI_CHARACTER;

typedef struct _SDI_PHY_CONTROL {
   __u8 bType;
   __u8 bRate;
   __u8 bReserved[6];
   __u32 uVendorUnique[8];
   __u32 uTransmitterFlags;
   __i8 bTransmitterAmplitude;
   __i8 bTransmitterPreemphasis;
   __i8 bTransmitterSlewRate;
   __i8 bTransmitterReserved[13];
   __u8 bTransmitterVendorUnique[64];
   __u32 uReceiverFlags;
   __i8 bReceiverThreshold;
   __i8 bReceiverEqualizationGain;
   __i8 bReceiverReserved[14];
   __u8 bReceiverVendorUnique[64];
   __u32 uPatternFlags;
   __u8 bFixedPattern;
   __u8 bUserPatternLength;
   __u8 bPatternReserved[6];
   SDI_CHARACTER UserPatternBuffer[16];
} SDI_PHY_CONTROL, *PSDI_PHY_CONTROL;

typedef struct _SDI_PHY_CONTROL_BUFFER {
   IOCTL_HEADER IoctlHeader;
   __u32 uFunction;
   __u8 bPhyIdentifier;
   __u16 usLengthOfControl;
   __u8 bNumberOfControls;
   __u8 bReserved[4];
   __u32 uLinkFlags;
   __u8 bSpinupRate;
   __u8 bLinkReserved[7];
   __u32 uVendorUnique[8];
   SDI_PHY_CONTROL Control[1];
} SDI_PHY_CONTROL_BUFFER, *PSDI_PHY_CONTROL_BUFFER;

#pragma SDI_END_PACK

#endif // _SDI_H_
