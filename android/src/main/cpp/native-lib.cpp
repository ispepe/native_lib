#include "common.h"
#include "opencv2/opencv.hpp"
#include "twoFisheyeBlend.h"

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

void imgInfo2Mat(const IMAGEINFO *pImage, cv::Mat &dst) {
    int iType = 8 == pImage->iDepth ? CV_8U : (16 == pImage->iDepth ? CV_16S : CV_32S);
    cv::Mat image(pImage->iHeight, pImage->iWidth, CV_MAKETYPE(iType, pImage->iChannel));
    const unsigned char *pData = pImage->pData;

    for (int i = 0; i < pImage->iHeight; i++, pData += pImage->iWStep) {
        uchar *pCurRow = image.row(i).ptr<uchar>();
        memcpy(pCurRow, pData, pImage->iWidth * pImage->iChannel * (pImage->iDepth >> 3));
    }
    dst = image;
}

int
createImageInfo(int iWidth, int iHeight, int iDepth, int iChannel, bool bInit, IMAGEINFO *pImage) {
    int iWStep;

    if (!pImage)
        return -1;

    if (!bInit) {
        if (pImage->pData) {
            free(pImage->pData);
            pImage->pData = NULL;
        }
    }

    pImage->iDepth = iDepth;
    iDepth >>= 3;
    iWStep = iWidth * iChannel * iDepth;
    /*if(1 == iDepth)
     iWStep = (iWStep + 3) & 0x7ffffffc;*/
    pImage->pData = (unsigned char *) malloc(iWStep * iHeight);
    if (!pImage->pData)
        return -1;

    pImage->iWidth = iWidth;
    pImage->iWStep = iWStep;
    pImage->iHeight = iHeight;
    pImage->iChannel = iChannel;
    return 0;
}

void Mat2imgInfo(cv::Mat dst, IMAGEINFO *pImage) {
    createImageInfo(dst.cols, dst.rows, (dst.step.buf[1] * 8) / dst.channels(), dst.channels(),
                    true, pImage);

    unsigned char *pData = pImage->pData;
    for (int i = 0; i < pImage->iHeight; i++, pData += pImage->iWStep) {
        uchar *pCurRow = dst.row(i).ptr<uchar>();
        memcpy(pData, pCurRow, pImage->iWidth * pImage->iChannel);
    }
}

extern "C" __attribute__((visibility("default"))) __attribute__((used))
int
fuse(const char *pFileName1, const char *pFileName2, const char *pMapPath, const char *pSavePath) {
    cv::Mat srcImgs[2], result;
    int iSpherialRadius;
    FEIMAGECONTEXT imgCxt[2];
    MAPPINGINFO maps[4];
    IMAGEINFO fuseResult;
    int i;
    srcImgs[0] = cv::imread(cv::String(pFileName1));
    srcImgs[1] = cv::imread(cv::String(pFileName2));
    int reValue = -1;
    if (loadAllMap(pMapPath, maps, &iSpherialRadius)) {
        printf("load map files failed.\n");
        reValue = -1;
    } else {
        for (i = 0; i < 2; i++) {
            imgCxt[i].iSpherialRadius = iSpherialRadius;
            imgCxt[i].iDstHeight = iSpherialRadius * 2 + 1;
            Mat2imgInfo(srcImgs[i], &imgCxt[i].image);
        }

        if (fuseFinal(imgCxt, maps, &fuseResult)) {
            printf("fuse failed.\n");
            reValue = -2;
        } else {
            imgInfo2Mat(&fuseResult, result);
            imwrite(cv::String(pSavePath), result);
            reValue = 1;
        }
    }

//    cv::waitKey();

    releaseMaps(maps);
    releaseImageInfo(&imgCxt[0].image);
    releaseImageInfo(&imgCxt[1].image);
    releaseImageInfo(&fuseResult);
    return reValue;
}