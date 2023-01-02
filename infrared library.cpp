 * Specify which protocol(s) should be used for decoding.
 * If no protocol is defined, all protocols (except Bang&Olufsen) are active.
 * This must be done before the #include <IRremote.hpp>
 */
//#define DECODE_DENON        // Includes Sharp
//#define DECODE_JVC
//#define DECODE_KASEIKYO
//#define DECODE_PANASONIC    // alias for DECODE_KASEIKYO
//#define DECODE_LG
//#define DECODE_NEC          // Includes Apple and Onkyo
//#define DECODE_SAMSUNG
//#define DECODE_SONY
//#define DECODE_RC5
//#define DECODE_RC6

//#define DECODE_BOSEWAVE
//#define DECODE_LEGO_PF
//#define DECODE_MAGIQUEST
//#define DECODE_WHYNTER

//#define DECODE_DISTANCE_WIDTH // Universal decoder for pulse distance width protocols
//#define DECODE_HASH         // special decoder for all protocols

//#define DECODE_BEO          // This protocol must always be enabled manually, i.e. it is NOT enabled if no protocol is defined. It prevents decoding of SONY!

//#define DEBUG               // Activate this for lots of lovely debug output from the decoders.

//#define RAW_BUFFER_LENGTH  180  // Default is 112 if DECODE_MAGIQUEST is enabled, otherwise 100.

/*# Supported IR Protocols
` NEC / Onkyo / Apple ` &nbsp; &nbsp; ` Denon / Sharp ` &nbsp; &nbsp; ` Panasonic / Kaseikyo `

` JVC ` &nbsp; &nbsp; ` LG ` &nbsp; &nbsp; ` RC5 ` &nbsp; &nbsp; ` RC6 ` &nbsp; &nbsp; ` Samsung ` &nbsp; &nbsp; ` Sony `

` Universal Distance ` &nbsp; &nbsp; ` Hash ` &nbsp; &nbsp; ` Pronto `
 
` BoseWave ` &nbsp; &nbsp; ` Lego ` &nbsp; &nbsp; ` Whynter ` &nbsp; &nbsp; ` MagiQuest `*/


//----------------# Converting your 2.x program to the 3.x version---------------

### Example
#### 2.x program:


#include <IRremote.h>

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
...
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      ...
      irrecv.resume(); // Receive the next value
  }
  ...
}
```


#### 3.x program:

```c++
#include <IRremote.hpp>

void setup()
{
...
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      IrReceiver.printIRResultShort(&Serial); // optional use new print version
      ...
      IrReceiver.resume(); // Enable receiving of the next value
  }
  ...
}

# Receiving IR codes
Check for **received data** with:<br/>
`if (IrReceiver.decode()) {}`<br/>
This also decodes the received data.

## Data format
After successful decoding, the IR data is contained in the IRData structure, available as `IrReceiver.decodedIRData`.

```c++
struct IRData {
    decode_type_t protocol;     // UNKNOWN, NEC, SONY, RC5, PULSE_DISTANCE, ...
    uint16_t address;           // Decoded address
    uint16_t command;           // Decoded command
    uint16_t extra;             // Used for Kaseikyo unknown vendor ID. Ticks used for decoding Distance protocol.
    uint16_t numberOfBits;      // Number of bits received for data (address + command + parity) - to determine protocol length if different length are possible.
    uint8_t flags;              // See IRDATA_FLAGS_* definitions
    uint32_t decodedRawData;    // Up to 32 bit decoded raw data, used for sendRaw functions.
    uint32_t decodedRawDataArray[RAW_DATA_ARRAY_SIZE]; // 32 bit decoded raw data, to be used for send function.
    irparams_struct *rawDataPtr; // Pointer of the raw timing data to be decoded. Mainly the data buffer filled by receiving ISR.
};
```
#### To access the **RAW data**, use:
```c++
uint32_t myRawdata= IrReceiver.decodedIRData.decodedRawData;
```

The definitions for the `IrReceiver.decodedIRData.flags` are described [here](https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/src/IRremoteInt.h#L128-L140).

#### Print all fields:
```c++
IrReceiver.printIRResultShort(&Serial);
```

#### Print the raw timing data received:
```c++
IrReceiver.printIRResultRawFormatted(&Serial, true);`
```

<br/>