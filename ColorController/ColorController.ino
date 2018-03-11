    /*Creator: Carlos Garcia Roig
     * This code allow you control an LCD- RGB Backlight colors 
     * by selecting each one of them using a button and adjusting
     * its brightness using an Angle Sensor
     */
    
    /*macro definitions of Rotary angle sensor and LED pin*/
    #define ROTARY_ANGLE_SENSOR A0
    #define ADC_REF 5//reference voltage of ADC is 5v.If the Vcc switch on the seeeduino
                     //board switches to 3V3, the ADC_REF should be 3.3
    #define GROVE_VCC 5//VCC of the grove interface is normally 5v
    #define FULL_ANGLE 300//full value of the rotary angle is 300 degrees

    /*Include the library of the LCD-RGB backlight*/
    #include <Wire.h> 
    #include "rgb_lcd.h"

    rgb_lcd lcd;
    
    int ContadorColor = 0; 
    int ColorR = 0;
    int ColorG = 0;
    int ColorB = 0;
    char buffer[17] = " ";
    
    void setup()
    {
        Serial.begin(9600);
        pinMode(ROTARY_ANGLE_SENSOR, INPUT);
        pinMode(2,INPUT);
        lcd.begin(16,2);
    }

    void loop()
    {
        //Color selector  
        // 0 = Red; 1 = Green ; 2 = Blue
        if(digitalRead(2) == HIGH){
          ContadorColor = (ContadorColor+1)%3;
          }
        int degrees;
        degrees = getDegree();
        int brightness = map(degrees, 0, FULL_ANGLE, 0, 255); 
        switch(ContadorColor){
          case 0:
            ColorR = brightness; 
            lcd.setRGB(ColorR,ColorG,ColorB);
            lcd.clear();
            sprintf (buffer,">R=%dG=%dB=%d",ColorR,ColorG,ColorB);
            lcd.print (buffer);
            break;
          case 1: 
            ColorG = brightness;
            lcd.setRGB(ColorR,ColorG,ColorB);
            lcd.clear();
            sprintf (buffer,"R=%d>G=%dB=%d",ColorR,ColorG,ColorB);
            lcd.print (buffer);
            break;
          case 2: 
            ColorB = brightness;
            lcd.setRGB(ColorR,ColorG,ColorB);
            lcd.clear();
            sprintf (buffer,"R=%dG=%d>B=%d",ColorR,ColorG,ColorB);
            lcd.print (buffer);
            break;
          } 
         delay(150);                                       
    }
    /************************************************************************/
    /*Function: Get the angle between the mark and the starting position    */
    /*Parameter:-void                                                       */
    /*Return:   -int,the range of degrees is 0~300                          */
    int getDegree()
    {
        int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
        Serial.println(sensor_value);
        float voltage;
        voltage = (float)sensor_value*ADC_REF/1023;
        //Serial.println(voltage);
        float degrees = (voltage*FULL_ANGLE)/GROVE_VCC;
        return degrees;
    }
