در کادر زیر، متن کامل و اصلاح‌شده بدون هیچ‌گونه حاشیه یا متن اضافی قرار داده شده است. تمام عبارات تکراری و کلماتی مانند `content_copy` یا `note_addویرایش با Canvas` که به دلیل کپی کردن از محیط‌های دیگر وارد متن شده بودند، به‌طور کامل پاک‌سازی و فرمول‌های ریاضی و کدهای برنامه‌نویسی قالب‌بندی استاندارد شده‌اند.

کافی است روی دکمه **Copy** کلیک کنید و آن را مستقیماً در فایل `README.md` گیت‌هاب قرار دهید:

```markdown
# Intel IPP Signal Convolver

این پروژه شامل کلاس `SignalConvolver` است که به کمک کتابخانه بهینه‌شده **Intel IPP (Integrated Performance Primitives)**، عملیات کانولوشن (Convolution) را بر روی سیگنال‌های یک‌بعدی با دقت‌های اعشاری ۳۲ بیتی (`float`) و ۶۴ بیتی (`double`) انجام می‌دهد. این پیاده‌سازی از حالت‌های مختلف کانولوشن نظیر `full`، `same` و `valid` پشتیبانی می‌کند.

---

## 📋 ویژگی‌ها (Features)

* **پشتیبانی از دقت‌های مختلف:** محاسبات کانولوشن برای داده‌های ۳۲ بیتی (`Ipp32f`) و ۶۴ بیتی (`Ipp64f`).
* **انواع کانولوشن:**
  * **Full:** خروجی با طول $N + M - 1$ (کانولوشن کامل).
  * **Same:** خروجی هم‌اندازه با سیگنال اصلی.
  * **Valid:** خروجی بدون اعمال لبه‌های ناشی از Padding (طول خروجی $\max(M, N) - \min(M, N) + 1$).
* **پشتیبانی از کانولوشن دارای Bias:** استفاده از تابع داخلی `ippsConvBiased_32f` برای اعمال آفست مستقیم روی سیگنال خروجی.
* **کارایی بالا:** بهره‌گیری از بهینه‌سازی‌های سخت‌افزاری پردازنده‌های Intel.

---

##  پیش‌نیازها و نصب کتابخانه‌ها

برای کامپایل و اجرای این پروژه، به ابزارهای ساخت ++C و کتابخانه **Intel IPP** نیاز دارید.

### ۱. نصب Intel IPP

#### روش اول: نصب از طریق Intel oneAPI (پیشنهادی)
Intel IPP به عنوان بخشی از ابزار **Intel oneAPI Base Toolkit** ارائه می‌شود. برای نصب در توزیع‌های مبتنی بر دبیان/ابونتو می‌توانید از دستور زیر استفاده کنید:

```bash
sudo apt update
sudo apt install intel-oneapi-ipp
```

#### روش دوم: نصب نسخه مستقل (Standalone)
اگر مایلید صرفاً کتابخانه IPP را دانلود کنید:
1. به [صفحه دانلود رسمی Intel IPP](https://www.intel.com/content/www/us/en/developer/tools/oneapi/ipp.html) مراجعه کنید.
2. نسخه سازگار با سیستم‌عامل خود (Windows, Linux, macOS) را دریافت و نصب کنید.

---

## نحوه کامپایل و لینک کردن

از آنجا که این پروژه به توابع داخلی IPP متکی است، هنگام کامپایل باید مسیر هدرها (`include`) و کتابخانه‌ها (`libs`) را به کامپایلر خود معرفی و کتابخانه‌های `ippcore` و `ippsignal` را لینک کنید.

### در سیستم‌عامل لینوکس (g++)

کد زیر را متناسب با مسیر نصب IPP در سیستم خود اجرا کنید (معمولاً در `/opt/intel/oneapi/ipp/latest` قرار دارد):

```bash
g++ -std=c++11 main.cpp -o signal_convolver \
    -I/opt/intel/oneapi/ipp/latest/include \
    -L/opt/intel/oneapi/ipp/latest/lib/intel64 \
    -lippsignal -lippcore
```

### در سیستم‌عامل ویندوز (MSVC)

در تنظیمات پروژه Visual Studio خود تغییرات زیر را اعمال کنید:
1. **Additional Include Directories:** مسیر پوشه `include` مربوط به IPP.
2. **Additional Library Directories:** مسیر پوشه `lib` معماری مورد نظر (مانند `intel64`).
3. **Additional Dependencies:** اضافه کردن فایل‌های `ipps.lib` و `ippcore.lib` (یا معادل‌های داینامیک آن‌ها).

---

## مستندات توابع استفاده شده از IPP

توابع کلیدی استفاده شده در پشت صحنه این کلاس به شرح زیر هستند:

### ۱. محاسبه اندازه بافر محاسباتی
```cpp
IPPAPI(IppStatus, ippsConvolveGetBufferSize, (int src1Len, int src2Len, IppDataType dataType, IppEnum algType, int* pBufferSize))
```
* **کاربرد:** تخمین فضای بافر مورد نیاز در حافظه برای انجام محاسبات سریع کانولوشن.

### ۲. توابع اصلی کانولوشن سیگنال
```cpp
IPPAPI(IppStatus, ippsConvolve_32f, (const Ipp32f* pSrc1, int src1Len, const Ipp32f* pSrc2, int src2Len, Ipp32f* pDst, IppEnum algType, Ipp8u* pBuffer))
IPPAPI(IppStatus, ippsConvolve_64f, (const Ipp64f* pSrc1, int src1Len, const Ipp64f* pSrc2, int src2Len, Ipp64f* pDst, IppEnum algType, Ipp8u* pBuffer))
```
* **کاربرد:** انجام کانولوشن خطی بر روی سیگنال‌های یک‌بعدی ۳۲ بیتی و ۶۴ بیتی اعشاری.

### ۳. کانولوشن همراه با مقدار Bias
```cpp
IPPAPI(IppStatus, ippsConvBiased_32f, (const Ipp32f *pSrc1, int src1Len, const Ipp32f *pSrc2, int src2Len, Ipp32f *pDst, int dstLen, int bias))
```
* **کاربرد:** اعمال یک مقدار ثابت (Bias) به خروجی کانولوشن در طول مشخصی از سیگنال.
```
