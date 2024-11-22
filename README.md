# IntelIpp
This class provides a set of functions for performing signal convolution  using the Intel IPP (Integrated Performance Primitives) library. It supports  both 32-bit and 64-bit floating-point data types and offers various types of  convolutions (e.g., "same", "valid", "full") for the input signals.



/* /////////////////////////////////////////////////////////////////////////////
//                  Convolution functions
///////////////////////////////////////////////////////////////////////////// */

/* /////////////////////////////////////////////////////////////////////////////
//  Names:  ippsConvolveGetBufferSize
//
//  Purpose:     Get the size (in bytes) of the buffer for ippsConvolve's internal calculations.
//
//  Parameters:
//    src1Len     - Length of the first source vector.
//    src2Len     - Length of the second source vector.
//    dataType    - Data type for convolution {Ipp32f|Ipp64f}.
//    algType     - Selector for the algorithm type. Contains IppAlgType values.
//    pBufferSize - Pointer to the calculated buffer size (in bytes).
//  Return:
//   ippStsNoErr       - OK
//   ippStsNullPtrErr  - pBufferSize is NULL.
//   ippStsSizeErr     - Vector's length is not positive.
//   ippStsDataTypeErr - Unsupported data type.
//   ippStsAlgTypeErr - Unsupported algorithm type.
*/
IPPAPI(IppStatus, ippsConvolveGetBufferSize, (int src1Len, int src2Len, IppDataType dataType, IppEnum algType, int* pBufferSize))

/* /////////////////////////////////////////////////////////////////////////////
// Name:       ippsConvolve_32f, ippsConvolve_64f
// Purpose:    Perform a linear convolution of 1D signals.
// Parameters:
//    pSrc1   - Pointer to the first source vector.
//    src1Len - Length of the first source vector.
//    pSrc2   - Pointer to the second source vector.
//    src2Len - Length of the second source vector.
//    pDst    - Pointer to the destination vector.
//    algType - Selector for the algorithm type. Contains IppAlgType values.
//    pBuffer - Pointer to the buffer for internal calculations.
// Returns:    IppStatus
//    ippStsNoErr       - OK.
//    ippStsNullPtrErr  - One of the pointers is NULL.
//    ippStsSizeErr     - Vector's length is not positive.
//    ippStsAlgTypeErr  - Unsupported algorithm type.
//  Notes:
//          Length of the destination data vector is src1Len+src2Len-1.
//          The input signals are exchangeable because of the commutative
//          property of convolution.
//          Some other values may be returned the by FFT transform functions.
*/
IPPAPI(IppStatus, ippsConvolve_32f, (const Ipp32f* pSrc1, int src1Len, const Ipp32f* pSrc2, int src2Len, Ipp32f* pDst, IppEnum algType, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsConvolve_64f, (const Ipp64f* pSrc1, int src1Len, const Ipp64f* pSrc2, int src2Len, Ipp64f* pDst, IppEnum algType, Ipp8u* pBuffer))

/* /////////////////////////////////////////////////////////////////////////////
//  Name:       ippsConvBiased_32f
//  Purpose:    Linear Convolution of 1D signals with a bias.
//  Parameters:
//      pSrc1               pointer to the first source vector
//      pSrc2               pointer to the second source vector
//      src1Len             length of the first source vector
//      src2Len             length of the second source vector
//      pDst                pointer to the destination vector
//      dstLen              length of the destination vector
//      bias
//  Returns:    IppStatus
//      ippStsNullPtrErr        pointer(s) to the data is NULL
//      ippStsSizeErr           length of the vectors is less or equal zero
//      ippStsNoErr             otherwise
*/
IPPAPI(IppStatus, ippsConvBiased_32f, (const Ipp32f *pSrc1, int src1Len, const Ipp32f *pSrc2, int src2Len, Ipp32f *pDst, int dstLen, int bias))

//

SignalConvolver
این پروژه شامل یک کلاس SignalConvolver است که به کمک کتابخانه Intel IPP (Integrated Performance Primitives) عملیات کانولوشن (همبستگی) بر روی دو سیگنال را با استفاده از داده‌های شناور 32 بیتی یا 64 بیتی انجام می‌دهد. این کلاس از چندین نوع کانولوشن مختلف مانند "full"، "same" و "valid" پشتیبانی می‌کند و به کاربران این امکان را می‌دهد که سیگنال‌ها را با استفاده از این روش‌ها پردازش کنند.

پیش‌نیازها
برای استفاده از این پروژه، شما نیاز به نصب کتابخانه Intel IPP دارید. این کتابخانه یک مجموعه از توابع بهینه‌شده برای پردازش سیگنال، رمزنگاری، فشرده‌سازی و بسیاری از عملیات دیگر است که بر روی پردازنده‌های مختلف عملکرد بسیار خوبی دارد.

1. نصب Intel IPP
روش 1: نصب از طریق Intel oneAPI
Intel IPP به‌عنوان بخشی از Intel oneAPI عرضه می‌شود. برای نصب آن به‌طور رسمی می‌توانید از لینک‌های زیر استفاده کنید:

Intel oneAPI SDK
در اینجا چند مرحله برای نصب این کتابخانه آورده شده است:

ابتدا وارد صفحه دانلود Intel oneAPI شوید و نسخه مناسب سیستم عامل خود را انتخاب کنید.
پس از نصب، محیط توسعه را راه‌اندازی کنید.
از دستور زیر برای نصب Intel IPP استفاده کنید:
bash
Copy code
sudo apt install intel-oneapi-ipp
روش 2: نصب از طریق Intel IPP (جداگانه)
اگر تنها نیاز به کتابخانه IPP دارید، می‌توانید نسخه جداگانه آن را از صفحه Intel IPP Download دریافت کنید.

پس از دانلود، دستورالعمل‌های نصب را دنبال کنید.

2. نصب وابستگی‌ها
برای اجرای این پروژه، نیاز به کتابخانه‌های استاندارد C++ مانند <iostream> و <stdexcept> خواهید داشت که به‌طور پیش‌فرض در اکثر سیستم‌ها موجود هستند.

نحوه استفاده
1. ساخت و لینک کردن پروژه
برای استفاده از کلاس SignalConvolver در پروژه خود، ابتدا باید کتابخانه Intel IPP را به پروژه اضافه کنید. در اینجا نحوه لینک کردن آن در سیستم‌های لینوکسی و ویندوزی آورده شده است.

لینوکس:
اگر از g++ برای ساخت پروژه استفاده می‌کنید، می‌توانید پروژه را به‌طور زیر کامپایل و لینک کنید:

bash
Copy code
g++ -std=c++11 -o signal_convolver main.cpp -I/path/to/ipp/include -L/path/to/ipp/lib -lippcore -lippsignal



