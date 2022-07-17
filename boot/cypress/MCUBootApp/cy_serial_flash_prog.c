/***************************************************************************//**
* \file cy_serial_flash_prog.c
*
* \brief
* Provides variables necessary to inform programming tools how to program the
* attached serial flash memory. The variables used here must be placed at
* specific locations in order to be detected and used by programming tools
* to know that there is an attached memory and its characteristics. Uses the
* configuration provided as part of BSP.
*
********************************************************************************
* \copyright
* Copyright 2018-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_serial_flash Serial Flash
* \{
* Variables for informing programming tools that there is an attached memory device and what
* its characteristics are so it can be programmed just like the on-chip memory.
*
* \defgroup group_serial_flash_variables Variables
*/

#include <stdint.h>
#include "flash_qspi.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct
{
    const cy_stc_smif_block_config_t * smifCfg; /* Pointer to SMIF top-level configuration */
    const uint32_t null_t; /* NULL termination */
} stc_smif_ipblocks_arr_t;

/**
* \addtogroup group_serial_flash_variables
* \{
*/

/**
 * This data can be placed anywhere in the internal memory, but it must be at a location that
 * can be determined and used for the calculation of the CRC16 checksum in the cyToc below. There
 * are multiple ways this can be accomplished including:
 * 1) Placing it in a dedicated memory block with a known address. (as done here)
 * 2) Placing it at an absolute location via a the linker script
 * 3) Using 'cymcuelftool -S' to recompute the checksum and patch the elf file after linking
 */
/* const stc_smif_ipblocks_arr_t smifIpBlocksArr = {&smifBlockConfig_sfdp, 0x00000000}; */
/* if used zero-pointer to config, DAP link will use hardcoded config for CY8CPROTO-062-4343W */
const stc_smif_ipblocks_arr_t smifIpBlocksArr = {0x00000000, 0x00000000};

/**
 * This data is used to populate the table of contents part 2. When present, it is used by the boot
 * process and programming tools to determine key characteristics about the memory usage including
 * where the boot process should start the application from and what external memories are connected
 * (if any). This must consume a full row of flash memory row. The last entry is a checksum of the
 * other values in the ToC which must be updated if any other value changes. This can be done manually
 * or by running 'cymcuelftool -S' to recompute the checksum.
 */

/** \} group_serial_flash_variables */

#if defined(__cplusplus)
}
#endif

/** \} group_serial_flash */
