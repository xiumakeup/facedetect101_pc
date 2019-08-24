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
File name:    YNTypes.h
Description:  人脸关键点定位
Author:       xiusdk
Version:      V1.0
Date:         20190101-20201230
*****************************************************************************/
#ifndef YN_TYPES_H_
#define YN_TYPES_H_


#ifdef _MSC_VER
#	ifdef __cplusplus
#		ifdef YN_STATIC_LIB
#			define YN_SDK_API  extern "C"
#		else
#			ifdef YN_SDK_EXPORTS
#				define YN_SDK_API extern "C" __declspec(dllexport)
#			else
#				define YN_SDK_API extern "C" __declspec(dllimport)
#			endif
#		endif
#	else
#		ifdef YN_STATIC_LIB
#			define YN_SDK_API
#		else
#			ifdef YN_SDK_EXPORTS
#				define YN_SDK_API __declspec(dllexport)
#			else
#				define YN_SDK_API __declspec(dllimport)
#			endif
#		endif
#	endif
#else /* _MSC_VER */
#	ifdef __cplusplus
#		ifdef YN_SDK_EXPORTS
#			define YN_SDK_API extern "C" __attribute__((visibility ("default")))
#		else
#			define YN_SDK_API extern "C"
#		endif
#	else
#		ifdef YN_SDK_EXPORTS
#			define YN_SDK_API __attribute__((visibility ("default")))
#		else
#			define YN_SDK_API
#		endif
#	endif
#endif

///== handle declearation
typedef void YNVOID;
typedef YNVOID* YNHandle;

///== result declearation
typedef int YNRESULT;


#define YN_OK (0)                       // 正常运行
#define YN_E_INVALID_ARG (-1)           // 无效参数
#define YN_E_HANDLE (-2)                // 句柄错误
#define YN_E_OUT_OF_MEMORY (-3)         // 内存不足
#define YN_E_FAIL (-4)                  // 内部错误
#define YN_E_DEF_NOT_FOUND (-5)         // 定义缺失
#define YN_E_INVALID_PIXEL_FORMAT (-6)  // 图像格式不支持
#define YN_E_FILE_NOT_FOUND (-7)        // 模型文件不存在
#define YN_E_FILE_NOT_INITIALIZED (-8)  // 模型文件未初始化
#define YN_E_FILE_INVALID_FORMAT (-9)   // 模型文件格式不支持
#define YN_E_FILE_EXPIRE (-10)           // 模型文件过期
#define YN_E_INVALID_APPID (-11)        // 包名错误
#define YN_E_INVALID_AUTH (-12)         // 功能不支持
#define YN_E_AUTH_EXPIRE (-13)          // 功能过期

// 使用单线程或双线程
#define YN_MOBILE_ALIGN_SINGLE_THREAD        0x00000000
#define YN_MOBILE_ALIGN_MULTI_THREAD         0x00000010  

/// st pixel format definition
typedef enum {
	YN_PIX_FMT_GRAY8,   // Y    1        8bpp ( 单通道8bit灰度像素 )
	YN_PIX_FMT_YUV420P, // YUV  4:2:0   12bpp ( 3通道, 一个亮度通道, 另两个为U分量和V分量通道, 所有通道都是连续的 )
	YN_PIX_FMT_NV12,    // YUV  4:2:0   12bpp ( 2通道, 一个通道是连续的亮度通道, 另一通道为UV分量交错 )
	YN_PIX_FMT_NV21,    // YUV  4:2:0   12bpp ( 2通道, 一个通道是连续的亮度通道, 另一通道为VU分量交错 )
	YN_PIX_FMT_BGRA8888,// BGRA 8:8:8:8 32bpp ( 4通道32bit BGRA 像素 )
	YN_PIX_FMT_BGR888,  // BGR  8:8:8   24bpp ( 3通道24bit BGR 像素 )
	YN_PIX_FMT_RGBA8888,// BGRA 8:8:8:8 32bpp ( 4通道32bit RGBA 像素 )
	YN_PIX_FMT_RGB888,  // BGR  8:8:8   24bpp ( 3通道24bit RGB 像素 )
} YN_PIXEL_FORMAT;


typedef enum {
	YN_CLOCKWISE_ROTATE_0 = 0,  // 图像不需要转向
	YN_CLOCKWISE_ROTATE_90 = 1, // 图像需要顺时针旋转90度
	YN_CLOCKWISE_ROTATE_180 = 2,// 图像需要顺时针旋转180度
	YN_CLOCKWISE_ROTATE_270 = 3 // 图像需要顺时针旋转270度
} YN_ROTATION_TYPE;


#define MAX_PTS_SIZE 101

typedef struct {
	float x;
	float y;
} YNPoint2f;

typedef struct {
	YNPoint2f pts[MAX_PTS_SIZE];
	int ptsSize;
} YNShape;

typedef struct{
	int left;
	int top;
	int right;
	int bottom;
} YNRect;

typedef struct {
	YNRect rect;            ///< 代表面部的矩形区域
	float score;            ///< 置信度
	YNShape shape;          ///< 人脸101关键点的数组
	int yaw;                ///< 水平转角，真实度量的左负右正
	int pitch;              ///< 俯仰角，真实度量的上负下正
	int roll;               ///< 旋转角，真实度量的左负右正
	int ID;                 ///< faceID: 每个检测到的人脸拥有唯一的faceID。人脸跟踪丢失以后重新被检测到，会有一个新的faceID
} YNFaces;


#endif//YN_TYPES_H_