FRDM-KL46 based projects
========================

These are some projects I have created based on KL46 Freedom board

IDE used: Kinetis Design Studio
Other components used: Kinetis SDK

Currently active project is a remote vehicle monitoring application. It uses seperate GPS module and GSM module(SIM900) connected through UART

Hardware:
1. FRDM-KL46Z
2. GPS module (only Tx, 5V and GND pins are used)
3. GSM(SIM900) module (UART Tx/Rx, 5V, Logic 3.3V, GND pins)
4. Power supply (12V car baatery voltage to 5V converter. I have used 7805, but it is the least efficient solution. Should consider a switching power supply)

I intented to build a real-time tracker, which can be installed on a vehicle and when GPS fix is received, it would log the position details (Latitude, Logitude,
Speed, Heading, Time) to a remote server, periodically. That's one part. One the other end, this update would be reflected on a mobile application which would show the changing location on a map. This is the whole idea.


