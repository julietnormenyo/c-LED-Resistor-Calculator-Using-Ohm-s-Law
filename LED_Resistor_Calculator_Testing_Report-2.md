LED Resistor Value Calculator - Testing Report
Testing Lead

For this round I compiled the C++ program from Slide 10 (g++ -std=c++17) and ran a batch of LED circuits through it, checking both what printed to the console and what actually got written to led_resistor_report.txt to make sure they matched and the file wasn't dropping anything.

LED1 was just a plain normal design (Vs=9, Vf=2, If=20) to make sure the happy path works. LED2 (Vs=5, Vf=2, If=40) was there to check the high-current warning actually fires. Then LED3 through LED6 each broke one rule on purpose - Vs=0, then Vf=0, then Vs lower than Vf, then If=0 - so I could see all four invalid messages come up correctly. Last I threw in LED7 at exactly 30mA and LED8 at 31mA back to back, since that's the one spot in the spec where being off by even a little bit changes the output (the warning shouldn't show at 30 but should at 31).

Results

Case 1 came back with I=0.02A, R=350ohm, P=0.14W, marked Design Valid - matches hand calculation.

Case 2 gave I=0.04A, R=75ohm, P=0.12W, Design Valid, and the warning line printed as expected.

Cases 3-6 all correctly stopped before doing any math - I, R and P all sat at 0 and the report file recorded the right invalid reason for each one (Invalid Supply Voltage, Invalid Forward Voltage, Invalid Design, Invalid Current Value respectively).

Case 7 was the one I was most curious about. At exactly 30mA the program did NOT print the warning, which is correct since the code checks If > 30, not >=. R came out to 233.33ohm.

Case 8 at 31mA did trigger the warning, so the boundary is handled right on both sides.

I also compared the console output line by line against led_resistor_report.txt for all 8 records and they line up - same numbers, same status, same warning text where it applies. The program printed "Report saved successfully." after the loop finished and the file closed properly (no leftover open handle, checked by re-reading the file after the program exited).

Bugs found: none. Everything matched what the spec on slides 3-9 describes.

One thing worth flagging for the group, not a bug exactly: invalid records still get written to the file with Vs/Vf/If filled in but R and P as 0 - that's correct behavior per the spec, but it's worth double checking with the professor that "0" is what he wants displayed there instead of something like "N/A", since it could read as a real calculated resistor value at a glance.
