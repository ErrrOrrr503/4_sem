#ifndef LEVEL_COMMON_H
#define LEVEL_COMMON_H

#include <cinttypes>

#endif // LEVEL_COMMON_H

/* file structure (in binary):
   <level_header><wall_section><other>
*/
#define FILETYPE_DESCR_LEN 16

struct level_fileheader {
    char filetype[FILETYPE_DESCR_LEN] = "DOORkaEngine_v0";
    uint32_t version = 0;
    uint64_t walls_size; // in bytes
    uint64_t other_size;
};
