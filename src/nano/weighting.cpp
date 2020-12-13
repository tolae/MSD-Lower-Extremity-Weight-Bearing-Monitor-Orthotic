#include "inc/weighting.h"
#include "inc/convolution.h"

/** Defines **/

/* Defines for extender board connection logic */
#define CONNECTIONS_READING_ANALOG_PIN A0
#define EXT_ANALOG_PER_CONNECTION 205
/***********************************************/

/* Defines for sensor ids and sensor count logic */
#define BASE_SENSOR_ID_MAX 2 // Modified from 8 as we only have 2 sensors for demo.
#define ONE_EXT_SENSOR_ID_MAX 12
#define TWO_EXT_SENSOR_ID_MAX 16
#define THREE_EXT_SENSOR_ID_MAX 20

#define SENSOR_MAX 20
#define SENSOR_HISTORY 16
#define SENSORS_PER_EXT 4
/*************************************************/

/* Defines for sensor pin locations */
/* Analog Pins */
#define MUXA_OPA_ANALOG_PIN A7
#define MUXA_OPB_ANALOG_PIN A6
#define EXT1_ANALOG_PIN A5
#define EXT2_ANALOG_PIN A4
#define EXT3_ANALOG_PIN A3

/* Digital Pins */
#define MUXA_SELECT0 2
#define MUXA_SELECT1 3

#define MUXA_SELECT0_MASK 0x01
#define MUXA_SELECT1_MASK 0x02
/*************************************************/

/* Defines for sensor data logic */
#define MAX_AVERAGE_CNT 1 // Modified from 4 as we only have 2 sensors for demo.
/*********************************/

/* Enumeration for how many connector boards are attached (and supported) */
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
void _check_connections();

/* Updates the particular sensor */
void _update_sensor(uint8_t sensor);

/** Computes a single reading and returns a weight calculation.
 * 
 * Needs to be ran SENSOR_HISTORY times before valid/useful values come out.
*/
uint16_t update_weights()
{
    uint8_t i;
    uint8_t j;
    uint8_t k;
    uint32_t average;
    uint32_t max_averages[MAX_AVERAGE_CNT] = {0};
    /* Current unused for demo purposes */
    // _check_connections();

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
        average /= SENSOR_HISTORY;
        
        /* Store all the max averages */
        for (k = 0; k < MAX_AVERAGE_CNT; k++)
        {
            if (max_averages[k] < average)
            {
                max_averages[k] = average;
            }
        }
    }
    sensor_weights_curr_index = (++sensor_weights_curr_index) % SENSOR_HISTORY;

    /* Compute the final average */
    average = 0;
    for (k = 0; k < MAX_AVERAGE_CNT; k++)
    {
        average += max_averages[k];
    }
    average /= MAX_AVERAGE_CNT;

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
    uint8_t mux_sel;
    if (sensor < BASE_SENSOR_ID_MAX)
    {
        /** The base pad reads two sensors at a time. The pairs of sensors will
         * be next to each other in the array.
         * 
         * Set the mux for the given pair of sensors and read them.
         */
        /** No longer used as demo circuit doesn't have multiplexers **/
        /* Sensors come in pairs */
        // mux_sel = sensor / 2;
        // digitalWrite(MUXA_SELECT0, mux_sel & MUXA_SELECT0_MASK);
        // digitalWrite(MUXA_SELECT1, mux_sel & MUXA_SELECT1_MASK);
        /* Allow muxs to stabilize the signal */
        // delay(1);

        if (sensor % 2)
        {
            sensor_weights[sensor][sensor_weights_curr_index] = analogRead(MUXA_OPA_ANALOG_PIN);
        }
        else
        {
            sensor_weights[sensor][sensor_weights_curr_index] = analogRead(MUXA_OPB_ANALOG_PIN);
        }
    }
    else
    {
        /** The extention pads are read one at a time.
         * 
         * Set the mux for the given sensor and read them.
         */
        mux_sel = sensor % SENSORS_PER_EXT;
        digitalWrite(MUXA_SELECT0, mux_sel & MUXA_SELECT0_MASK);
        digitalWrite(MUXA_SELECT1, mux_sel & MUXA_SELECT1_MASK);
        delay(1); // Allow muxs to stabilize the signal

        if (sensor < ONE_EXT_SENSOR_ID_MAX)
        {
            sensor_weights[sensor][sensor_weights_curr_index] = analogRead(EXT1_ANALOG_PIN);
        }
        else if (sensor < TWO_EXT_SENSOR_ID_MAX)
        {
            sensor_weights[sensor][sensor_weights_curr_index] = analogRead(EXT2_ANALOG_PIN);
        }
        else if (sensor < THREE_EXT_SENSOR_ID_MAX)
        {
            sensor_weights[sensor][sensor_weights_curr_index] = analogRead(EXT3_ANALOG_PIN);
        }
    }
}
