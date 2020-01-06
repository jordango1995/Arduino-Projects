//////////////////////////IR CODE////////////////////////////

#include <IRremote.h>

int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;

#define BUTTON_OK 0xFF38C7
#define BUTTON_1 0xFFA25D
#define BUTTON_2 0xFF629D
#define BUTTON_3 0xFFE21D
#define BUTTON_4 0xFF22DD
#define BUTTON_5 0xFF02FD
#define BUTTON_6 0xFFC23D
#define BUTTON_7 0xFFE01F
#define BUTTON_8 0xFFA857
#define BUTTON_9 0xFF906F
#define BUTTON_0 0xFF9867

/////////////////////////////LED STRIP CODE///////////////////
#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    300
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

int LED_STRIP = 5;  //added by me

void setup() {
    delay( 3000 ); // power-up safety delay

    pinMode(LED_STRIP, OUTPUT); //added by me
    irrecv.enableIRIn();        //added by me
    
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

    //REDUNDANT:
    //currentPalette = RainbowColors_p;
    //currentBlending = LINEARBLEND;

    //currentPalette = myRedWhiteBluePalette_p; 
    //currentBlending = NOBLEND;
    
}




void loop() {

  if (irrecv.decode(&results))
  {

    //RAINBOW BLEND
    if (results.value == BUTTON_1)
    
      //digitalWrite(LED_STRIP, HIGH);    //COMMENTED THIS OUT BECAUSE REDUNDANCY
    { 
      currentPalette = RainbowColors_p;         
      currentBlending = LINEARBLEND;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);

/*
      if (results.value == BUTTON_OK)
      {
        SetupPurpleAndGreenPalette();             
        currentBlending = LINEARBLEND;
  
        static uint8_t startIndex = 0;
        startIndex = startIndex + 1; // motion speed 
      
        FillLEDsFromPaletteColors( startIndex);
      
        FastLED.show();
        FastLED.delay(1000 / UPDATES_PER_SECOND);
      }
*/
    }
    //irrecv.resume();   //COMMENTED THIS LINE OUT BECAUSE IT MAKES EACH CLICK EQUATE TO ONE CLOCK CYCLE


    //RAINBOW STRIPES, NO BLEND
    if (results.value == BUTTON_2)
    {
      currentPalette = RainbowStripeColors_p;   
      currentBlending = NOBLEND;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);

      if (results.value == BUTTON_OK)
      {
        digitalWrite(LED_PIN, LOW);
      }
      
    }

    //RAINBOW STRIPES, BLEND
    if (results.value == BUTTON_3)
    {
      currentPalette = RainbowStripeColors_p;   
      currentBlending = LINEARBLEND;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
    }

    //PURPLE AND GREEN
    if (results.value == BUTTON_4)
    {
      SetupPurpleAndGreenPalette();             
      currentBlending = LINEARBLEND;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
    }

    //RANDOM BLEND
    if (results.value == BUTTON_5)
    {
      SetupTotallyRandomPalette();              
      currentBlending = LINEARBLEND;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
    }

    //BLACK AND WHITE STRIPES, NO BLEND
    if (results.value == BUTTON_6)
    {
      SetupBlackAndWhiteStripedPalette();       
      currentBlending = NOBLEND;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
    }

    //BLACK AND WHITE STRIPES, BLEND
    if (results.value == BUTTON_7)
    {
      SetupBlackAndWhiteStripedPalette();       
      currentBlending = LINEARBLEND;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
    }

    //CLOUD COLORS, BLEND
    if (results.value == BUTTON_8)
    {
      currentPalette = CloudColors_p;           
      currentBlending = LINEARBLEND;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
    }

    //PARTY COLORS, BLEND
    if (results.value == BUTTON_9)
    {
      currentPalette = PartyColors_p;           
      currentBlending = LINEARBLEND;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
    }

    //ALL
    if (results.value == BUTTON_0)
    {
      ChangePalettePeriodically();
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
    }
/*
    if (results.value == BUTTON_OK)
    {
      digitalWrite(LED_PIN, LOW);

      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; // motion speed 
    
      FillLEDsFromPaletteColors( startIndex);
    
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
    }
*/   
  }
 
}


void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
      leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
      colorIndex += 3;
    }
}

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 15)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 20)  { SetupPurpleAndGreenPalette();             currentBlending = LINEARBLEND; }
        if( secondHand == 25)  { SetupTotallyRandomPalette();              currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { SetupBlackAndWhiteStripedPalette();       currentBlending = NOBLEND; }
        if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 45)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
        if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
}

void SetupTotallyRandomPalette()
{
    for( int i = 0; i < 16; i++) {
        currentPalette[i] = CHSV( random8(), 255, random8());
    }
}

void SetupBlackAndWhiteStripedPalette()
{
    // 'black out' all 16 palette entries...
    fill_solid( currentPalette, 16, CRGB::Black);
    // and set every fourth one to white.
    currentPalette[0] = CRGB::White;
    currentPalette[4] = CRGB::White;
    currentPalette[8] = CRGB::White;
    currentPalette[12] = CRGB::White;
    
}

void SetupPurpleAndGreenPalette()
{
    CRGB purple = CHSV( HUE_PURPLE, 255, 255);
    CRGB green  = CHSV( HUE_GREEN, 255, 255);
    CRGB black  = CRGB::Black;
    
    currentPalette = CRGBPalette16(
                                   green,  green,  black,  black,
                                   purple, purple, black,  black,
                                   green,  green,  black,  black,
                                   purple, purple, black,  black );
}

const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
    CRGB::Red,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Black,
    
    CRGB::Red,
    CRGB::Red,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Blue,
    CRGB::Blue,
    CRGB::Black,
    CRGB::Black
};


