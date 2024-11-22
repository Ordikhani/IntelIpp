////#include <stdio.h>
////#include "ipp.h"

////#define PRINT_INFO(feature, text) printf("  %-30s= ", #feature); \
////      printf("%c\t%c\t", (cpuFeatures & feature) ? 'Y' : 'N', (enabledFeatures & feature) ? 'Y' : 'N'); \
////      printf( #text "\n")

////int main(int argc, char* argv[])
////{
////      const       IppLibraryVersion *libVersion;
////      IppStatus   status;
////      Ipp64u      cpuFeatures, enabledFeatures;

////      ippInit();                      /* Initialize Intel(R) IPP library */
////      libVersion = ippGetLibVersion(); /* Get Intel(R) IPP library version info */
////      printf("%s %s\n", libVersion->Name, libVersion->Version);

////      status = ippGetCpuFeatures(&cpuFeatures, 0); /* Get CPU features and features enabled with selected library level */
////      if (ippStsNoErr != status) return status;
////      enabledFeatures = ippGetEnabledCpuFeatures();
////      printf("Features supported: by CPU\tby Intel(R) IPP\n");
////      printf("------------------------------------------------\n");
////      PRINT_INFO(ippCPUID_MMX,        Intel(R) Architecture MMX technology supported);
////      PRINT_INFO(ippCPUID_SSE,        Intel(R) Streaming SIMD Extensions (Intel(R) SSE));
////      PRINT_INFO(ippCPUID_SSE2,       Intel(R) Streaming SIMD Extensions 2 (Intel(R) SSE2));
////      PRINT_INFO(ippCPUID_SSE3,       Intel(R) Streaming SIMD Extensions 3 (Intel(R) SSE3));
////      PRINT_INFO(ippCPUID_SSSE3,      Supplemental Streaming SIMD Extensions 3 (SSSE3));
////      PRINT_INFO(ippCPUID_MOVBE,      Intel(R) MOVBE instruction);
////      PRINT_INFO(ippCPUID_SSE41,      Intel(R) Streaming SIMD Extensions 4.1 (Intel(R) SSE4.1));
////      PRINT_INFO(ippCPUID_SSE42,      Intel(R) Streaming SIMD Extensions 4.2 (Intel(R) SSE4.2));
////      PRINT_INFO(ippCPUID_AVX,        Intel(R) Advanced Vector Extensions (Intel(R) AVX) instruction set);
////      PRINT_INFO(ippAVX_ENABLEDBYOS,  Intel(R) Advanced Vector Extensions instruction set is supported by OS);
////      PRINT_INFO(ippCPUID_AES,        Intel(R) AES New Instructions (Intel(R) AES-NI));
////      PRINT_INFO(ippCPUID_CLMUL,      Intel(R) CLMUL instruction);
////      PRINT_INFO(ippCPUID_RDRAND,     Intel(R) RDRAND instruction);
////      PRINT_INFO(ippCPUID_F16C,       Intel(R) F16C new instructions);
////      PRINT_INFO(ippCPUID_AVX2,       Intel(R) Advanced Vector Extensions 2 instruction set);
////      PRINT_INFO(ippCPUID_ADCOX,      Intel(R) ADOX/ADCX new instructions);
////      PRINT_INFO(ippCPUID_RDSEED,     Intel(R) RDSEED instruction);
////      PRINT_INFO(ippCPUID_PREFETCHW,  Intel(R) PREFETCHW instruction);
////      PRINT_INFO(ippCPUID_SHA,        Intel(R) Secure Hash Algorithm - New Instructions (Intel SHA-NI));
////      PRINT_INFO(ippCPUID_AVX512F,    Intel(R) Advanced Vector Extensions 512 (Intel(R) AVX-512) Foundation instruction set);
////      PRINT_INFO(ippCPUID_AVX512CD,   Intel(R) Advanced Vector Extensions 512 CD instruction set);
////      PRINT_INFO(ippCPUID_AVX512ER,   Intel(R) Advanced Vector Extensions 512 ER instruction set);
////      PRINT_INFO(ippCPUID_AVX512PF,   Intel(R) Advanced Vector Extensions 512 PF instruction set);
////      PRINT_INFO(ippCPUID_AVX512BW,   Intel(R) Advanced Vector Extensions 512 BW instruction set);
////      PRINT_INFO(ippCPUID_AVX512VL,   Intel(R) Advanced Vector Extensions 512 VL instruction set);
////      PRINT_INFO(ippCPUID_AVX512VBMI, Intel(R) Advanced Vector Extensions 512 Bit Manipulation instructions);
////      PRINT_INFO(ippCPUID_MPX,        Intel(R) Memory Protection Extensions (Intel(R) MPX));
////      PRINT_INFO(ippCPUID_AVX512_4FMADDPS,    Intel(R) Advanced Vector Extensions 512 DL floating-point single precision);
////      PRINT_INFO(ippCPUID_AVX512_4VNNIW,      Intel(R) Advanced Vector Extensions 512 DL enhanced word variable precision);
////      PRINT_INFO(ippCPUID_KNC,        Intel(R) Xeon Phi Coprocessor);
////      PRINT_INFO(ippCPUID_AVX512IFMA, Intel(R) Advanced Vector Extensions 512 IFMA (PMADD52) instruction set);
////      PRINT_INFO(ippAVX512_ENABLEDBYOS,       Intel(R) Advanced Vector Extensions 512 is supported by OS);
////      return 0;
////}


//#include <iostream>
//#include <ipp.h>
//#include <ipps.h>
//int main() {
//    //
//    Ipp32f signal1[] = {1.0f, 2.0f, 3.0f, 4.0f};
//    int signal1Len = sizeof(signal1) / sizeof(Ipp32f);

//    //
//    Ipp32f signal2[] = {0.5f, 0.5f};
//    int signal2Len = sizeof(signal2) / sizeof(Ipp32f);

//    // : signal1Len + signal2Len - 1
//    int resultLen = signal1Len + signal2Len - 1;

//    //
//    Ipp32f* result = new Ipp32f[resultLen];

//    //
//    int bufferSize = 0;
//    IppStatus status = ippsConvolveGetBufferSize(signal1Len, signal2Len, ipp32f, ippAlgAuto, &bufferSize);

//    if (status != ippStsNoErr) {
//        std::cerr << "Error in ippsConvolveGetBufferSize: " << status << std::endl;
//        delete[] result;
//        return -1;
//    }

//    //
//    Ipp8u* buffer = ippsMalloc_8u(bufferSize);

//    //
//    status = ippsConvolve_32f(signal1, signal1Len, signal2, signal2Len, result, ippAlgAuto, buffer);

//    if (status == ippStsNoErr) {
//        std::cout << "Convolution Result:" << std::endl;
//        for (int i = 0; i < resultLen; i++) {
//            std::cout << result[i] << " ";
//        }
//        std::cout << std::endl;
//    } else {
//        std::cerr << "Error in ippsConvolve_32f: " << status << std::endl;
//    }

//    //
//    delete[] result;
//    ippsFree(buffer);

//    return 0;
//}





#include <iostream>
#include "signalconvolver.h"

int main() {
    try {
        SignalConvolver convolver;

        //use  Ipp32f
        std::vector<Ipp32f> signal1_32f = {1.0f, 2.0f, 3.0f, 4.0f};
        std::vector<Ipp32f> signal2_32f = {0.5f, 0.5f};
        convolver.setSignals(signal1_32f, signal2_32f, SignalConvolver::Float32);
        convolver.convolve();
        std::cout << "Convolution Result (32f) with 'same':" << std::endl;
        convolver.convolvesame(true); // same state conv
        for (auto val : convolver.getResult32f()) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
std::cout << "Convolution Result (32f) with 'valid':" << std::endl;
        convolver.convolvevalid(); // valid state conv
        for (auto val : convolver.getResult32f()) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
std::cout << "Convolution Result (32f) with 'full':" << std::endl;
        convolver.convolvefull(); // full state conv
        for (auto val : convolver.getResult32f()) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
        std::cout << "Convolution Result (32f):" << std::endl;
        for (auto val : convolver.getResult32f()) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

        // use  Ipp64f
        std::vector<Ipp64f> signal1_64f = {1.0, 2.0, 3.0, 4.0};
        std::vector<Ipp64f> signal2_64f = {0.5, 0.5};
        convolver.setSignals(signal1_64f, signal2_64f, SignalConvolver::Float64);
        convolver.convolve();

        std::cout << "Convolution Result (64f):" << std::endl;
        for (auto val : convolver.getResult64f()) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return -1;
    }






    return 0;
}





