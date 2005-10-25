/*
 * libsdi.h
 *
 * Header Definitions for libsysfs
 *
 * Copyright (C) 2005 Hewlett-Packard Corp.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */
#ifndef _LIBSDI_H_
#define _LIBSDI_H_

#if 0
#include <sdi.h>
#endif

/* Temporary until sdi.h is cleaned up. */
typedef int SDI_DRIVER_INFO_BUFFER;
typedef int SDI_CNTLR_INFO_BUFFER;
typedef int SDI_CNTLR_STATUS_BUFFER;
typedef int SDI_FIRMWARE_DOWNLOAD_BUFFER;
typedef int SDI_RAID_INFO_BUFFER;
typedef int SDI_RAID_CONFIG_BUFFER;
typedef int SDI_PHY_INFO_BUFFER;
typedef int SDI_SET_PHY_INFO_BUFFER;
typedef int SDI_LINK_ERRORS_BUFFER;
typedef int SDI_SMP_PASSTHROUGH_BUFFER;
typedef int SDI_SSP_PASSTHROUGH_BUFFER;
typedef int SDI_STP_PASSTHROUGH_BUFFER;
typedef int SDI_SATA_SIGNATURE_BUFFER;
typedef int SDI_GET_SCSI_ADDRESS_BUFFER;
typedef int SDI_GET_DEVICE_ADDRESS_BUFFER;
typedef int SDI_SSP_TASK_IU_BUFFER;
typedef int SDI_PHY_CONTROL_BUFFER;
typedef int SDI_GET_CONNECTOR_INFO_BUFFER;

typedef unsigned int sdi_driver_handle_t;
typedef unsigned int sdi_cntlr_handle_t;


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Prototypes
 */
extern int sdi_load_library();
extern int sdi_free_library();
extern int sdi_set_debug_level(int level);

extern int sdi_get_driver_handles(sdi_driver_handle_t **handles); 
extern int sdi_release_driver_handles(sdi_driver_handle_t *handles); 
extern int sdi_get_cntrl_handles(const sdi_driver_handle_t driver_handle, 
                                 sdi_cntlr_handle_t **cntlr_handles); 
extern int sdi_release_cntlr_handles(sdi_cntlr_handle_t *handles); 

extern int sdi_get_driver_info(const sdi_driver_handle_t *handle, 
                               SDI_DRIVER_INFO_BUFFER *buffer);

extern int sdi_get_cntlr_info(const sdi_cntlr_handle_t *handle, 
                              SDI_CNTLR_INFO_BUFFER *buffer);

extern int sdi_get_cntlr_status(const sdi_cntlr_handle_t *handle, 
                                SDI_CNTLR_STATUS_BUFFER *buffer);

extern int sdi_firmware_download(const sdi_cntlr_handle_t *handle, 
                                 SDI_FIRMWARE_DOWNLOAD_BUFFER *buffer);

extern int sdi_get_raid_info(const sdi_cntlr_handle_t *handle,
                             SDI_RAID_INFO_BUFFER *buffer);

extern int sdi_get_raid_config(const sdi_cntlr_handle_t *handle,
                               SDI_RAID_CONFIG_BUFFER *buffer);

extern int sdi_get_phy_info(const sdi_cntlr_handle_t *handle,
                            SDI_PHY_INFO_BUFFER *buffer);

extern int sdi_set_phy_info(const sdi_cntlr_handle_t *handle,
                            SDI_SET_PHY_INFO_BUFFER *buffer);

extern int sdi_get_link_errors(const sdi_cntlr_handle_t *handle,
                               SDI_LINK_ERRORS_BUFFER *buffer);

extern int sdi_smp_passthrough(const sdi_cntlr_handle_t *handle,
                               SDI_SMP_PASSTHROUGH_BUFFER *buffer);

extern int sdi_ssp_passthrough(const sdi_cntlr_handle_t *handle,
                               SDI_SSP_PASSTHROUGH_BUFFER *buffer);

extern int sdi_stp_passthrough(const sdi_cntlr_handle_t *handle,
                               SDI_STP_PASSTHROUGH_BUFFER *buffer);

extern int sdi_get_sata_signature(const sdi_cntlr_handle_t *handle,
                                  SDI_SATA_SIGNATURE_BUFFER *buffer);

extern int sdi_get_scsi_address(const sdi_cntlr_handle_t *handle,
                                SDI_GET_SCSI_ADDRESS_BUFFER *buffer);

extern int sdi_get_device_address(const sdi_cntlr_handle_t *handle,
                                  SDI_GET_DEVICE_ADDRESS_BUFFER *buffer);

extern int sdi_task_management(const sdi_cntlr_handle_t *handle,
                               SDI_SSP_TASK_IU_BUFFER *buffer);

extern int sdi_phy_control(const sdi_cntlr_handle_t *handle,
                           SDI_PHY_CONTROL_BUFFER *buffer);

extern int sdi_get_connector_info(const sdi_cntlr_handle_t *handle,
                                  SDI_GET_CONNECTOR_INFO_BUFFER *buffer);

#ifdef __cplusplus
}
#endif

#endif /* _LIBSDI_H_ */
