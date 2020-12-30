/*----------------------------------------------------------------------------------------------
*
* This file is XIUSDK's property. It contains XIUSDK's trade secret, proprietary and
* confidential information.
*
* The information and code contained in this file is only for authorized XIUSDK employees
* to design, create, modify, or review.
*
* DO NOT DISTRIBUTE, DO NOT DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER AUTHORIZATION.
*
* If you are not an intended recipient of this file, you must not copy, distribute, modify,
* or take any action in reliance on it.
*
* If you have received this file in error, please immediately notify XIUSDK and
* permanently delete the original and any copy of any file and any printout thereof.
*
*---------------------------------------------------------------------------------------------*/
/*****************************************************************************
Copyright:    www.xiusdk.cn(all rights reserved)
File name:    YNFaceDetector.h
Description:  人脸关键点定位
Author:       xiusdk
Version:      V1.2
qq group:     567648913(加群获取最新信息)
*****************************************************************************/

#ifndef YN_FACE_DETECTOR_H_
#define YN_FACE_DETECTOR_H_
 
#include "YNTypes.h"


/*************************************************
Function:    YNFaceDetector_Initialize
Description: create face detection instance
Input:   thread num
Output:  none
Return:  YNFaceDetectorRef handle
Others:  none.
*************************************************/
YN_SDK_API YNHandle YNFaceDetector_Initialize(int config);


/*************************************************
Function:    YNFaceDetector_Unintialize
Description: destory face detection instance
Input:   YNFaceDetectorRef handle
Output:  none
Return:  none
Others:  none.
*************************************************/
YN_SDK_API void  YNFaceDetector_Unintialize(YNHandle handle);


/*************************************************
Function:    YNFaceDetector_loadModels
Description: load face detection model
Input:
alignModel:  "yn_model_detect.tar"
Output: none
Return:      YNRESULT
Others:      none.
*************************************************/
YN_SDK_API int YNFaceDetector_loadModels(YNHandle handle, const char* alignModel);


/*************************************************
Function:    YNFaceDetector_Align
Description: detect face with image buffer
Input:
handle: handle created by YNFaceDetector_Initialize
image: image buffer
with,height,stride: image info
format: image pixel order
orientation: image orientation
Output:
faces: return face detect result
faceCount: return face count
Return:      YNRESULT
Others:      none.
*************************************************/
YN_SDK_API int YNFaceDetector_Align(YNHandle handle, const unsigned char* image, int width, int height, int stride,
	YN_PIXEL_FORMAT format, YN_ROTATION_TYPE orientation, YNFaces** faces, int* faceCount);

/*
detect face with image buffer
param:
handle: handle created by YNFaceDetector_Initialize
image: image buffer with BGRA 4 channels
with,height,stride: image info
result: return face detect result
faceCount: return face count
*/



#endif//YN_FACE_DETECTOR_H_