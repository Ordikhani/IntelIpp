#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <vector>
#include <string>

class Convolution {
public:
    Convolution();
    ~Convolution();

    // کانولوشن با انتخاب نوع padding
    std::vector<float> convolve(const std::vector<float>& signal,
                                const std::vector<float>& kernel,
                                const std::string& paddingType);

private:
    // اعمال padding به سیگنال
    std::vector<float> applyPadding(const std::vector<float>& signal, int kernelSize);

    // اجرای کانولوشن
    std::vector<float> performConvolution(const std::vector<float>& signal, const std::vector<float>& kernel);
};

#endif // CONVOLUTION_H
