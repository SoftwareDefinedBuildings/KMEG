#ifndef __STORAGE_VOLUME_H__
#define __STORAGE_VOLUME_H__

#include "Stm25p.h"

#define VOLUME_LOGTEST 0
#define VOLUME_CONFIGTEST 1

static const stm25p_volume_info_t STM25P_VMAP[ 2 ] = {
    { base : 0, size : 4 },
    { base : 4, size : 2 },
};

#endif
