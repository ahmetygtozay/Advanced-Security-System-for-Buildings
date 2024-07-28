
# Smart Safe Security System

This project is a Smart Safe Security System using an Arduino, a keypad, a servo motor, an LCD display, and a buzzer. The system can lock and unlock based on a user-inputted password. It also includes a PIR sensor to detect unauthorized access and an LED for status indication. The system provides visual and auditory feedback for successful and failed unlock attempts.

## Features

1. **Keypad Input**: Users can enter a 4-digit password to unlock the safe.
2. **Servo Lock Mechanism**: A servo motor is used to physically lock and unlock the safe.
3. **LCD Display**: Displays the status of the safe, including locked/unlocked states and prompts for the user.
4. **PIR Sensor**: Detects motion and can trigger an alarm if unauthorized access is attempted.
5. **Buzzer**: Provides auditory feedback for successful unlock attempts and alarms for failed attempts or unauthorized access.
6. **LED Indicator**: Indicates the status of the safe, turning on when access is denied.

## Components Used

- Arduino
- Keypad
- Servo Motor
- LCD Display
- PIR Sensor
- Buzzer
- LED
- Resistors, Wires, Breadboard

## Setup and Usage

### 1. **Hardware Setup**

   - Connect the keypad, LCD, PIR sensor, servo motor, buzzer, and LED to the Arduino according to the pin configuration defined in the code.
   - Ensure the servo motor is correctly calibrated to lock and unlock positions.

### 2. **Software Setup**

   - Download the code and upload it to the Arduino.
   - You may need to install the following libraries:
     - LiquidCrystal
     - Keypad
     - Servo

### 3. **Operation**

   - Upon powering up, the system will display a welcome message and lock the safe.
   - To unlock the safe, enter the 4-digit password using the keypad. The default password is `1721`.
   - The system will provide feedback on the LCD and with the buzzer.
   - If the PIR sensor detects motion while the system is locked, or if the wrong password is entered, the system will trigger an alarm.

## Customization

- **Change Password**: The default password is set to `1721`. This can be changed by modifying the `PASSWORD` constant in the code.
- **Buzzer Tones**: The tones for successful and failed attempts can be modified in the `successful()` and `wrong()` functions.
- **Icons**: Customize the icons displayed on the LCD by modifying the `icons.h` file.

## Code Explanation

- **Lock and Unlock Functions**: `lock()` and `unlock()` control the servo motor to lock or unlock the safe.
- **showStartupMessage()**: Displays a welcome message on the LCD upon startup.
- **safeLockedLogic()**: Handles the logic when the safe is locked, including reading the password input.
- **safeUnlockedLogic()**: Handles the logic when the safe is unlocked.
- **inputSecretCode()**: Handles keypad input for the password.
- **showWaitScreen()**: Displays a waiting screen during processing.
- **successful()**: Plays a melody when the correct password is entered.
- **wrong()**: Triggers the alarm and LED when the wrong password is entered or unauthorized access is detected.

## Future Improvements

- Add an RTC (Real-Time Clock) to log access attempts with timestamps.
- Implement wireless notification for remote monitoring.
- Integrate with a mobile app for remote control and monitoring.

## License

This project is open-source and available under the MIT License.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## Acknowledgements

- Thanks to the Arduino community for providing resources and support.

Feel free to modify the project and adapt it to your specific needs!
```
