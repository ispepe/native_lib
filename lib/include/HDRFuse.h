#ifndef __HDR_FUSE_H__
#define __HDR_FUSE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

int HDRFuse(const IMAGEINFO images[], int iImgNum, HDRPARAMS * pPars, IMAGEINFO * pResult);

#ifdef __cplusplus
}
#endif

#endif
