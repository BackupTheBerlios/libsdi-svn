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

#include <sdi.h>

typedef sdi_driver_handle_t unsigned int;
typedef sdi_cntrl_handle_t unsigned int;


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function Prototypes
 */
extern int sdi_get_driver_handles(sdi_driver_handle_t **handles); 
extern int sdi_release_driver_handles(sdi_driver_handle_t *handles); 
extern int sdi_get_cntlr_handles(sdi_cntlr_handle_t **handles); 
extern int sdi_release_cntlr_handles(sdi_cntlr_handle_t *handles); 

extern int sdi_get_driver_info(sdi_driver_handle_t *handle, 
                               SDI_DRIVER_INFO_BUFFER *buffer);

extern int sdi_get_cntrl_info(sdi_cntlr_handle_t *handle, 
                               SDI_CNTLR_INFO_BUFFER *buffer);

extern int sdi_get_cntrl_status(sdi_cntlr_handle_t *handle, 
                               SDI_CNTLR_STATUS_BUFFER *buffer);

extern int sdi_firmware_download(sdi_cntlr_handle_t *handle, 
                                 SDI_FIRMWARE_DOWNLOAD_BUFFER *buffer);

extern int sdi_get_raid_info(sdi_cntlr_handle_t *handle,
                             SDI_RAID_INFO_BUFFER *buffer);

extern int sdi_get_raid_config(sdi_cntlr_handle_t *handle,,
                               SDI_RAID_CONFIG_BUFFER *buffer);

extern int sdi_get_phy_info(sdi_cntlr_handle_t *handle,,
                            SDI_PHY_INFO_BUFFER *buffer);

extern int sdi_set_phy_info(sdi_cntlr_handle_t *handle,,
                            SDI_SET PHY_INFO_BUFFER *buffer);

extern int sdi_get_link_errors(sdi_cntlr_handle_t *handle,,
                               SDI_LINK_ERRORS_BUFFER *buffer);

extern int sdi_smp_passthrough(sdi_cntlr_handle_t *handle,,
                               SDI_SMP_PASSTHROUGH_BUFFER *buffer);

extern int sdi_ssp_passthrough(sdi_cntlr_handle_t *handle,,
                               SDI_SSP_PASSTHROUGH_BUFFER *buffer);

extern int sdi_stp_passthrough(sdi_cntlr_handle_t *handle,,
                               SDI_STP_PASSTHROUGH_BUFFER *buffer);

extern int sdi_get_sata_signature(sdi_cntlr_handle_t *handle,,
                                  SDI_SATA_SIGNATURE_BUFFER *buffer);

extern int sdi_get_scsi_address(sdi_cntlr_handle_t *handle,,
                                SDI_GET_SCSI_ADDRESS_BUFFER *buffer);

extern int sdi_get_device_address(sdi_cntlr_handle_t *handle,,
                                  SDI_GET_DEVICE_ADDRESS_BUFFER *buffer);

extern int sdi_task_management(sdi_cntlr_handle_t *handle,,
                               SDI_SSP_TASK_IU_BUFFER *buffer);

extern int sdi_phy_control(sdi_cntlr_handle_t *handle,,
                           SDI_PHY_CONTROL__BUFFER *buffer);

extern int sdi_get_connector_info(sdi_cntlr_handle_t *handle,,
                                  SDI_GET_CONNECTOR_INFO_BUFFER *buffer);

#ifdef __cplusplus
}
#endif

#endif /* _LIBSDI_H_ */
