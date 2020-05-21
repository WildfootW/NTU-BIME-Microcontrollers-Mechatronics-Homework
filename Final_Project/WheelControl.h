/*
 * Version
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2019-2020 WildfootW all rights reversed
 *
 */

#ifndef WHEELCONTROL_H
#define WHEELCONTROL_H
/*
 * class design for Arduino uno & L298 H-bridge controling two DC motor wheels.
 */
class SingleWheelControl
{
public:
    SingleWheelControl(byte pin_a, byte pin_b, byte pin_en): pin_a(pin_a), pin_b(pin_b), pin_en(pin_en) {} // digital, digital, pwm
    void initial(double ratio = 1) { pinMode(pin_a, OUTPUT); pinMode(pin_b, OUTPUT); pinMode(pin_en, OUTPUT); output_ratio = ratio; }
    void set_speed(uint8_t speed, bool backward = false) { forward = !backward; current_speed = speed * output_ratio; }
    void execute() const
    {
#ifndef NDEBUG
        Serial.println(current_speed);
#endif // NDEBUG
        analogWrite(pin_en, current_speed);
        if(forward) { digitalWrite(pin_a, HIGH); digitalWrite(pin_b, LOW ); }
        else        { digitalWrite(pin_a, LOW ); digitalWrite(pin_b, HIGH); }
    }
private:
    const byte pin_a, pin_b;
    const byte pin_en;
    bool forward;
    uint8_t current_speed;
    double output_ratio;
};

class WheelControl
{
public:
    WheelControl(byte pin_a_llleft, byte pin_b_llleft, byte pin_en_llleft,      // digital, digital, pwm
                     byte pin_a_rright, byte pin_b_rright, byte pin_en_rright):    // digital, digital, pwm
                     llleft_wheel(pin_a_llleft, pin_b_llleft, pin_en_llleft),
                     rright_wheel(pin_a_rright, pin_b_rright, pin_en_rright) {}
    void initial(double speed_ratio = 1)    // speed_ratio = llleft_speed / rright_speed;
    {
        global_ratio = 1;
        if(speed_ratio > 1) { llleft_wheel.initial(1 / speed_ratio); rright_wheel.initial(1);           }
        else                { llleft_wheel.initial(1);               rright_wheel.initial(speed_ratio); }
    }
    void set_speed(uint8_t llleft_speed, uint8_t rright_speed, bool llleft_backward = false, bool rright_backward = false) const
    {
        llleft_wheel.set_speed(llleft_speed * global_ratio, llleft_backward);
        rright_wheel.set_speed(rright_speed * global_ratio, rright_backward);
    }
    WheelControl& set_global_ratio(double ratio) { global_ratio = ratio ; return (*this); }
    WheelControl& keep(unsigned int time) { delay(time); return (*this); }

    WheelControl& go(uint8_t speed_amount, bool backward = false)
    {
        if(!backward) { set_speed(speed_amount, speed_amount); }
        else          { set_speed(speed_amount, speed_amount, true, true); }
        execute(); return (*this);
    }
    WheelControl& rotate(uint8_t speed_amount, bool clockwise = false)
    {
        if(clockwise) set_speed(speed_amount, speed_amount, false, true);
        else          set_speed(speed_amount, speed_amount, true, false);
        execute(); return (*this);
    }
    WheelControl& turn(int8_t steer_amount)
    {
        if(steer_amount == 0) set_speed(255, 255);
        if(steer_amount >  0) set_speed(255 - (steer_amount * 2), 255);
        if(steer_amount <  0) set_speed(255, 255 + (steer_amount * 2));
        execute(); return (*this);
    }

private:
    SingleWheelControl llleft_wheel, rright_wheel;
    double global_ratio;
    void execute() const
    {
#ifndef NDEBUG
        Serial.print("llleft: ");
#endif // NDEBUG
        llleft_wheel.execute();
#ifndef NDEBUG
        Serial.print("rright: ");
#endif // NDEBUG
        rright_wheel.execute();
    }
};
#endif //WHEELCONTROL_H

