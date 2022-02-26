#include "CircularBuffer.h"
#include <ctime>
#include <unistd.h>
#include <vector>
#include <math.h>

/** 
 * @brief Template for the EncoderReader.
 * 
 * @tparam T type for the values read from the encoder
 * @tparam Size of the circular buffer to store the encoder values
 * 
 */ 
template<class T, std::size_t Size>
class EncoderReader {
  public:
    /**
     * @brief EncoderReader Generic Exception class
     */
    class EncoderReaderException : public std::runtime_error
    {
    public:
        /**
         * @brief EncoderReaderException constructor.
         *
         * @param[in] what string whit the message to show when throwing
         * the exception.
         */
        EncoderReaderException(const std::string& what)
            : std::runtime_error(what)
        {
        }
    };

    /**
     * @brief EncoderReader constructor.
     *
     */
    EncoderReader()
    {
    }

    /**
     * @brief helper function to get the oldest encoder raw values from the
     * buffer.
     *
     * @return value raw encoder measurements (in absolute ticks).
     * 
     * @note can be extended to return also the timestamp
     * 
     */
    T readValue(){
        return _encoderValues.pop();
    };

    /**
     * @brief helper function to write encoder raw values into the buffer.
     *
     * @param[in] value raw encoder measurements (in absolute ticks).
     * 
     */
    void writeValue(T value){
        _encoderValues.push(value);
        _encoderTimes.push(std::time(nullptr));
    };

    /**
     * @brief get the current velocity using the centered finite difference
     * approach. For this method we neeed at least 3 measurements.
     *
     * @return current velocity in rad/s.
     * 
     * @throw EncoderReaderException if there are not enough values to calculate
     * the velocity
     * 
     */
    float getVelocity(){
        std::vector<T> enc_val;
        std::vector<time_t> enc_t;
        if (!_encoderValues.getElements(enc_val,3) || 
            !_encoderTimes.getElements(enc_t,3)) {
            throw(EncoderReaderException(
                "Not enough elements to estimate velocity"));
        }
        T pos_diff = enc_val[0] - enc_val[2];
        float t_diff = enc_t[0] - enc_t[2];
        return ((pos_diff*ticksToRad)/t_diff);
    };

    /**
     * @brief get the current acceleration using the centered finite difference
     * approach. For this method we neeed at least 3 measurements.
     *
     * @return current velocity in rad/s².
     * 
     * @throw EncoderReaderException if there are not enough values to calculate
     * the acceleration
     * 
     */
    float getAcceleration(){
        std::vector<T> enc_val;
        std::vector<time_t> enc_t;
        if (!_encoderValues.getElements(enc_val,3) || 
            !_encoderTimes.getElements(enc_t,3)) {
            throw(EncoderReaderException(
                "Not enough elements to estimate acceleration"));
        }

        T pos_diff = enc_val[0] -2*enc_val[1] + enc_val[2];
        if (pos_diff == 0) {
            return 0;
        }

        float t_diff = (enc_t[0] - enc_t[2]);

        return (pos_diff*ticksToRad)/(t_diff*t_diff);

    };
  private:
    /**
     * @brief The CircularBuffer for encoder raw measurements
     *
     */
    CircularBuffer<T,Size> _encoderValues;

    /**
     * @brief The CircularBuffer for encoder measurement timestamps
     *
     */
    CircularBuffer<time_t,Size> _encoderTimes;

    /**
     * @brief The encoder resolution (in ticks, 4096 = 360[º] 2*pi[rad])
     *
     */
    uint encoderResolution = 4096;
    float ticksToRad = (2*M_PI)/encoderResolution;
};
