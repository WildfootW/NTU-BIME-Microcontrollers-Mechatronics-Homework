/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#ifndef SENSORS_H
#define SENSORS_H

class BasicSensor
{
public:
    BasicSensor(byte pin): pin(pin) {}
    void initial(uint16_t divide, bool less_than = false) { pinMode(pin, INPUT); divide_value = divide; value_less_than = less_than; }
    void value_update()
    {
        unsigned int new_value = (mix_value * 9) + analogRead(pin);
        mix_value = new_value / 10;
#ifndef NDEBUG
        Serial.print(mix_value);
#endif // NDEBUG
        bool new_status = ( mix_value > divide_value );
        if(value_less_than) new_status = !new_status;
        if(new_status != current_status)
        {
            last_change_status_time = millis();
            current_status = new_status;
        }
#ifndef NDEBUG
        Serial.print(" ");
        Serial.println(current_status);
#endif // NDEBUG
    }
    bool target_detected() const { return current_status; }
    unsigned long get_last_change_status_time() const { return last_change_status_time; }
protected:
    bool current_status;
    bool value_less_than;
    const byte pin;
    uint16_t divide_value;
    uint16_t mix_value;
    unsigned long last_change_status_time;
};
class IrSensorTCRT5000: public BasicSensor
{
public:
    IrSensorTCRT5000(byte pin): BasicSensor(pin) {}
    void value_update()
    {
#ifndef NDEBUG
        Serial.print(" IR :");
#endif // NDEBUG
        BasicSensor::value_update();
    }
};
class IrSensor2Y0A21: public BasicSensor
{
public:
    IrSensorSHARP(byte pin): SharpIR(GP2Y0A21YK0F, pin) {}
    void initial() { pinMode(pin, INPUT); }
    uint8_t get_distance() { return getDistance(); }
};

#endif //SENSORS_H
