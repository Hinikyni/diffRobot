#ifndef MANUFATURA_ADITIVA_DIFFROBOT_HPP
#define MANUFATURA_ADITIVA_DIFFROBOT_HPP

#include <mbed.h>
#include <monsterdriver.hpp>
#include <encoder.hpp>
#include <pid.hpp>

namespace bra{

    class DiffRobot {

        private:
            float m_wheelLeftRadius, m_wheelRightRadius; // Wheel's Radius
            float m_lengthWheels; // Distance beetween wheels
            bool m_robotStatus;
            volatile float m_velocity[2]; // Linear and Angular Velocity
            volatile float m_wheelsVelocityTarget[2]; // Desired Wheels Velocity
            volatile float m_wheelsVelocity[2]; // Wheels Velocity
            volatile unsigned long m_lastTime;
            Timer m_Timer;

            const float m_PI = 3.14159265359;
            const float m_MICROS2SEC = 0.000001;
        public:
            DiffRobot(float p_wheelLeftRadius, float p_wheelRightRadius, float p_lengthWheels);
            ~DiffRobot();
            MonsterDriver* MotorLeft;
            MonsterDriver* MotorRight;
                     
            PID* VelocityControllerLeft;
            PID* VelocityControllerRight;
            
            Encoder* EncoderLeft;
            Encoder* EncoderRight;
            enum {LINEAR, ANGULAR};

            void setupMonsterDrivers(   // Left Motor
                                        PinName p_motorLeftEnablePin,
                                        PinName p_motorLeftPwmPin, 
                                        PinName p_motorLeftDirPin_A,
                                        PinName p_motorLeftDirPin_B,
                                        // Right Motor
                                        PinName p_motorRightEnablePin,
                                        PinName p_motorRightPwmPin, 
                                        PinName p_motorRightDirPin_A,
                                        PinName p_motorRightDirPin_B                                        
                                    );
            void setupEncoders( // Left Wheel
                                PinName p_phasePinALeft, PinName p_phasePinBLeft, void (*callbackRiseALeft)(), void (*callbackChangeBLeft)(), int p_resolutionLeft, bool p_sideLeft,
                                // Right Wheel
                                PinName p_phasePinARight, PinName p_phasePinBRight, void (*callbackRiseARight)(), void (*callbackChangeBRight)(), int p_resolutionRight, bool p_sideRight
                            );
            void setupController(   // Left Motor
                                    float p_KpLeft, float p_KiLeft, float p_KdLeft,
                                    // Right Motor
                                    float p_KpRight, float p_KiRight, float p_KdRight,
                                    int p_interval
                                );

            void setVelocity(float p_linear, float p_angular);   // Set Velocity in m/s and rad/s
            void run();
            void enable();
            void disable();
            bool getStatus();
            volatile float* getVelocity();   // Return velocity in m/s and rad/s
            float getVelocity(int);
            
    };
}
#endif