using System;
using System.Linq;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Drawing.Imaging;

namespace TestDemo
{
    class YNFaceDetector : IDisposable
    {

        IntPtr mHandle = IntPtr.Zero;
        public YNFaceDetector()
        {
            mHandle = YNFaceDetector_Initialize(0);
        }

        ~YNFaceDetector()
        {
            Release();
        }

        private void Release()
        {
            if (IntPtr.Zero != mHandle)
            {
                YNFaceDetector_Unintialize(mHandle);
                mHandle = IntPtr.Zero;
            }
        }
        public void Dispose()
        {
            Release();
        }


        //step 1. load models
        public YNRESULT loadModels(String detectModel)
        {
            YNRESULT r = YNFaceDetector_loadModels(mHandle, detectModel);
            return r;
        }

        //step 2. detect faces
        public YNFaces[] Detect(Bitmap src)
        {
            Int32 w = src.Width;
            Int32 h = src.Height;
            IntPtr faces = IntPtr.Zero;
            Int32 faceCount = 0;
            BitmapData srcData = src.LockBits(new Rectangle(0, 0, w, h), ImageLockMode.ReadOnly, PixelFormat.Format32bppArgb);
            YNRESULT r = YNFaceDetector_Align(mHandle, srcData.Scan0, w, h, srcData.Stride, 4, 0, ref faces, ref faceCount);
            src.UnlockBits(srcData);

            YNFaces[] results = new YNFaces[faceCount];
            int size = Marshal.SizeOf(typeof(YNFaces));

            for (int i = 0; i < faceCount; i++)
            {
                results[i] = new YNFaces();
                Marshal.PtrToStructure(faces, results[i]);
                faces = new IntPtr(faces.ToInt64() + size);
            }

            return results;
        }

        [DllImport("Alignment.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.None, ExactSpelling = true)]
        private static extern IntPtr YNFaceDetector_Initialize(Int32 config);

        [DllImport("Alignment.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.None, ExactSpelling = true)]
        private static extern void YNFaceDetector_Unintialize(IntPtr handle);

        [DllImport("Alignment.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, ExactSpelling = true)]
        private static extern YNRESULT YNFaceDetector_loadModels(IntPtr handle, String detectModel);

        [DllImport("Alignment.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, ExactSpelling = true)]
        private static extern YNRESULT YNFaceDetector_Align(IntPtr handle, IntPtr image, Int32 width, Int32 height, Int32 stride, int format, int orientation, ref IntPtr faces, ref Int32 faceCount);

        public enum YNRESULT
        {
            YN_OK = 0,                       // 正常运行
            YN_E_INVALID_ARG = -1,           // 无效参数
            YN_E_HANDLE = -2,                // 句柄错误
            YN_E_OUT_OF_MEMORY = -3,         // 内存不足
            YN_E_FAIL = -4,                  // 内部错误
            YN_E_DEF_NOT_FOUND = -5,         // 定义缺失
            YN_E_INVALID_PIXEL_FORMAT = -6,  // 图像格式不支持
            YN_E_FILE_NOT_FOUND = -7,        // 模型文件不存在
            YN_E_FILE_NOT_INITIALIZED = -8,  // 模型文件未初始化
            YN_E_FILE_INVALID_FORMAT = -9,   // 模型文件格式不支持
            YN_E_FILE_EXPIRE = -10,          // 模型文件过期
            YN_E_INVALID_APPID = -11,        // 包名错误
            YN_E_INVALID_AUTH = -12,         // 功能不支持
            YN_E_AUTH_EXPIRE = -13           // 功能过期
        };    

        [StructLayout(LayoutKind.Sequential)]
        public struct YNRect
        {
            public int left;
            public int top;
            public int right;
            public int bottom;
        }


        [StructLayout(LayoutKind.Sequential)]
        public struct YNPoint2f
        {
            public float x;
            public float y;

            public Point pointI()
            {
                return new Point((int)(x + 0.5), (int)(y + 0.5));
            }

            public void setPointI(Point pt)
            {
                x = pt.X;
                y = pt.Y;
            }

            public void setPointI(int X, int Y)
            {
                x = X;
                y = Y;
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        public class YNShape
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 101)]  
            public YNPoint2f[] pts = new YNPoint2f[101];

            public int ptsSize;

            public YNShape Clone()
            {
                YNShape shape = new YNShape();
                shape.ptsSize = ptsSize;
                pts.CopyTo(shape.pts, 0);
                return shape;
            }

            public void CopyTo(YNShape shape)
            {
                if (shape.pts.Count() < pts.Count())
                {
                    shape.pts = new YNPoint2f[pts.Count()];
                }
                shape.ptsSize = ptsSize;
                pts.CopyTo(shape.pts, 0);
            }

            public YNPoint2f[] Pts()
            {
                YNPoint2f[] result = new YNPoint2f[ptsSize];
                Array.Copy(pts, result, ptsSize);
                return result;
            }
        }

        [StructLayout(LayoutKind.Sequential)]
        public class YNFaces
        {
            public YNRect rect;
            public float score;
            public YNShape shape = new YNShape();
	        public int yaw;
            public int pitch;
            public int roll;
            public int ID;
        }
    }
}
