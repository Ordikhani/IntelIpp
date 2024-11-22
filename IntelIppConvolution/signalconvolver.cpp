


#include "signalconvolver.h"
#include <iostream>
#include <stdexcept>

SignalConvolver::SignalConvolver() : buffer(nullptr), bufferSize(0), dataType(Float32) {}

SignalConvolver::~SignalConvolver() {
    if (buffer) {
        ippsFree(buffer);
    }
}

void SignalConvolver::allocateBuffer(int src1Len, int src2Len, IppDataType ipType, IppEnum algType) {
    IppStatus status = ippsConvolveGetBufferSize(src1Len, src2Len, ipType, algType, &bufferSize);
    if (status != ippStsNoErr) {
        throw std::runtime_error("Error in ippsConvolveGetBufferSize: " + std::to_string(status));
    }

    if (buffer) {
        ippsFree(buffer);
    }
    buffer = ippsMalloc_8u(bufferSize);
}

void SignalConvolver::setSignals(const std::vector<Ipp32f>& sig1, const std::vector<Ipp32f>& sig2, DataType type) {
    if (type != Float32) throw std::invalid_argument("Invalid data type for Ipp32f signals.");

    signal1_32f = sig1;
    signal2_32f = sig2;
    result_32f.resize(signal1_32f.size() + signal2_32f.size() - 1, 0);
    dataType = Float32;

    allocateBuffer(static_cast<int>(signal1_32f.size()), static_cast<int>(signal2_32f.size()), ipp32f, ippAlgAuto);
}

void SignalConvolver::setSignals(const std::vector<Ipp64f>& sig1, const std::vector<Ipp64f>& sig2, DataType type) {
    if (type != Float64) throw std::invalid_argument("Invalid data type for Ipp64f signals.");

    signal1_64f = sig1;
    signal2_64f = sig2;
    result_64f.resize(signal1_64f.size() + signal2_64f.size() - 1, 0);
    dataType = Float64;

    allocateBuffer(static_cast<int>(signal1_64f.size()), static_cast<int>(signal2_64f.size()), ipp64f, ippAlgAuto);
}

void SignalConvolver::convolve() {
    if (dataType == Float32) {
        IppStatus status = ippsConvolve_32f(signal1_32f.data(), static_cast<int>(signal1_32f.size()),
                                            signal2_32f.data(), static_cast<int>(signal2_32f.size()),
                                            result_32f.data(), ippAlgAuto, buffer);
        if (status != ippStsNoErr) {
            throw std::runtime_error("Error in ippsConvolve_32f: " + std::to_string(status));
        }
    } else if (dataType == Float64) {
        IppStatus status = ippsConvolve_64f(signal1_64f.data(), static_cast<int>(signal1_64f.size()),
                                            signal2_64f.data(), static_cast<int>(signal2_64f.size()),
                                            result_64f.data(), ippAlgAuto, buffer);
        if (status != ippStsNoErr) {
            throw std::runtime_error("Error in ippsConvolve_64f: " + std::to_string(status));
        }
    } else {
        throw std::runtime_error("Invalid data type.");
    }
}

void SignalConvolver::convolveWithBias(int bias) {
    if (dataType == Float32) {
        int dstLen = static_cast<int>(result_32f.size());
        IppStatus status = ippsConvBiased_32f(signal1_32f.data(), static_cast<int>(signal1_32f.size()),
                                              signal2_32f.data(), static_cast<int>(signal2_32f.size()),
                                              result_32f.data(), dstLen, bias);
        if (status != ippStsNoErr) {
            throw std::runtime_error("Error in ippsConvBiased_32f: " + std::to_string(status));
        }
    } else {
        throw std::runtime_error("ippsConvBiased_32f supports only Float32 data type.");
    }
}

const std::vector<Ipp32f>& SignalConvolver::getResult32f() const {
    if (dataType != Float32) throw std::runtime_error("Result is not of type Float32.");
    return result_32f;
}

const std::vector<Ipp64f>& SignalConvolver::getResult64f() const {
    if (dataType != Float64) throw std::runtime_error("Result is not of type Float64.");
    return result_64f;
}

//conv "same"
void SignalConvolver::convolvesame(bool useSameSize) {
    if (dataType == Float32) {
        IppStatus status = ippsConvolve_32f(signal1_32f.data(), static_cast<int>(signal1_32f.size()),
                                            signal2_32f.data(), static_cast<int>(signal2_32f.size()),
                                            result_32f.data(), ippAlgAuto, buffer);
        if (status != ippStsNoErr) {
            throw std::runtime_error("Error in ippsConvolve_32f: " + std::to_string(status));
        }

        if (useSameSize) {
            int extra = static_cast<int>(result_32f.size() - signal1_32f.size());
            int start = extra / 2;
            result_32f = std::vector<Ipp32f>(result_32f.begin() + start, result_32f.begin() + start + signal1_32f.size());
        }
    } else if (dataType == Float64) {
        IppStatus status = ippsConvolve_64f(signal1_64f.data(), static_cast<int>(signal1_64f.size()),
                                            signal2_64f.data(), static_cast<int>(signal2_64f.size()),
                                            result_64f.data(), ippAlgAuto, buffer);
        if (status != ippStsNoErr) {
            throw std::runtime_error("Error in ippsConvolve_64f: " + std::to_string(status));
        }

        if (useSameSize) {
            int extra = static_cast<int>(result_64f.size() - signal1_64f.size());
            int start = extra / 2;
            result_64f = std::vector<Ipp64f>(result_64f.begin() + start, result_64f.begin() + start + signal1_64f.size());
        }
    } else {
        throw std::runtime_error("Invalid data type.");
    }
}

// conv "valid"
void SignalConvolver::convolvevalid() {
    if (dataType == Float32) {
        int validLen = static_cast<int>(signal1_32f.size() - signal2_32f.size() + 1);
        result_32f.resize(validLen, 0);

        IppStatus status = ippsConvolve_32f(signal1_32f.data(), static_cast<int>(signal1_32f.size()),
                                            signal2_32f.data(), static_cast<int>(signal2_32f.size()),
                                            result_32f.data(), ippAlgAuto, buffer);
        if (status != ippStsNoErr) {
            throw std::runtime_error("Error in ippsConvolve_32f: " + std::to_string(status));
        }
    } else if (dataType == Float64) {
        int validLen = static_cast<int>(signal1_64f.size() - signal2_64f.size() + 1);
        result_64f.resize(validLen, 0);

        IppStatus status = ippsConvolve_64f(signal1_64f.data(), static_cast<int>(signal1_64f.size()),
                                            signal2_64f.data(), static_cast<int>(signal2_64f.size()),
                                            result_64f.data(), ippAlgAuto, buffer);
        if (status != ippStsNoErr) {
            throw std::runtime_error("Error in ippsConvolve_64f: " + std::to_string(status));
        }
    } else {
        throw std::runtime_error("Invalid data type.");
    }
}

// conv "full"
void SignalConvolver::convolvefull() {
    if (dataType == Float32) {
        int fullLen = static_cast<int>(signal1_32f.size() + signal2_32f.size() - 1);
        result_32f.resize(fullLen, 0);

        IppStatus status = ippsConvolve_32f(signal1_32f.data(), static_cast<int>(signal1_32f.size()),
                                            signal2_32f.data(), static_cast<int>(signal2_32f.size()),
                                            result_32f.data(), ippAlgAuto, buffer);
        if (status != ippStsNoErr) {
            throw std::runtime_error("Error in ippsConvolve_32f: " + std::to_string(status));
        }
    } else if (dataType == Float64) {
        int fullLen = static_cast<int>(signal1_64f.size() + signal2_64f.size() - 1);
        result_64f.resize(fullLen, 0);

        IppStatus status = ippsConvolve_64f(signal1_64f.data(), static_cast<int>(signal1_64f.size()),
                                            signal2_64f.data(), static_cast<int>(signal2_64f.size()),
                                            result_64f.data(), ippAlgAuto, buffer);
        if (status != ippStsNoErr) {
            throw std::runtime_error("Error in ippsConvolve_64f: " + std::to_string(status));
        }
    } else {
        throw std::runtime_error("Invalid data type.");
    }
}





//#include "signalconvolver.h"

//SignalConvolver::SignalConvolver() : buffer(nullptr), bufferSize(0), dataType(Float32) {}

//SignalConvolver::~SignalConvolver() {
//    if (buffer) {
//        ippsFree(buffer);
//    }
//}

//void SignalConvolver::allocateBuffer(int src1Len, int src2Len, IppDataType ipType, IppEnum algType) {
//    IppStatus status = ippsConvolveGetBufferSize(src1Len, src2Len, ipType, algType, &bufferSize);
//    if (status != ippStsNoErr) {
//        throw std::runtime_error("Error in ippsConvolveGetBufferSize: " + std::to_string(status));
//    }

//    if (buffer) {
//        ippsFree(buffer);
//    }
//    buffer = ippsMalloc_8u(bufferSize);
//}

//void SignalConvolver::setSignals(const std::vector<Ipp32f>& sig1, const std::vector<Ipp32f>& sig2, DataType type) {
//    if (type != Float32) throw std::invalid_argument("Invalid data type for Ipp32f signals.");

//    signal1_32f = sig1;
//    signal2_32f = sig2;
//    result_32f.resize(signal1_32f.size() + signal2_32f.size() - 1, 0);
//    dataType = Float32;

//    allocateBuffer(static_cast<int>(signal1_32f.size()), static_cast<int>(signal2_32f.size()), ipp32f, ippAlgAuto);
//}

//void SignalConvolver::setSignals(const std::vector<Ipp64f>& sig1, const std::vector<Ipp64f>& sig2, DataType type) {
//    if (type != Float64) throw std::invalid_argument("Invalid data type for Ipp64f signals.");

//    signal1_64f = sig1;
//    signal2_64f = sig2;
//    result_64f.resize(signal1_64f.size() + signal2_64f.size() - 1, 0);
//    dataType = Float64;

//    allocateBuffer(static_cast<int>(signal1_64f.size()), static_cast<int>(signal2_64f.size()), ipp64f, ippAlgAuto);
//}

//void SignalConvolver::convolve() {
//    if (dataType == Float32) {
//        IppStatus status = ippsConvolve_32f(signal1_32f.data(), static_cast<int>(signal1_32f.size()),
//                                            signal2_32f.data(), static_cast<int>(signal2_32f.size()),
//                                            result_32f.data(), ippAlgAuto, buffer);
//        if (status != ippStsNoErr) {
//            throw std::runtime_error("Error in ippsConvolve_32f: " + std::to_string(status));
//        }
//    } else if (dataType == Float64) {
//        IppStatus status = ippsConvolve_64f(signal1_64f.data(), static_cast<int>(signal1_64f.size()),
//                                            signal2_64f.data(), static_cast<int>(signal2_64f.size()),
//                                            result_64f.data(), ippAlgAuto, buffer);
//        if (status != ippStsNoErr) {
//            throw std::runtime_error("Error in ippsConvolve_64f: " + std::to_string(status));
//        }
//    } else {
//        throw std::runtime_error("Invalid data type.");
//    }
//}

//void SignalConvolver::convolveWithBias(int bias) {
//    if (dataType == Float32) {
//        int dstLen = static_cast<int>(result_32f.size());
//        IppStatus status = ippsConvBiased_32f(signal1_32f.data(), static_cast<int>(signal1_32f.size()),
//                                              signal2_32f.data(), static_cast<int>(signal2_32f.size()),
//                                              result_32f.data(), dstLen, bias);
//        if (status != ippStsNoErr) {
//            throw std::runtime_error("Error in ippsConvBiased_32f: " + std::to_string(status));
//        }
//    } else {
//        throw std::runtime_error("ippsConvBiased_32f supports only Float32 data type.");
//    }
//}

//const std::vector<Ipp32f>& SignalConvolver::getResult32f() const {
//    if (dataType != Float32) throw std::runtime_error("Result is not of type Float32.");
//    return result_32f;
//}

//const std::vector<Ipp64f>& SignalConvolver::getResult64f() const {
//    if (dataType != Float64) throw std::runtime_error("Result is not of type Float64.");
//    return result_64f;
//}



//void SignalConvolver::convolvesame(bool useSameSize) {
//    if (dataType == Float32) {
//        IppStatus status = ippsConvolve_32f(signal1_32f.data(), static_cast<int>(signal1_32f.size()),
//                                            signal2_32f.data(), static_cast<int>(signal2_32f.size()),
//                                            result_32f.data(), ippAlgAuto, buffer);
//        if (status != ippStsNoErr) {
//            throw std::runtime_error("Error in ippsConvolve_32f: " + std::to_string(status));
//        }

//        if (useSameSize) {
//            int extra = static_cast<int>(result_32f.size() - signal1_32f.size());
//            int start = extra / 2;
//            result_32f = std::vector<Ipp32f>(result_32f.begin() + start, result_32f.begin() + start + signal1_32f.size());
//        }

//    } else if (dataType == Float64) {
//        IppStatus status = ippsConvolve_64f(signal1_64f.data(), static_cast<int>(signal1_64f.size()),
//                                            signal2_64f.data(), static_cast<int>(signal2_64f.size()),
//                                            result_64f.data(), ippAlgAuto, buffer);
//        if (status != ippStsNoErr) {
//            throw std::runtime_error("Error in ippsConvolve_64f: " + std::to_string(status));
//        }

//        if (useSameSize) {
//            int extra = static_cast<int>(result_64f.size() - signal1_64f.size());
//            int start = extra / 2;
//            result_64f = std::vector<Ipp64f>(result_64f.begin() + start, result_64f.begin() + start + signal1_64f.size());
//        }
//    } else {
//        throw std::runtime_error("Invalid data type.");
//    }
//}

