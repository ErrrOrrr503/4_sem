#ifndef LEVEL_COMMON_H
#define LEVEL_COMMON_H

#include <cinttypes>

#endif // LEVEL_COMMON_H

/* file structure (in binary):
   <level_header><wall_section>
*/
struct level_fileheader {
    const char filetype[16] = "DOORkaEngine_v0";
    const uint32_t version = 0;
    uint64_t walls_addr; // shift in bytes from the start of file, so start position of wall vector
    uint64_t walls_size; // in bytes
    uint64_t other_addr;
};
