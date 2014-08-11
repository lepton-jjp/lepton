/*
The contents of this file are subject to the Mozilla Public License Version 1.1
(the "License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for the
specific language governing rights and limitations under the License.

The Original Code is Lepton.

The Initial Developer of the Original Code is Chauvin-Arnoux.
Portions created by Chauvin-Arnoux are Copyright (C) 2011. All Rights Reserved.

Alternatively, the contents of this file may be used under the terms of the eCos GPL license
(the  [eCos GPL] License), in which case the provisions of [eCos GPL] License are applicable
instead of those above. If you wish to allow use of your version of this file only under the
terms of the [eCos GPL] License and not to allow others to use your version of this file under
the MPL, indicate your decision by deleting  the provisions above and replace
them with the notice and other provisions required by the [eCos GPL] License.
If you do not delete the provisions above, a recipient may use your version of this file under
either the MPL or the [eCos GPL] License."
*/

//------------------------------------------------------------------------------
/// \unit
/// !Purpose
///
/// SCSI definitions.
///
/// !Usage
///
/// -# After command block received, Access and decode the SCSI command block
///    with SBCCommand structure.
//------------------------------------------------------------------------------

#ifndef SBC_H
#define SBC_H

//------------------------------------------------------------------------------
//      Definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SBC Operation Codes"
/// This page lists operation codes of commands described in the SBC-3
/// standard.
///
/// \note That most commands are actually defined in other standards,
///       like SPC-4. Optional commands are not included here.
///
/// \see    sbc3r07.pdf - Section 5.1 - Table 12
/// \see    spc4r06.pdf
/// \see    SBCCommand
///
/// !Codes
/// - SBC_INQUIRY
/// - SBC_READ_10
/// - SBC_READ_CAPACITY_10
/// - SBC_REQUEST_SENSE
/// - SBC_TEST_UNIT_READY
/// - SBC_WRITE_10
///
/// !Optional Codes but required by Windows
/// - SBC_PREVENT_ALLOW_MEDIUM_REMOVAL
/// - SBC_MODE_SENSE_6
/// - SBC_VERIFY_10

/// Request information regarding parameters of the target and Logical Unit.
#define SBC_INQUIRY                                     0x12
/// Request the transfer data to the host.
#define SBC_READ_10                                     0x28
/// Request capacities of the currently installed medium.
#define SBC_READ_CAPACITY_10                            0x25
/// Request that the device server transfer sense data.
#define SBC_REQUEST_SENSE                               0x03
/// Check if the LUN is ready
#define SBC_TEST_UNIT_READY                             0x00
/// Request that the device write the data transferred by the host.
#define SBC_WRITE_10                                    0x2A

/// Request that the target enable or disable the removal of the medium in
/// the Logical Unit.
#define SBC_PREVENT_ALLOW_MEDIUM_REMOVAL                0x1E
/// Report parameters.
#define SBC_MODE_SENSE_6                                0x1A
/// Request that the %device verify the data on the medium.
#define SBC_VERIFY_10                                   0x2F
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SBC Periph. Qualifiers"
/// This page lists the peripheral qualifier values specified in the INQUIRY
/// data
/// \see    spc4r06.pdf - Section 6.4.2 - Table 83
/// \see    SBCInquiryData
///
/// !Qualifiers
/// - SBC_PERIPHERAL_DEVICE_CONNECTED
/// - SBC_PERIPHERAL_DEVICE_NOT_CONNECTED
/// - SBC_PERIPHERAL_DEVICE_NOT_SUPPORTED

#define SBC_PERIPHERAL_DEVICE_CONNECTED                 0x00
#define SBC_PERIPHERAL_DEVICE_NOT_CONNECTED             0x01
#define SBC_PERIPHERAL_DEVICE_NOT_SUPPORTED             0x03
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SBC Periph. Types"
/// This page lists peripheral device types specified in the INQUIRY data
/// \see    spc4r06.pdf - Section 6.4.2 - Table 84
/// \see    SBCInquiryData
///
/// !Types
/// - SBC_DIRECT_ACCESS_BLOCK_DEVICE
/// - SBC_SEQUENTIAL_ACCESS_DEVICE
/// - SBC_PRINTER_DEVICE
/// - SBC_PROCESSOR_DEVICE
/// - SBC_WRITE_ONCE_DEVICE
/// - SBC_CD_DVD_DEVICE
/// - SBC_SCANNER_DEVICE
/// - SBC_OPTICAL_MEMORY_DEVICE
/// - SBC_MEDIA_CHANGER_DEVICE
/// - SBC_COMMUNICATION_DEVICE
/// - SBC_STORAGE_ARRAY_CONTROLLER_DEVICE
/// - SBC_ENCLOSURE_SERVICES_DEVICE
/// - SBC_SIMPLIFIED_DIRECT_ACCESS_DEVICE
/// - SBC_OPTICAL_CARD_READER_WRITER_DEVICE
/// - SBC_BRIDGE_CONTROLLER_COMMANDS
/// - SBC_OBJECT_BASED_STORAGE_DEVICE

#define SBC_DIRECT_ACCESS_BLOCK_DEVICE              0x00
#define SBC_SEQUENTIAL_ACCESS_DEVICE                0x01
#define SBC_PRINTER_DEVICE                          0x02
#define SBC_PROCESSOR_DEVICE                        0x03
#define SBC_WRITE_ONCE_DEVICE                       0x04
#define SBC_CD_DVD_DEVICE                           0x05
#define SBC_SCANNER_DEVICE                          0x06
#define SBC_OPTICAL_MEMORY_DEVICE                   0x07
#define SBC_MEDIA_CHANGER_DEVICE                    0x08
#define SBC_COMMUNICATION_DEVICE                    0x09
#define SBC_STORAGE_ARRAY_CONTROLLER_DEVICE         0x0C
#define SBC_ENCLOSURE_SERVICES_DEVICE               0x0D
#define SBC_SIMPLIFIED_DIRECT_ACCESS_DEVICE         0x0E
#define SBC_OPTICAL_CARD_READER_WRITER_DEVICE       0x0F
#define SBC_BRIDGE_CONTROLLER_COMMANDS              0x10
#define SBC_OBJECT_BASED_STORAGE_DEVICE             0x11
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \brief  Version value for the SBC-3 specification
/// \see    spc4r06.pdf - Section 6.4.2 - Table 85
#define SBC_SPC_VERSION_4                           0x06
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \brief  Values for the TPGS field returned in INQUIRY data
/// \see    spc4r06.pdf - Section 6.4.2 - Table 86
#define SBC_TPGS_NONE                               0x0
#define SBC_TPGS_ASYMMETRIC                         0x1
#define SBC_TPGS_SYMMETRIC                          0x2
#define SBC_TPGS_BOTH                               0x3
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \brief  Version descriptor value for the SBC-3 specification
/// \see    spc4r06.pdf - Section 6.4.2 - Table 87
#define SBC_VERSION_DESCRIPTOR_SBC_3                0x04C0
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SBC Sense Response Codes"
/// This page lists sense data response codes returned in REQUEST SENSE data
/// \see    spc4r06.pdf - Section 4.5.1 - Table 12
///
/// !Codes
/// - SBC_SENSE_DATA_FIXED_CURRENT
/// - SBC_SENSE_DATA_FIXED_DEFERRED
/// - SBC_SENSE_DATA_DESCRIPTOR_CURRENT
/// - SBC_SENSE_DATA_DESCRIPTOR_DEFERRED

#define SBC_SENSE_DATA_FIXED_CURRENT                0x70
#define SBC_SENSE_DATA_FIXED_DEFERRED               0x71
#define SBC_SENSE_DATA_DESCRIPTOR_CURRENT           0x72
#define SBC_SENSE_DATA_DESCRIPTOR_DEFERRED          0x73
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SBC Sense Keys"
/// This page lists sense key values returned in the REQUEST SENSE data
/// \see    spc4r06.pdf - Section 4.5.6 - Table 27
///
/// !Keys
/// - SBC_SENSE_KEY_NO_SENSE
/// - SBC_SENSE_KEY_RECOVERED_ERROR
/// - SBC_SENSE_KEY_NOT_READY
/// - SBC_SENSE_KEY_MEDIUM_ERROR
/// - SBC_SENSE_KEY_HARDWARE_ERROR
/// - SBC_SENSE_KEY_ILLEGAL_REQUEST
/// - SBC_SENSE_KEY_UNIT_ATTENTION
/// - SBC_SENSE_KEY_DATA_PROTECT
/// - SBC_SENSE_KEY_BLANK_CHECK
/// - SBC_SENSE_KEY_VENDOR_SPECIFIC
/// - SBC_SENSE_KEY_COPY_ABORTED
/// - SBC_SENSE_KEY_ABORTED_COMMAND
/// - SBC_SENSE_KEY_VOLUME_OVERFLOW
/// - SBC_SENSE_KEY_MISCOMPARE

/// No specific sense key. Successful command.
#define SBC_SENSE_KEY_NO_SENSE                        0x00
/// Command completed succesfully with some recovery action by the %device.
#define SBC_SENSE_KEY_RECOVERED_ERROR                 0x01
/// The device can not be accessed.
#define SBC_SENSE_KEY_NOT_READY                       0x02
/// Command terminated with a error condition that was probably caused by a
/// flaw in the medium or an error in the recorded data.
#define SBC_SENSE_KEY_MEDIUM_ERROR                    0x03
/// Hardware failure while performing the command or during a self test.
#define SBC_SENSE_KEY_HARDWARE_ERROR                  0x04
/// Illegal parameter found in the command or additional parameters.
#define SBC_SENSE_KEY_ILLEGAL_REQUEST                 0x05
/// Removable medium may have been changed or the %device has been reset.
#define SBC_SENSE_KEY_UNIT_ATTENTION                  0x06
/// Write on a block that is protected.
#define SBC_SENSE_KEY_DATA_PROTECT                    0x07
/// Indicates that a write-once device or a sequential-access device
/// encountered blank medium or format-defined end-of-data indication while
/// reading or a write-once device encountered a non-blank medium while writing.
#define SBC_SENSE_KEY_BLANK_CHECK                     0x08
/// Reporting vendor specific conditions.
#define SBC_SENSE_KEY_VENDOR_SPECIFIC                 0x09
/// EXTENDED COPY command was aborted.
#define SBC_SENSE_KEY_COPY_ABORTED                    0x0A
/// Device aborted the command.
#define SBC_SENSE_KEY_ABORTED_COMMAND                 0x0B
/// A buffered peripheral device is overflow.
#define SBC_SENSE_KEY_VOLUME_OVERFLOW                 0x0D
/// The source data did not match the data read from the medium.
#define SBC_SENSE_KEY_MISCOMPARE                      0x0E
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SBC Sense Additionals"
/// This page lists additional sense code values returned in REQUEST SENSE data
/// \see    spc4r06.pdf - Section 4.5.6 - Table 28
///
/// !Additional Codes
/// - SBC_ASC_LOGICAL_UNIT_NOT_READY
/// - SBC_ASC_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE
/// - SBC_ASC_INVALID_FIELD_IN_CDB
/// - SBC_ASC_WRITE_PROTECTED
/// - SBC_ASC_FORMAT_CORRUPTED
/// - SBC_ASC_INVALID_COMMAND_OPERATION_CODE
/// - SBC_ASC_TOO_MUCH_WRITE_DATA
/// - SBC_ASC_NOT_READY_TO_READY_CHANGE
/// - SBC_ASC_MEDIUM_NOT_PRESENT

#define SBC_ASC_LOGICAL_UNIT_NOT_READY                0x04
#define SBC_ASC_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE    0x21
#define SBC_ASC_INVALID_FIELD_IN_CDB                  0x24
#define SBC_ASC_WRITE_PROTECTED                       0x27
#define SBC_ASC_FORMAT_CORRUPTED                      0x31
#define SBC_ASC_INVALID_COMMAND_OPERATION_CODE        0x20
#define SBC_ASC_TOO_MUCH_WRITE_DATA                   0x26
#define SBC_ASC_NOT_READY_TO_READY_CHANGE             0x28
#define SBC_ASC_MEDIUM_NOT_PRESENT                    0x3A
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \brief  MEDIUM TYPE field value for direct-access block devices
/// \see    sbc3r06.pdf - Section 6.3.1
#define SBC_MEDIUM_TYPE_DIRECT_ACCESS_BLOCK_DEVICE    0x00
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \brief  MRIE field values
/// \see    sbc3r06.pdf - Section 7.4.11 - Table 286
#define SBC_MRIE_NO_REPORTING                         0x00
#define SBC_MRIE_ASYNCHRONOUS                         0x01
#define SBC_MRIE_GENERATE_UNIT_ATTENTION              0x02
#define SBC_MRIE_COND_GENERATE_RECOVERED_ERROR        0x03
#define SBC_MRIE_UNCOND_GENERATE_RECOVERED_ERROR      0x04
#define SBC_MRIE_GENERATE_NO_SENSE                    0x05
#define SBC_MRIE_ON_REQUEST                           0x06
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \brief  Supported mode pages
/// \see    sbc3r06.pdf - Section 6.3.1 - Table 115
#define SBC_PAGE_READ_WRITE_ERROR_RECOVERY            0x01
#define SBC_PAGE_INFORMATIONAL_EXCEPTIONS_CONTROL     0x1C
#define SBC_PAGE_RETURN_ALL                           0x3F
#define SBC_PAGE_VENDOR_SPECIFIC                      0x00
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "SBC Command States"
/// This page lists the possible states of a SBC command.
///
/// !States
/// - SBC_STATE_READ
/// - SBC_STATE_WAIT_READ
/// - SBC_STATE_WRITE
/// - SBC_STATE_WAIT_WRITE
/// - SBC_STATE_NEXT_BLOCK

/// Start of reading bulk data
#define SBC_STATE_READ                          0x01
/// Waiting for the bulk data reading complete
#define SBC_STATE_WAIT_READ                     0x02
/// Start writing bulk data to host
#define SBC_STATE_WRITE                         0x03
/// Waiting for the bulk data sending complete
#define SBC_STATE_WAIT_WRITE                    0x04
/// Start next command block
#define SBC_STATE_NEXT_BLOCK                    0x05
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// \page "MSD Endian Macros"
/// This page lists the macros for endianness conversion.
///
/// !Macros
/// - WORDB
/// - DWORDB
/// - STORE_DWORDB
/// - STORE_WORDB
/// \brief  Converts a byte array to a word value using the big endian format
#define WORDB(bytes)            ((unsigned short) ((bytes[0] << 8) | bytes[1]))

/// \brief  Converts a byte array to a dword value using the big endian format
#define DWORDB(bytes)   ((unsigned int) ((bytes[0] << 24) | (bytes[1] << 16) \
                                         | (bytes[2] << 8) | bytes[3]))

/// \brief  Stores a dword value in a byte array, in big endian format
#define STORE_DWORDB(dword, bytes) \
   bytes[0] = (unsigned char) (((dword) >> 24) & 0xFF); \
   bytes[1] = (unsigned char) (((dword) >> 16) & 0xFF); \
   bytes[2] = (unsigned char) (((dword) >> 8) & 0xFF); \
   bytes[3] = (unsigned char) ((dword) & 0xFF);

/// \brief  Stores a word value in a byte array, in big endian format
#define STORE_WORDB(word, bytes) \
   bytes[0] = (unsigned char) (((word) >> 8) & 0xFF); \
   bytes[1] = (unsigned char) ((word) & 0xFF);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//      Structures
//------------------------------------------------------------------------------

#ifdef __ICCARM__          // IAR
   #pragma pack(1) // IAR
   #define __attribute__(...) // IAR
#endif                     // IAR

//------------------------------------------------------------------------------
/// \brief  Structure for the INQUIRY command
/// \see    spc4r06.pdf - Section 6.4.1 - Table 81
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bOperationCode;        //!< 0x12 : SBC_INQUIRY
   unsigned char isEVPD : 1,            //!< Type of requested data
                 bReserved1 : 7;        //!< Reserved bits
   unsigned char bPageCode;             //!< Specifies the VPD to return
   unsigned char pAllocationLength[2];  //!< Size of host buffer
   unsigned char bControl;              //!< 0x00

} __attribute__ ((packed)) SBCInquiry; // GCC

//------------------------------------------------------------------------------
/// \brief  Standard INQUIRY data format returned by the device
/// \see    spc4r06.pdf - Section 6.4.2 - Table 82
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bPeripheralDeviceType : 5, //!< Peripheral device type
                 bPeripheralQualifier : 3;  //!< Peripheral qualifier
   unsigned char bReserved1 : 7,            //!< Reserved bits
                 isRMB     : 1;             //!< Is media removable ?
   unsigned char bVersion;                  //!< SPC version used
   unsigned char bResponseDataFormat : 4,   //!< Must be 0x2
                 isHIGHSUP          : 1,    //!< Hierarchical addressing used ?
                 isNORMACA          : 1,    //!< ACA attribute supported ?
                 bObsolete1         : 2;    //!< Obsolete bits
   unsigned char bAdditionalLength;         //!< Length of remaining INQUIRY data
   unsigned char isSCCS    : 1,             //!< Embedded SCC ?
                 isACC     : 1,             //!< Access control coordinator ?
                 bTPGS     : 2,             //!< Target port support group
                 is3PC     : 1,             //!< Third-party copy supported ?
                 bReserved2 : 2,            //!< Reserved bits
                 isProtect : 1;             //!< Protection info supported ?
   unsigned char bObsolete2 : 1,            //!< Obsolete bit
                 isEncServ : 1,             //!< Embedded enclosure service comp?
                 isVS      : 1,             //!< ???
                 isMultiP  : 1,             //!< Multi-port device ?
                 bObsolete3 : 3,            //!< Obsolete bits
                 bUnused1  : 1;             //!< Unused feature
   unsigned char bUnused2 : 6,              //!< Unused features
                 isCmdQue : 1,              //!< Task management model supported ?
                 isVS2   : 1;               //!< ???
   unsigned char pVendorID[8];              //!< T10 vendor identification
   unsigned char pProductID[16];            //!< Vendor-defined product ID
   unsigned char pProductRevisionLevel[4];  //!< Vendor-defined product revision
   unsigned char pVendorSpecific[20];       //!< Vendor-specific data
   unsigned char bUnused3;                  //!< Unused features
   unsigned char bReserved3;                //!< Reserved bits
   unsigned short pVersionDescriptors[8];   //!< Standards the device complies to
   unsigned char pReserved4[22];            //!< Reserved bytes

} __attribute__ ((packed)) SBCInquiryData; // GCC

//------------------------------------------------------------------------------
/// \brief  Data structure for the READ (10) command
/// \see    sbc3r07.pdf - Section 5.7 - Table 34
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bOperationCode;           //!< 0x28 : SBC_READ_10
   unsigned char bObsolete1 : 1,           //!< Obsolete bit
                 isFUA_NV : 1,             //!< Cache control bit
                 bReserved1 : 1,           //!< Reserved bit
                 isFUA : 1,                //!< Cache control bit
                 isDPO : 1,                //!< Cache control bit
                 bRdProtect : 3;           //!< Protection information to send
   unsigned char pLogicalBlockAddress[4];  //!< Index of first block to read
   unsigned char bGroupNumber : 5,         //!< Information grouping
                 bReserved2 : 3;           //!< Reserved bits
   unsigned char pTransferLength[2];       //!< Number of blocks to transmit
   unsigned char bControl;                 //!< 0x00

} __attribute__ ((packed)) SBCRead10; // GCC

//------------------------------------------------------------------------------
/// \brief  Structure for the READ CAPACITY (10) command
/// \see    sbc3r07.pdf - Section 5.11.1 - Table 40
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bOperationCode;           //!< 0x25 : RBC_READ_CAPACITY
   unsigned char bObsolete1 : 1,           //!< Obsolete bit
                 bReserved1 : 7;           //!< Reserved bits
   unsigned char pLogicalBlockAddress[4];  //!< Block to evaluate if PMI is set
   unsigned char pReserved2[2];            //!< Reserved bytes
   unsigned char isPMI : 1,                //!< Partial medium indicator bit
                 bReserved3 : 7;           //!< Reserved bits
   unsigned char bControl;                 //!< 0x00

} SBCReadCapacity10;

//------------------------------------------------------------------------------
/// \brief  Data returned by the device after a READ CAPACITY (10) command
/// \see    sbc3r07.pdf - Section 5.11.2 - Table 41
//------------------------------------------------------------------------------
typedef struct {

   unsigned char pLogicalBlockAddress[4];  //!< Address of last logical block
   unsigned char pLogicalBlockLength[4];   //!< Length of last logical block

} SBCReadCapacity10Data;

//------------------------------------------------------------------------------
/// \brief  Structure for the REQUEST SENSE command
/// \see    spc4r06.pdf - Section 6.26 - Table 170
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bOperationCode;     //!< 0x03 : SBC_REQUEST_SENSE
   unsigned char isDesc    : 1,      //!< Type of information expected
                 bReserved1 : 7;     //!< Reserved bits
   unsigned char pReserved2[2];      //!< Reserved bytes
   unsigned char bAllocationLength;  //!< Size of host buffer
   unsigned char bControl;           //!< 0x00

} SBCRequestSense;

//------------------------------------------------------------------------------
/// \brief  Fixed format sense data returned after a REQUEST SENSE command has
///         been received with a DESC bit cleared.
/// \see    spc4r06.pdf - Section 4.5.3 - Table 26
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bResponseCode : 7,               //!< Sense data format
                 isValid      : 1;                //!< Information field is standard
   unsigned char bObsolete1;                      //!< Obsolete byte
   unsigned char bSenseKey : 4,                   //!< Generic error information
                 bReserved1 : 1,                  //!< Reserved bit
                 isILI     : 1,                   //!< SSC
                 isEOM     : 1,                   //!< SSC
                 isFilemark : 1;                  //!< SSC
   unsigned char pInformation[4];                 //!< Command-specific
   unsigned char bAdditionalSenseLength;          //!< sizeof(SBCRequestSense_data)-8
   unsigned char pCommandSpecificInformation[4];  //!< Command-specific
   unsigned char bAdditionalSenseCode;            //!< Additional error information
   unsigned char bAdditionalSenseCodeQualifier;   //!< Further error information
   unsigned char bFieldReplaceableUnitCode;       //!< Specific component code
   unsigned char bSenseKeySpecific : 7,           //!< Additional exception info
                 isSKSV           : 1;            //!< Is sense key specific valid?
   unsigned char pSenseKeySpecific[2];            //!< Additional exception info

} SBCRequestSenseData;

//------------------------------------------------------------------------------
/// \brief  Data structure for the TEST UNIT READY command
/// \see    spc4r06.pdf - Section 6.34 - Table 192
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bOperationCode;  //!< 0x00 : SBC_TEST_UNIT_READY
   unsigned char pReserved1[4];   //!< Reserved bits
   unsigned char bControl;        //!< 0x00

} __attribute__ ((packed)) SBCTestUnitReady; // GCC

//------------------------------------------------------------------------------
/// \brief  Structure for the WRITE (10) command
/// \see    sbc3r07.pdf - Section 5.26 - Table 70
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bOperationCode;           //!< 0x2A : SBC_WRITE_10
   unsigned char bObsolete1 : 1,           //!< Obsolete bit
                 isFUA_NV : 1,             //!< Cache control bit
                 bReserved1 : 1,           //!< Reserved bit
                 isFUA : 1,                //!< Cache control bit
                 isDPO : 1,                //!< Cache control bit
                 bWrProtect : 3;           //!< Protection information to send
   unsigned char pLogicalBlockAddress[4];  //!< First block to write
   unsigned char bGroupNumber : 5,         //!< Information grouping
                 bReserved2 : 3;           //!< Reserved bits
   unsigned char pTransferLength[2];       //!< Number of blocks to write
   unsigned char bControl;                 //!< 0x00

} __attribute__ ((packed)) SBCWrite10;

//------------------------------------------------------------------------------
/// \brief  Structure for the PREVENT/ALLOW MEDIUM REMOVAL command
/// \see    sbc3r07.pdf - Section 5.5 - Table 30
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bOperationCode;  //!< 0x1E : SBC_PREVENT_ALLOW_MEDIUM_REMOVAL
   unsigned char pReserved1[3];   //!< Reserved bytes
   unsigned char bPrevent : 2,    //!< Accept/prohibit removal
                 bReserved2 : 6;  //!< Reserved bits
   unsigned char bControl;        //!< 0x00

} __attribute__ ((packed)) SBCMediumRemoval; // GCC

//------------------------------------------------------------------------------
/// \brief  Structure for the MODE SENSE (6) command
/// \see    spc4r06 - Section 6.9.1 - Table 98
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bOperationCode;     //!< 0x1A : SBC_MODE_SENSE_6
   unsigned char bReserved1 : 3,     //!< Reserved bits
                 isDBD : 1,          //!< Disable block descriptors bit
                 bReserved2 : 4;     //!< Reserved bits
   unsigned char bPageCode : 6,      //!< Mode page to return
                 bPC : 2;            //!< Type of parameter values to return
   unsigned char bSubpageCode;       //!< Mode subpage to return
   unsigned char bAllocationLength;  //!< Host buffer allocated size
   unsigned char bControl;           //!< 0x00

} __attribute__ ((packed)) SBCModeSense6; // GCC

//------------------------------------------------------------------------------
/// \brief  Header for the data returned after a MODE SENSE (6) command
/// \see    spc4r06.pdf - Section 7.4.3 - Table 268
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bModeDataLength;           //!< Length of mode data to follow
   unsigned char bMediumType;               //!< Type of medium (SBC_MEDIUM_TYPE_DIRECT_ACCESS_BLOCK_DEVICE)
   unsigned char bReserved1 : 4,            //!< Reserved bits
                 isDPOFUA : 1,              //!< DPO/FUA bits supported ?
                 bReserved2 : 2,            //!< Reserved bits
                 isWP : 1;                  //!< Is medium write-protected ?
   unsigned char bBlockDescriptorLength;    //!< Length of all block descriptors

} __attribute__ ((packed)) SBCModeParameterHeader6; // GCC

//------------------------------------------------------------------------------
/// \brief  Informational exceptions control mode page
/// \see    spc4r06.pdf - Section 7.4.11 - Table 285
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bPageCode : 6,      //!< 0x1C : SBC_PAGE_INFORMATIONAL_EXCEPTIONS_CONTROL
                 isSPF : 1,          //!< Page or subpage data format
                 isPS : 1;           //!< Parameters saveable ?
   unsigned char bPageLength;        //!< Length of page data (0x0A)
   unsigned char isLogErr : 1,       //!< Should informational exceptions be logged ?
                 isEBackErr : 1,     //!< Enable background error bit
                 isTest : 1,         //!< Create a device test failure ?
                 isDExcpt : 1,       //!< Disable exception control bit
                 isEWasc : 1,        //!< Report warnings ?
                 isEBF : 1,          //!< Enable background function bit
                 bReserved1 : 1,     //!< Reserved bit
                 isPerf : 1;         //!< Delay acceptable when treating exceptions ?
   unsigned char bMRIE : 4,          //!< Method of reporting informational exceptions
                 bReserved2 : 4;     //!< Reserved bits
   unsigned char pIntervalTimer[4];  //!< Error reporting period
   unsigned char pReportCount[4];    //!< Maximum number of time a report can be issued

} __attribute__ ((packed)) SBCInformationalExceptionsControl; // GCC

//------------------------------------------------------------------------------
/// \brief  Read/write error recovery mode page
/// \see    sbc3r07.pdf - Section 6.3.5 - Table 122
//------------------------------------------------------------------------------
typedef struct {

   unsigned char bPageCode : 6,          //!< 0x01 : SBC_PAGE_READ_WRITE_ERROR_RECOVERY
                 isSPF : 1,              //!< Page or subpage data format
                 isPS : 1;               //!< Parameters saveable ?
   unsigned char bPageLength;            //!< Length of page data (0x0A)
   unsigned char isDCR : 1,              //!< Disable correction bit
                 isDTE : 1,              //!< Data terminate on error bit
                 isPER : 1,              //!< Post error bit
                 isEER : 1,              //!< Enable early recovery bit
                 isRC : 1,               //!< Read continuous bit
                 isTB : 1,               //!< Transfer block bit
                 isARRE : 1,             //!< Automatic read reallocation enabled bit
                 isAWRE : 1;             //!< Automatic write reallocation enabled bit
   unsigned char bReadRetryCount;        //!< Number of retries when reading
   unsigned char pObsolete1[3];          //!< Obsolete bytes
   unsigned char bReserved1;             //!< Reserved byte
   unsigned char bWriteRetryCount;       //!< Number of retries when writing
   unsigned char bReserved2;             //!< Reserved byte
   unsigned char pRecoveryTimeLimit[2];  //!< Maximum time duration for error recovery

} __attribute__ ((packed)) SBCReadWriteErrorRecovery; // GCC

//------------------------------------------------------------------------------
/// \brief  Generic structure for holding information about SBC commands
/// \see    SBCInquiry
/// \see    SBCRead10
/// \see    SBCReadCapacity10
/// \see    SBCRequestSense
/// \see    SBCTestUnitReady
/// \see    SBCWrite10
/// \see    SBCMediumRemoval
/// \see    SBCModeSense6
//------------------------------------------------------------------------------
typedef union {

   unsigned char bOperationCode;      //!< Operation code of the command
   SBCInquiry inquiry;                //!< INQUIRY command
   SBCRead10 read10;                  //!< READ (10) command
   SBCReadCapacity10 readCapacity10;  //!< READ CAPACITY (10) command
   SBCRequestSense requestSense;      //!< REQUEST SENSE command
   SBCTestUnitReady testUnitReady;    //!< TEST UNIT READY command
   SBCWrite10 write10;                //!< WRITE (10) command
   SBCMediumRemoval mediumRemoval;    //!< PREVENT/ALLOW MEDIUM REMOVAL command
   SBCModeSense6 modeSense6;          //!< MODE SENSE (6) command

} SBCCommand;

#ifdef __ICCARM__          // IAR
   #pragma pack() // IAR
#endif                     // IAR

//
void SBC_UpdateSenseData(SBCRequestSenseData *requestSenseData,
                         unsigned char senseKey,
                         unsigned char additionalSenseCode,
                         unsigned char additionalSenseCodeQualifier);


#endif //#ifndef SBC_H
