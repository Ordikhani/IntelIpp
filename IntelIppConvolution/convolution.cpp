#include "convolution.h"
#include <ippcore.h>
#include <ipps.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>

Convolution::Convolution() {}

Convolution::~Convolution() {}

std::vector<float> Convolution::convolve(const std::vector<float>& signal,
                                         const std::vector<float>& kernel,
                                         const std::string& paddingType) {
    if (paddingType != "same" && paddingType != "valid") {
        throw std::invalid_argument("Unsupported padding type. Use 'same' or 'valid'.");
    }

    // اعمال padding در صورت نیاز
    std::vector<float> paddedSignal = signal;
    if (paddingType == "same") {
        paddedSignal = applyPadding(signal, static_cast<int>(kernel.size()));
    }

    // اجرای کانولوشن
    return performConvolution(paddedSignal, kernel);
}

std::vector<float> Convolution::applyPadding(const std::vector<float>& signal, int kernelSize) {
    int padSize = (kernelSize - 1) / 2; // اندازه پدینگ
    std::vector<float> paddedSignal(signal.size() + 2 * padSize, 0.0f);

    // کپی سیگنال اصلی به مرکز سیگنال پد شده
    std::copy(signal.begin(), signal.end(), paddedSignal.begin() + padSize);

    return paddedSignal;
}

std::vector<float> Convolution::performConvolution(const std::vector<float>& signal, const std::vector<float>& kernel) {
    int signalSize = static_cast<int>(signal.size());
    int kernelSize = static_cast<int>(kernel.size());
    int outputSize = signalSize + kernelSize - 1; // اندازه خروجی کانولوشن کامل

    if (kernelSize > signalSize) {
        throw std::invalid_argument("Kernel size must be smaller than or equal to the signal size.");
    }

    std::vector<float> output(outputSize, 0.0f);

    // گرفتن اندازه بافر مورد نیاز
    int bufferSize = 0;
    IppStatus status = ippsConvolveGetBufferSize(signalSize, kernelSize, ipp32f, 1, &bufferSize);
    if (status != ippStsNoErr) {
        throw std::runtime_error("Failed to get buffer size: " + std::string(ippGetStatusString(status)));
    }

    // تخصیص بافر
    std::vector<Ipp8u> buffer(bufferSize);

    // اجرای کانولوشن
    status = ippsConvolve_32f(
        signal.data(), signalSize,           // سیگنال ورودی و طول آن
        kernel.data(), kernelSize,           // کرنل و طول آن
        output.data(), outputSize,           // خروجی و اندازه آن
        buffer.data()                        // بافر کاری
    );

    if (status != ippStsNoErr) {
        throw std::runtime_error("IPP convolution failed: " + std::string(ippGetStatusString(status)));
    }

    return output;
}
