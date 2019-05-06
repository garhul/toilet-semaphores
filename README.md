# toilet-semaphores
Proof of concept using low power mode of deep_sleep awaken by a change in a switch.
Reporting switch state and battery level to a mqtt broker.


### instructions:

The file crds.h is in .gitignore, here you put your ssid and password, and some other sensitive data
since this is a proof of concept that's a quick'n'dirty solution to keep credentials.

here's a sample of the file:

```
#define LOCAL_SSID ""
#define LOCAL_PWD "" // your ssid
#define VBAT_MULTIPLIER 0.0092 // multiplier for the adc
#dfine BROKER 192.168.0.1  // your broker ip
```
