#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 100


#define DATA_PIN 6

//Rouge, jaune, vert, cyan, bleu, rose
int possibleHue[] = {0, 60, 120, 180, 240, 300};
// Define the array of leds
//CRGB leds[NUM_LEDS];
CRGBArray<NUM_LEDS> leds;

int vitesse = 3;

struct ledstate {
  int colour;
  int fade;
  int pause;
  int state;  //1 -> gradation; 2 -> stable; 3 -> exticntion
};
ledstate myledstate[NUM_LEDS];

void setup() { 
      Serial.begin(9600);
      randomSeed(analogRead(0));
      //FastLED.addLeds<NEOPIXEL, RGB>(leds, NUM_LEDS);
      FastLED.addLeds<NEOPIXEL,DATA_PIN>(leds, NUM_LEDS);
      int i =0;
      for (i=0; i<NUM_LEDS; i++)
      {
          //Hue aleatoire, full saturation and variable value
          myledstate[i].state = random(1,3);
          myledstate[i].colour = possibleHue[random(0,5)];
          myledstate[i].colour = random(0,360);
          myledstate[i].pause = random(0,900);
          if(myledstate[i].state == 2)
          {
            myledstate[i].fade = 255;
          }
          else
          {
            myledstate[i].fade = random(0, 255);
          }
          leds[i].setHSV(myledstate[i].colour, 255, myledstate[i].fade);
      }
}

void loop() { 
  int i = 0;
  for (i=0; i<NUM_LEDS; i++)
  {
    if(myledstate[i].state == 1)//CAS 1
    {
      if (myledstate[i].fade < 254)
      {
        myledstate[i].fade += vitesse;
      }
      else
      {
        myledstate[i].state = 2;
        myledstate[i].pause = 0;
        myledstate[i].fade = 255;
      }
    }
    else if (myledstate[i].state == 2)//CAS 2
    {
        if (myledstate[i].pause < 1000)
        {
          myledstate[i].pause += vitesse;
        }
        else
        {
          myledstate[i].state = 3;
        }
    }
    else
    {
        if (myledstate[i].fade > 1)
        {
          myledstate[i].fade -= vitesse;
        }
        else
        {
          myledstate[i].state = 1;
          myledstate[i].fade = 0;
          myledstate[i].colour = possibleHue[random(0,5)];
          myledstate[i].colour = random(0,360);
        }
    }
  leds[i].setHSV(myledstate[i].colour, 255, myledstate[i].fade);
  }
  FastLED.show();
  delay(1);
  //Serial.print("ullo");
}
