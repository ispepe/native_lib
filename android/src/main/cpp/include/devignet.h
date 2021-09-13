#ifndef __DEVIGNET_H__
#define __DEVIGNET_H__

#ifdef __cplusplus
extern "C" {
#endif

//#define VIGNET_BGR

typedef struct _vignetInfo
{
    int iCx, iCy, iCr;
    float k1, k2;
}VIGNETINFO;

void deVignet_bgr(IMAGEINFO *pImg, VIGNETINFO *pVignet);
void deVignet_yuv(IMAGEINFO *pImg, VIGNETINFO *pVignet);
int loadVignetPara(const char * pFilePath, VIGNETINFO Vignet[2]);

#ifdef __cplusplus
}
#endif

#endif
