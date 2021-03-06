/*

 File generated by ../../tools/common_config.py from common_config.input

 Copyright (c) 2010 Fizians SAS. <http://www.fizians.com>
 This file is part of Rozofs.

 Rozofs is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published
 by the Free Software Foundation, version 2.

 Rozofs is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see
 <http://www.gnu.org/licenses/>.
 */
#ifndef _COMMON_CONFIG_H
#define _COMMON_CONFIG_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <libconfig.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include <dirent.h>
void common_config_read(char * fname);


/*_______________________________
** ENUM definion
*/

// device_selfhealing_mode 
typedef enum _common_config_device_selfhealing_mode_e {
  common_config_device_selfhealing_mode_spareOnly,
  common_config_device_selfhealing_mode_resecure,
  common_config_device_selfhealing_mode_relocate,
} common_config_device_selfhealing_mode_e;
// enum to string
static inline char * common_config_device_selfhealing_mode2String(common_config_device_selfhealing_mode_e x) {
  switch(x) {
    case common_config_device_selfhealing_mode_spareOnly: return "spareOnly";
    case common_config_device_selfhealing_mode_resecure: return "resecure";
    case common_config_device_selfhealing_mode_relocate: return "relocate";
    default: return "?";
  }
  return "?";
}
// string to enum
static inline common_config_device_selfhealing_mode_e string2common_config_device_selfhealing_mode(const char * x) {
  if (strcmp(x,"spareOnly")==0) return common_config_device_selfhealing_mode_spareOnly;
  if (strcmp(x,"resecure")==0) return common_config_device_selfhealing_mode_resecure;
  if (strcmp(x,"relocate")==0) return common_config_device_selfhealing_mode_relocate;
  return -1;
}

/*_______________________________
** common_config structure
*/
typedef struct _common_config_t {

  /*
  ** global scope configuration parameters
  */

  // Number of core files that the system is allowed to keep for all the modules of this server.
  // Older core files are kept while newest are removed.	
  int32_t     nb_core_file;
  // Directory where the core files are stored.
  char *      core_file_directory;
  // Enables to take into account the NUMA architecture of the board in 
  // order to collocate some RozoFS modules on the same node for memory
  // access efficiency.
  int32_t     numa_aware;
  // Number of slices in the STORIO.
  int32_t     storio_slice_number;
  // File distribution mode upon cluster, storages and devices. Check rozofs.conf manual.
  // 0         = Cluster size balancing                   + device size balancing
  // 1,2,3     = Cluster strict round robin               + device write spreading
  // 4         = Cluster strict round robin               + device read spreading
  // 5         = Cluster weighted round robin (nb SID)    + device write spreading
  // 6         = Cluster weighted round robin (nb SID)    + device read spreading
  // 7         = Cluster weighted round robin (free size) + device write spreading
  // 6         = Cluster weighted round robin (free size) + device read spreading
  int32_t     file_distribution_rule;
  // DSCP for exchanges from/to the STORIO.
  int32_t     storio_dscp;
  // DSCP for exchanges from/to the EXPORTD.
  int32_t     export_dscp;

  /*
  ** export scope configuration parameters
  */

  // Max number of file that the exportd can remove from storages in a run.
  // A new run occurs every 2 seconds.
  int32_t     trashed_file_per_run;
  // High trash water mark when FID recycling is activated.
  // When the trash has already this number of files, files are no more
  // deleted but recycled.
  int32_t     trash_high_threshold;
  // Whether FID recycling feature is activated.
  int32_t     fid_recycle;
  int32_t     export_buf_cnt;
  // To activate export writebehind attributes thread.
  int32_t     export_attr_thread;
  // Support of deleted directory/file versioning.
  int32_t     export_versioning;
  // Number of MB to account a file for during file distribution phase
  int32_t     alloc_estimated_mb;
  // Delay from which a rozofsmoun client is declared disconnected and its 
  // file locks are automatically removed
  int32_t     client_flock_timeout;
  // Time out between export and storage for remove and stat
  int32_t     mproto_timeout;
  // Directory to use on the export to build temporary files.
  // Used for instance to build list of files to rebuild.
  char *      export_temporary_dir;
  // To activate workaround that make mkdir respond OK instead of EEXIST
  // when the directory is already created 
  int32_t     mkdir_ok_instead_of_eexist;
  // To activate workaround that make mknod respond OK instead of EEXIST
  // when the file is already created  
  int32_t     mknod_ok_instead_of_eexist;
  // To disable synchronous write of attributes when set to True
  int32_t     disable_sync_attributes;
  // Minimum delay between the deletion request and the effective projections deletion
  int32_t     deletion_delay;
  // Minimum number of inodes that must be available on metadata device to allow a mknod/mkdir operation
  int32_t     min_metadata_inodes;
  // Minimum available size in MB that must be available on metadata device to allow a mknod/mkdir operation
  int32_t     min_metadata_MB;
  // Number of trash threads that work in parallel
  int32_t     nb_trash_thread;
  // Number of thin provisioning threads that work in parallel
  int32_t     nb_thin_thread;
  // Max number of files that the exportd can submit to storages to get the number of blocks (thin provisioning) in a run.
  // A new run occurs every 2 seconds.
  int32_t     thin_scan_file_per_run;
  // Thin provisioning Level 1 hash table size in power of 2 (changing this parameter will take effect on the next export restart) 
  int32_t     thin_lv1_hash_tb_size;
  // Guard delay in seconds between two file scanning of a file that belongs to an exportd configured for thin provisioning
  int32_t     expthin_guard_delay_sec;
  // Guard delay associated with directory re-write used for tracking children changes within a directory 
  int32_t     expdir_guard_delay_sec;
  // Maximum number of entries that the export level 2 cache can contain (unit is KB) 
  int32_t     level2_cache_max_entries_kb;
  // Whether file locks must be persistent on exportd restart/switchover or not
  int32_t     persistent_file_locks;
  // Minimum % of free space in a volume.
  // When the free space of a volume reaches this value, file creation requests
  // receive back ENOSPC in order to try to avoid later write errors.
  // A value of 0 means there is no limit on the volume.
  // A value of 100 forbids every file creation.
  int32_t     minimum_free_size_percent;

  /*
  ** client scope configuration parameters
  */

  // Whether STORCLI acknowleges write request on inverse or forward STORIO responses.
  int32_t     wr_ack_on_inverse;
  // To activate rozofsmount reply fuse threads.
  int32_t     rozofsmount_fuse_reply_thread;
  // To activate fast reconnect from client to exportd
  int32_t     client_fast_reconnect;
  // delay is minutes after which a file is considered as an archived file (unit is minute)
  int32_t     archive_file_delay;
  // dentry cache timeout for archive file type (unit is second)
  int32_t     archive_file_dentry_timeout;
  // attribute cache timeout for archive file type (unit is second)
  int32_t     archive_file_attr_timeout;
  // When that flag is asserted, the rozofsmount client can cache the extended attributes
  int32_t     client_xattr_cache;
  // When that flag is asserted, the rozofsmount client performs setattr in asynchronous mode
  int32_t     async_setattr;
  // statfs period in seconds. minimum is 0.
  int32_t     statfs_period;

  /*
  ** storage scope configuration parameters
  */

  // Number of sub threads in the storaged
  int32_t     nb_storaged_subthread;
  /// Number of disk threads in the STORIO.
  int32_t     nb_disk_thread;
  // Whether CRC32 MUST be checked by STORIO.
  int32_t     crc32c_check;
  // Whether CRC32 MUST be computed by STORIO.
  int32_t     crc32c_generate;
  // Whether CRC32 MUST be absolutly hardware computed by STORIO.
  int32_t     crc32c_hw_forced;
  // Whether STORIO device monitoring should avoid reading from 
  // devices when no access have occured for read or write. This
  // enables disk spin down to occur.
  int32_t     allow_disk_spin_down;
  // Over which device usage threashold should the STORIO log the event. 
  int32_t     disk_usage_threshold;
  // Over which device read delay threashold should the STORIO log the event. 
  int32_t     disk_read_threshold;
  // Over which device write delay threashold should the STORIO log the event. 
  int32_t     disk_write_threshold;
  // Number of STORIO receive buffer.
  int32_t     storio_buf_cnt;
  // Number of block to which the chunk files should be truncated on storage 
  // node at the time it is recycled.
  int32_t     recycle_truncate_blocks;
  // Name of an executable file that the storaged should call at startup
  char *      storaged_start_script;
  // Whether the storage has to automount the devices
  int32_t     device_automount;
  // automount path where the devices should be mounted
  char *      device_automount_path;
  // Device mounting options
  char *      device_automount_option;
  // Directory to use on the storage node to build temporary files.
  // Used for instance by the rebuild process.
  char *      storage_temporary_dir;
  // self healing : Paralellism factor for device self healing feature
  // i.e the number of process to run rebuild in //
  int32_t     device_self_healing_process;
  // self healing : Fault duration in minutes before device selfhealing starts
  int32_t     device_selfhealing_delay;
  // self healing :  throughput limitation in MB/s per rebuild process in //
  // for reading external projections. The writing on disk is only
  // 1/2 of that in layout 0, 1/4 in layout 1...
  // 0 means no limit
  int32_t     device_selfhealing_read_throughput;
  // self healing : possible modes
  // spareOnly  only self repair on a spare disk
  // relocate   also repair on remaining disks when no spare available
  // resecure   repair on spare device when available, and then resecure files on
  //            spare storages when no spare device is available
  common_config_device_selfhealing_mode_e  device_selfhealing_mode;
  // Export host names or IP addresses separated with / 
  // Required for selfhealing.
  // Required for spare file restoring to its nominal location.
  char *      export_hosts;
  // Spare file restoring : whether the service is active or not
  int32_t     spare_restore_enable;
  // Spare file restoring : how often the process runs  
  int32_t     spare_restore_loop_delay;
  // Default rebuild reloop value 
  // Mainly used to help simulation
  int32_t     default_rebuild_reloop;
  // Spare file restoring : throughput limitation for reading and analyzing spare files in MB/s
  // 0 means no limit
  int32_t     spare_restore_read_throughput;
  // Storio number of FID context in 1K unit
  int32_t     storio_fidctx_ctx;
  // Spare file restoring : Number of spare file context in 1K unit
  int32_t     spare_restore_spare_ctx;
  // Whether RozoFS devices must mandatorily be identified by a valid label.
  // Storages will not mount any device not having a valid RozoFS label.
  int32_t     mandatory_device_label;
} common_config_t;

extern common_config_t common_config;

/*_______________________________
** ENUM macro
*/
// Read enum from configuration file
static inline void COMMON_CONFIG_DEVICE_SELFHEALING_MODE_READ_ENUM(config_t * cfg) {
  const char * charval;
  common_config.device_selfhealing_mode = -1;
  if (config_lookup_string(cfg, "device_selfhealing_mode", &charval) == CONFIG_TRUE) {
    common_config.device_selfhealing_mode = string2common_config_device_selfhealing_mode(charval);
  }
  if (common_config.device_selfhealing_mode == -1) {
    common_config.device_selfhealing_mode =  string2common_config_device_selfhealing_mode("spareOnly");
  }
}
// Set enum value thanks to rozodiag
#define COMMON_CONFIG_DEVICE_SELFHEALING_MODE_SET_ENUM(VAL)  {\
  int myval = string2common_config_device_selfhealing_mode(VAL);\
  if (myval == -1) {\
    pChar += rozofs_string_append_error(pChar," Unexpected enum value for device_selfhealing_mode : ");\
    pChar += rozofs_string_append_error(pChar,VAL);\
  }\
  else {\
    common_config.device_selfhealing_mode = myval;\
    pChar += rozofs_string_append(pChar,"device_selfhealing_mode");\
    pChar += rozofs_string_append(pChar," set to value ");\
    pChar += rozofs_string_append(pChar,VAL);\
  }\
  pChar += rozofs_eol(pChar);\
  return 0;\
}

#endif
