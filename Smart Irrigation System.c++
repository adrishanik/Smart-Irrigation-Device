#include <LiquidCrystal_12c.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Intilize the LCD display
LiquidCrystal - 12c LCD(0 * 27, 16, 2);

char auth[] = "1GP6cpN_sjbT1VvZp-04W1SSPPVKbHLqp";
char ssid[] = "Anik";
char pass[] = "123456789";
BlynkTimer timer;
bool Relay = 0;

#define sensor A0
#define waterPump D3

void setup()
{
    Serial.begin(9600);
    pinMode(waterPump, OUTPUT);
    digitalWrite(waterPump, HIGH);
    lcd.init();
    lcd.backlight();
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 80)
        lcd.setCursor(1, 0);
    lcd.print("System Loarding");
    for (int a = 0; a <= 15; a++)
        [lcd.setCursor(a, 1);
            lcd.print(".");
            delay(500);

        ] lcd.clear()

            timer.setinterval(100l, soilMoistureSensor);
}
BLYNK_WRITE(V1)
{
    Relay = param.asint();

    if (Relay == 1)
    {
        digitalWrite(waterPump, LOW);
        lcd.setCursor(0, 1);
        lcd.print("Motor is ON");
    }
    else
    {
        digitalWrite(waterPump, HIGH);
        lcd.setCursor(0, 1);
        lcd.print("Motor is OFF");
    }
}

void soilMoistureSensor()
{
    int value = analogRead(sensor);
    value = map(value, 0, 1024, 0, 100);
    value = (value - 100) * -1;

    Blynk.virtualWrite(V0, value);
    lcd.setCursor(0, 0);
    lcd.print("Moistue :");
    lcd.print(value);
    lcd.print("");
}

void loop()
{
    Blynk.run();
    timer.run();
}
