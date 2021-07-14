#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

extern "C" __attribute__((visibility("default"))) __attribute__((used))
int32_t native_add(int32_t x, int32_t y) {
    return x + y;
}

extern "C" __attribute__((visibility("default"))) __attribute__((used))
int loadImageData(const char *pFileName, int iImgW, int iImgH, unsigned char **ppData) {
    FILE *pFile = nullptr;

    if (!ppData)
        return -1;

    pFile = fopen(pFileName, "rb");
    if (!pFile)
        return -1;

    *ppData = (unsigned char *) malloc(iImgW * iImgH * 3);
    if (!*ppData) {
        fclose(pFile);
        return -1;
    }

    fclose(pFile);
    return 0;
}

extern "C" __attribute__((visibility("default"))) __attribute__((used))
void releaseImageData(unsigned char **ppData) {
    if (!*ppData) {
        return;
    } else {
        free(*ppData);
    }
}

extern "C" __attribute__((visibility("default"))) __attribute__((used))
IMAGEINFO makeImageInfo(int imageW, int imageH, unsigned char *pImageData) {
    IMAGEINFO info;
    info.iChannel = 3;
    info.iDepth = 8;

    info.iHeight = imageH;
    info.iWidth = imageW;
    info.iWStep = imageW * info.iChannel;
    info.pData = pImageData;

    return info;
}

int clamp(int lower, int higher, int val) {
    if (val < lower)
        return 0;
    else if (val > higher)
        return 255;
    else
        return val;
}

int getRotatedImageByteIndex(int x, int y, int rotatedImageWidth) {
    return rotatedImageWidth * (y + 1) - (x + 1);
}