#ifndef __COMMON_H__
#define __COMMON_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

typedef struct _imageROI
{
	int iLeft, iTop;
	int iWidth, iHeight;
}IMAGEROI;

typedef struct _imageInfo
{
	unsigned char * pData;
	int iChannel, iDepth;
	int iWidth, iWStep;
	int iHeight;
}IMAGEINFO;

typedef struct _pyramidData
{
	int iLevel;
	IMAGEINFO * pImage;
}PYRAMIDDATA;

typedef struct _feDistortParam
{
	double dRadius, dCx, dCy;
	double coefs[3];
}FEDISTORTPARAM;

typedef struct _feImageContext
{
	IMAGEINFO image;

	// output
	int iSpherialRadius;
	int iDstHeight;
}FEIMAGECONTEXT;

typedef struct _mappingInfo
{
	int * pCoordinate;
	int iWidth;// , iWStep;
	int iHeight;
}MAPPINGINFO;

typedef struct _HDRParams
{
	int iWeight;
	int iReference;
	bool bShift;
}HDRPARAMS;

int loadAllMap(const char * pPath, MAPPINGINFO maps[4], int * pSpherialRadius);
void releaseMaps(MAPPINGINFO maps[4]);
void releaseImageInfo(IMAGEINFO * pImage);
int loadImageData(const char *pFileName, int iImgW, int iImgH, unsigned char **ppData);
IMAGEINFO makeImageInfo(int imageW, int imageH, unsigned char *pImageData);
void releaseImageData(unsigned char **ppData);
void fuse(const char *pFileName1, const char *pFileName2, const char *pMapPath, const char *pSavePath);
#ifdef __cplusplus
}
#endif

#endif
