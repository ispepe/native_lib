import 'dart:ffi' as ffi;

class ImageROI extends ffi.Struct {
  @ffi.Int32()
  external int iLeft;

  @ffi.Int32()
  external int iTop;

  @ffi.Int32()
  external int iWidth;

  @ffi.Int32()
  external int iHeight;
}

class ImageInfo extends ffi.Struct {
  external ffi.Pointer<ffi.Uint8> pData;

  @ffi.Int32()
  external int iChannel;

  @ffi.Int32()
  external int iDepth;

  @ffi.Int32()
  external int iWidth;

  @ffi.Int32()
  external int iWStep;

  @ffi.Int32()
  external int iHeight;
}

class PyramidData extends ffi.Struct {
  @ffi.Int32()
  external int iLevel;

  external ffi.Pointer<ImageInfo> pImage;
}

class FeDistortParam extends ffi.Struct {
  @ffi.Double()
  external double dRadius;

  @ffi.Double()
  external double dCx;

  @ffi.Double()
  external double dCy;

  @ffi.Array.multi([3])
  external ffi.Array<ffi.Double> coefs;
}

class FeImageContext extends ffi.Struct {
  external ImageInfo image;

  @ffi.Int32()
  external int iSpherialRadius;

  @ffi.Int32()
  external int iDstHeight;
}

class MappingInfo extends ffi.Struct {
  external ffi.Pointer<ffi.Int32> pCoordinate;

  @ffi.Int32()
  external int iWidth;

  @ffi.Int32()
  external int iHeight;
}

class HDRParams extends ffi.Struct {
  @ffi.Int32()
  external int iWeight;

  @ffi.Int32()
  external int iReference;

  @ffi.Uint8()
  external int bShift;
}

const int true_1 = 0;

const int false_1 = -1;

const int __bool_true_false_are_defined = 1;
