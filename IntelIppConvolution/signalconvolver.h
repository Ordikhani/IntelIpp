#ifndef SIGNAL_CONVOLVER_H
#define SIGNAL_CONVOLVER_H

#include <vector>
#include <ipp.h>
#include <stdexcept>
#include <string>
/*
 *
 *
Complete class for convolution of signals with full functionality taken from the library intelipps:
Library intelipp 2021.12  : section : Convolution functions,
Author : Fateme Ordikhani  - FaOrdi
Data : 1403 -09 -02    2024 - 11 - 21

 ============================================================================
 SignalConvolver Class
 ============================================================================

 This class provides a set of functions for performing signal convolution
 using the Intel IPP (Integrated Performance Primitives) library. It supports
 both 32-bit and 64-bit floating-point data types and offers various types of
 convolutions (e.g., "same", "valid", "full") for the input signals.

 The class has methods to:
  - Allocate necessary buffers for convolution operations.
  - Set the input signals (in both 32-bit and 64-bit floating point formats).
  - Perform the convolution with or without bias.
  - Return the result of the convolution for both data types (32-bit and 64-bit).

 Dependencies:
  - Intel IPP Library: The methods use IPP functions like ippsConvolve_32f,
    ippsConvolve_64f, etc., for performing the convolution operations.

 Methods and Usage:
  1. `allocateBuffer`:
      - Allocates memory for the internal buffer required by the convolution functions.
  2. `setSignals`:
      - Sets the input signals (both signal vectors for convolution) and allocates
        memory for the result based on the signal lengths.
  3. `convolve`:
      - Performs a standard convolution of the two input signals (full convolution).
  4. `convolveWithBias`:
      - Performs convolution with an additional bias parameter.
  5. `convolvesame`:
      - Performs a "same" convolution, where the result is truncated to the size
        of the first signal.
  6. `convolvevalid`:
      - Performs a "valid" convolution, where the result only includes values
        that do not rely on zero-padding.
  7. `convolvefull`:
      - Performs a "full" convolution, where the result includes all values
        from both signals, with zero-padding as necessary.

 Error Handling:
  - Methods throw `std::runtime_error` if there are any issues during the
    convolution operation or if invalid data types are encountered.
  - The `setSignals` method checks that the data type matches the type of the signals.
  - The `convolveWithBias` method only supports 32-bit floating-point signals.

 Example Usage:
  1. Create an instance of the SignalConvolver class.
  2. Set signals using `setSignals` (for either 32f or 64f types).
  3. Call the desired convolution method (e.g., `convolve`, `convolvesame`, etc.)
  4. Retrieve the result using `getResult32f` or `getResult64f` based on the data type.

 ============================================================================

*/
class SignalConvolver {
public:
    enum DataType {
        Float32,
        Float64
    };

    //
    SignalConvolver();
    ~SignalConvolver();

    //
    void setSignals(const std::vector<Ipp32f>& sig1, const std::vector<Ipp32f>& sig2, DataType type = Float32);
    void setSignals(const std::vector<Ipp64f>& sig1, const std::vector<Ipp64f>& sig2, DataType type = Float64);

    void convolve();
    void convolveWithBias(int bias);
    void convolvesame(bool useSameSize = false);
    void convolvevalid();
    void convolvefull();
    const std::vector<Ipp32f>& getResult32f() const;
    const std::vector<Ipp64f>& getResult64f() const;

private:
    // private data :
    std::vector<Ipp32f> signal1_32f, signal2_32f, result_32f;
    std::vector<Ipp64f> signal1_64f, signal2_64f, result_64f;

    Ipp8u* buffer;
    int bufferSize;
    DataType dataType;

    void allocateBuffer(int src1Len, int src2Len, IppDataType ipType, IppEnum algType);
};

#endif // SIGNAL_CONVOLVER_H
