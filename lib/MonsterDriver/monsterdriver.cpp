#include <mbed.h>
#include "monsterdriver.hpp"

bra::MonsterDriver::MonsterDriver(  PinName p_motorEnablePin, PinName p_motorPwmPin, 
                                    PinName p_motorDirPin_A, PinName p_motorDirPin_B){
    
    m_motorEnablePin = new DigitalOut(p_motorEnablePin, bra::MonsterDriver::LOW);  // INA: Clockwise input
    m_motorDirPin_A = new DigitalOut(p_motorDirPin_A, bra::MonsterDriver::LOW);    // INB: Counter-clockwise input
    m_motorDirPin_B = new DigitalOut(p_motorDirPin_B, bra::MonsterDriver::LOW);    // EN: Status of switches output 
    
    m_motorEnablePin->write(1);
    
    m_motorPwmPin = new PwmOut(p_motorPwmPin);   // PWM Pin
    m_motorPwmPin->period_us(this->m_pwmPeriod);                // PWM Frequency [20kHz]
    m_motorPwmPin->write(this->m_pwmValue);                  // PWM Initial Output [0%]

}

bra::MonsterDriver::~MonsterDriver(){
    m_motorEnablePin->write(bra::MonsterDriver::LOW);
    m_motorDirPin_A->write(bra::MonsterDriver::LOW);
    m_motorDirPin_B->write(bra::MonsterDriver::LOW);
    this->setPWM(0.0f);

    delete m_motorEnablePin;
    delete m_motorDirPin_A;
    delete m_motorDirPin_B;
    delete m_motorPwmPin;
}

void bra::MonsterDriver::setPWM(float p_pwmValue){
    float pwm;
    
    if(p_pwmValue <= 1.0 && p_pwmValue >= -1.0){
        pwm = p_pwmValue;
    } else if(p_pwmValue > 1.0) {
        pwm = 1.0;
    } else if(p_pwmValue < -1.0) {
        pwm = -1.0;
    }
    
    if(pwm > 0.0) { 
        this->setDirection(FORWARD);
    } else {
        this->setDirection(BACKWARD);
    }
    m_pwmValue = pwm;
    m_motorPwmPin->write(fabs(m_pwmValue));
}

float bra::MonsterDriver::getPWM(){
    return m_pwmValue;
}

void bra::MonsterDriver::setDirection(bra::MonsterDriver::Direction p_direction){
    m_motorDirPin_A->write(((bool)p_direction));
    m_motorDirPin_B->write(!((bool)p_direction));
}

void bra::MonsterDriver::enable(){
    m_motorEnablePin->write(bra::MonsterDriver::HIGH);
}

void bra::MonsterDriver::disable(){
    m_motorEnablePin->write(bra::MonsterDriver::LOW);
}
