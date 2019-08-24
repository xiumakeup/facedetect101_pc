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
Copyright:    www.xiusdk.cn
File name:    YNFaceDetector.h
Description:  人脸关键点定位
Author:       xiusdk
Version:      V1.0
Date:         20190101-20201230
*****************************************************************************/

#ifndef YN_FACE_DETECTOR_H_
#define YN_FACE_DETECTOR_H_
 
#include "YNTypes.h"

typedef struct YNFaceDetector YNFaceDetector;
typedef YNFaceDetector* YNFaceDetectorRef;


/*************************************************
Function:    YNFaceDetector_Initialize
Description: create face detection instance
Input:   "592100DC-905B-4B94-8101-3E2AF63F5831"
Output:  none
Return:  YNFaceDetectorRef handle
Others:  none.
*************************************************/
YN_SDK_API YNFaceDetectorRef YNFaceDetector_Initialize(const char* key);


/*************************************************
Function:    YNFaceDetector_Unintialize
Description: destory face detection instance
Input:   YNFaceDetectorRef handle
Output:  none
Return:  none
Others:  none.
*************************************************/
YN_SDK_API YNVOID  YNFaceDetector_Unintialize(YNFaceDetectorRef handle);


/*************************************************
Function:    YNFaceDetector_loadModels
Description: load face detection model
Input:
alignModel:  "yn_model_detect.tar"
Output: none
Return:      YNRESULT
Others:      none.
*************************************************/
YN_SDK_API YNRESULT YNFaceDetector_loadModels(YNFaceDetectorRef handle, const char* alignModel);


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
YN_SDK_API YNRESULT YNFaceDetector_Align(YNFaceDetectorRef handle, const unsigned char* image, int width, int height, int stride,
	int format, int orientation, YNFaces** faces, int* faceCount);


/*************************************************
c-example:
YNFaceDetectorRef handle = YNFaceDetector_Initialize("592100DC-905B-4B94-8101-3E2AF63F5831");
YNFaceDetector_loadModels(handle, "/your/path/of/yn_model_detect.tar");
YNFaces* faces = NULL; 
int faceCount = 0;
YNFaceDetector_Align(handle, image_buffer, width, height, stride, YN_PIX_FMT_BGRA8888, YN_CLOCKWISE_ROTATE_0, &faces, &faceCount);
for(int i = 0; i < faceCount; i++){
   YNFaces& face = faces[i]; // get detected face info
}
YNFaceDetector_Unintialize(handle);
*************************************************/

#endif//YN_FACE_DETECTOR_H_