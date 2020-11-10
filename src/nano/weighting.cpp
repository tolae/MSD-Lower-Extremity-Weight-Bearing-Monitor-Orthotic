#include "inc/weighting.h"
#include "inc/convolution.h"

#define CONNECTIONS_READING_ANALOG_PIN
#define EXT_ANALOG_PER_CONNECTION 205

#define BASE_SENSOR_ID_MAX 8
#define ONE_EXT_SENSOR_ID_MAX 12
#define TWO_EXT_SENSOR_ID_MAX 16
#define THREE_SENSOR_ID_MAX 20

#define SENSOR_MAX 20
#define SENSOR_HISTORY 16
#define SENSORS_PER_EXT 4

#define MAX_AVERAGE_CNT 4

typedef enum CONNECTED_SENSORS
{
    NO_EXT = 0,
    ONE_EXT,
    TWO_EXT,
    THREE_EXT
} connections_t;

/** Array of sensor readings
 * 
 * The first array corresponds to the individual 20 sensors.
 * The second array corresponds to the history for that particular sensor.
 */
uint16_t sensor_weights[SENSOR_MAX][SENSOR_HISTORY];
uint8_t sensor_weights_curr_index = 0;

/* Global variable that holds the number of connections */
connections_t connections = NO_EXT;

/* Updates the connections variable with the current number of attached exts */
void _check_connection();

/* Updates the particular sensor */
void _update_sensor(uint8_t sensor);

/* Computes a single reading and returns a weight calculation */
uint16_t update_weights()
{
    uint8_t i;
    uint8_t j;
    uint8_t k;
    uint32_t average;
    uint32_t max_averages[MAX_AVERAGE_CNT] = {0};
    _check_connection();

    /** The base pad has 8 connections (read at twice the speed), with each ext
     * adding 4 sensors.
     */
    for (i = 0; i < BASE_SENSOR_ID_MAX + connections * SENSORS_PER_EXT; i++)
    {
        _update_sensor(i);

        /* With the updated sensor, average out the last 16 readings. */
        for (j = 0; j < SENSOR_HISTORY; j++)
        {
            average += sensor_weights[i][j];
        }
        average = average >> 4; // div by 16
        
        /* Store all the max averages */
        for (k = 0; k < MAX_AVERAGE_CNT; k++)
        {
            if (max_averages[k] < average)
            {
                max_averages[k] = average;
            }
        }
    }
    sensor_weights_curr_index++;

    /* Compute the final average */
    average = 0;
    for (k = 0; k < MAX_AVERAGE_CNT; k++)
    {
        average += max_averages[k];
    }
    average = average >> 2; // div by 4

    return average;
}

void _check_connections()
{
    uint16_t divider = analogRead(CONNECTIONS_READING_ANALOG_PIN);
    if (divider > EXT_ANALOG_PER_CONNECTION*4)
    {
        /* 4 extentions */
    }
    else if (divider > EXT_ANALOG_PER_CONNECTION*3)
    {
        connections = THREE_EXT;
    }
    else if (divider > EXT_ANALOG_PER_CONNECTION*2)
    {
        connections = TWO_EXT;
    }
    else if (divider > EXT_ANALOG_PER_CONNECTION)
    {
        connections = ONE_EXT;
    }
    else
    {
        connections = NO_EXT;
    }
}

void _update_sensor(uint8_t sensor)
{
    if (sensor < BASE_SENSOR_ID_MAX)
    {
        /** The base pad reads two sensors at a time. The pairs of sensors will
         * be next to each other in the array.
         * 
         * Set the mux for the given pair of sensors and read them.
         */
    }
    else
    {
        /** The extention pads are read one at a time.
         * 
         * Set the mux for the given sensor and read them.
         */
    }
}
