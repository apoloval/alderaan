/*
 *  File        : kernel/i386/multiboot.h
 *  Description : This file provides declarations for multiboot specification
 *                v0.7 as published by GNU project
 *  Author      : Alvaro Polo <apoloval@gmail.com>
 *
 *  Revisions   :
 *
 *  Copyright (C) 2011 Alvaro Polo Valdenebro
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _I386_MULTIBOOT_H
#define _I386_MULTIBOOT_H

#define MULTIBOOT_HEADER_MAGIC         0x1BADB002
#define BOOTINFO_MAGIC                 0x2BADB002
   
#ifdef __ASSEMBLER__

/* For assembler, let's use macros for multiboot header flags. For the
 * kernel itself, an enum is used instead
 */
#define MBOOT_H_ALIGNMODS     0x00000001
#define MBOOT_H_INCMEM        0x00000002
#define MBOOT_H_INCVID        0x00000004
#define MBOOT_H_IMGPAR        0x00010000

#else

#include <stdint.h>

/* Image address information. This type provides address information for
 * the OS image. It is used for non-ELF image formats which boot manager
 * is unable to interpret.
 */
struct ImageAddrInfo
{
   uint32_t    headerAddr;    // Base address of this header
   uint32_t    loadAddr;      // Base address of image text segment
   uint32_t    loadEndAddr;   // End address of image data segment
   uint32_t    bssEndAddr;    // End address of image BSS segment
   uint32_t    entryAddr;     // Address of image entry point to jump to
};

/* Video information. This type provides the parameters provided by
 * boot manager about video device.
 */
struct VideoInfo
{
   uint32_t    mode;          // Video mode; 0 graphics, 1 text
   uint32_t    width;         // Screen width
   uint32_t    height;        // Screen height
   uint32_t    depth;         // Screen depth (0 in text mode)
};

/* Multiboot header flags. This enumerates the flags admitted by flags
 * field of MultibootHeader struct. 
 */
enum MultibootHeaderFlags
{
   AlignModulesToPage         = 0x00000001,
   IncludeMemoryInfo          = 0x00000002,
   IncludeVideoInfo           = 0x00000004,
   OverrideImageFormatParams  = 0x00010000,
};

/* Multiboot header. This header is located in OS image in order to
 * multiboot compliant OS to provide parameters for the boot process.
 */
struct MultibootHeader
{
   uint32_t             magic;      // Magic number
   uint32_t             flags;      // Flags passed to boot manager
   uint32_t             checksum;   // checksum + flags + magic must be 0
   struct ImageAddrInfo imgInfo;    // OS image information
   struct VideoInfo     videoInfo;  // Video information
};


/* ELF OS image format information. */
struct ELFInfo
{
   uint32_t          num;           // Number of ELF entries
   uint32_t          size;          // Size of each entry
   uint32_t          addr;
   uint32_t          shndx;
};

/* a.out OS image format information. */
struct AOutInfo
{
   uint32_t          tabSize;       // Size param from symbol table
   uint32_t          strSize;       // Size param from string section
   uint32_t          addr;          // Addr of a.out nlist structures
   uint32_t          reserved;      // Reserved
};

/* Image information. This union represents a generic OS image information
 * provided by boot manager as part of boot info (see below).
 */
union ImageInfo
{
   struct ELFInfo    elf;           // ELF image information
   struct AOutInfo   aout;          // a.out image information
};

/* */
struct VBEInfo
{
   uint32_t          controlInfo;   // Base address of control info
   uint32_t          modeInfo;      // Base address of mode info
   uint16_t          mode;          // Current video mode in VBE 3.0 format
   uint16_t          interfaceSeg;  // Segment for protected mode table VBE 2+
   uint16_t          interfaceOff;  // Offset for protected mode table VBE 2+
   uint16_t          interfaceLen;  // Length for protected mode table VBE 2+
};

/* Boot info flags. This enumerates the different flags admitted by 
 * flags field of BootInfo struct. 
 */
enum BootInfoFlags
{
   MemAreaInfoIncluded     = 0x00000001,
   BootDeviceInfoIncluded  = 0x00000002,
   CommandLineIncluded     = 0x00000004,
   ModulesInfoIncluded     = 0x00000008,
   AOutFormatInfoIncluded  = 0x00000010,
   ELFFormatInfoIncluded   = 0x00000020,
   MemoryMapIncluded       = 0x00000040,
   DrivesInfoIncluded      = 0x00000080,
   ROMConfigTableIncluded  = 0x00000100,
   BootLoaderNameIncluded  = 0x00000200,
   APMTableIncluded        = 0x00000400,
   GraphicsTableAvailable  = 0x00000800,
};

/* Boot information. This type is provided by boot manager to pass
 * configuration parameters to the OS.
 */
struct BootInfo
{
   uint32_t          flags;         // Flags passed from boot manager
   uint32_t          memLower;      // Length of lower memory area
   uint32_t          memUpper;      // Length of upper memory area
   uint32_t          bootDevice;    // Device from which OS is booting
   uint32_t          cmdLine;       // Command line passed by boot manager
   uint32_t          modsCount;     // Number of loaded modules
   uint32_t          modsAddr;      // Address of first loaded module
   union ImageInfo   imgInfo;       // Image information
   uint32_t          memMapLen;     // Length of memory map
   uint32_t          memMapAddr;    // Base address of memory map
   uint32_t          drivesLen;     // Length of drives vector in bytes
   uint32_t          drivesAddr;    // Base address of drives vector
   uint32_t          configTable;   // Address of ROM config table
   uint32_t          bootLoaderName;// char* of Boot loader name
   uint32_t          apmTable;      // Base address of APM table
   struct VBEInfo    vbe;           // VBE information
};

/*
 * Module information. This struct provides information for a loaded module.
 * This struct is referenced from modsAddr in boot info structure.
 */ 
struct ModuleInfo
{
   uint32_t          startAddr;     // Start address of the module
   uint32_t          endAddr;       // End address of the module
   uint32_t          string;        // Arbitrary string associated to module
   uint32_t          reserved;      // Bytes reserved
};

/* Memory map entry. This struct provides the parameters of a memory
 * map entry, describing a memory region reported by boot manager.
 */
struct MemoryMapEntry
{
   uint32_t          size;          // Size of the memory map entry
   uint32_t          addrLow;       // Base address of described memory region
   uint32_t          addrHigh;      // Base address of described memory region
   uint32_t          lenLow;        // Length of described memory region
   uint32_t          lenHigh;       // Length of described memory region
   uint32_t          type;          // Type of described memory region 
                                    // (1 for RAM; otherwise is reserved)
};

/* Drive info. This struct provides the parameters for a device drive.
 * It is referenced by drivesAddr field in BootInfo struct. 
 */ 
struct DriveInfo
{
   uint32_t          size;          // Size of the structure
   uint8_t           number;        // BIOS drive number
   uint8_t           mode;          // Drive access mode (0 CHS, 1 LBA)
   uint16_t          cylinders;     // Number of cylinders
   uint8_t           heads;         // Number of heads
   uint8_t           sectors;       // Number of sectors
   uint16_t          ports[64];     // Array of ports (up to 64, probably less)
};

/* APM table. This struct provides the APM configuration. It is referenced
 * by apmtable field in BootInfo struct. */
struct APMTable
{
   uint16_t          version;       // Version number
   uint16_t          cseg;          // Protected mode code segment for 32-bits
   uint32_t          offset;        // Offset of entry point
   uint16_t          cseg16;        // Protected mode code segment for 16-bits
   uint16_t          dseg;          // Protected mode data segment for 16-bits
   uint16_t          flags;         // Flags
   uint16_t          csegLen;       // Length of code segment for 32-bits
   uint16_t          cseg16Len;     // Length of code segment for 16-bits
   uint16_t          dsegLen;       // Length of data segment for 16-bits
};

#endif

#endif

