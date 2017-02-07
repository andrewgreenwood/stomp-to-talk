/*
    Project:    "Stomp-to-Talk"
    Author:     Andrew Greenwood
    Date:       March 2014
    Licence:    Public domain / do whatever you want with this code
*/

#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

// MIDI messages for pedal down/up (LSB first). These are control change
// messages on channel 0 relating to the sustain pedal (controller 0x40)
// where 0x7f is "on" and 0x00 is "off"
#define PEDAL_DOWN  0x007f40b0      // B0 40 7F
#define PEDAL_UP    0x000040b0      // B0 40 00

// Push-to-Talk key scancode to send - you'll need to look this up as it
// is hardware-dependent.
#define PTT_KEYCODE 0x28

// MIDI input device number to open - this depends on your Windows
// configuration.
#define MIDI_INPUT 1

void CALLBACK handle_midi_event(
    HMIDIIN midi_input,
    UINT message,
    DWORD_PTR userdata,
    DWORD_PTR param_1,
    DWORD_PTR param_2)
{
    INPUT input[1];

    // Respond to MIDI input messages
    if ( message == MIM_DATA )
    {
        // Prepare the keyboard input
        input[0].type = INPUT_KEYBOARD;
        input[0].ki.wVk = 0;
        input[0].ki.wScan = PTT_KEYCODE;
        input[0].ki.dwFlags = KEYEVENTF_SCANCODE;
        input[0].ki.time = 0;
        input[0].ki.dwExtraInfo = 0;

        switch ( param_1 )
        {
            // If the pedal was pressed down, send the input
            case PEDAL_DOWN :
                printf("Pedal down\n");
                SendInput(1, input, sizeof(INPUT));
                break;
                
            // If the pedal was released, send the input with the "key up" flag
            case PEDAL_UP :
                input[0].ki.dwFlags |= KEYEVENTF_KEYUP;
                SendInput(1, input, sizeof(INPUT));
                printf("Pedal up\n");
                break;
        }
    }
}

int main()
{
    HMIDIIN midi_input;

    // Open the MIDI input device
    if ( midiInOpen(&midi_input, MIDI_INPUT, (DWORD_PTR)handle_midi_event, (DWORD_PTR)NULL, CALLBACK_FUNCTION) != MMSYSERR_NOERROR )
    {
        MessageBox(0, "Failed to open MIDI input", "Error", MB_OK | MB_TASKMODAL);
        return 1;
    }

    // Begin receiving messages
    if ( midiInStart(midi_input) == MMSYSERR_NOERROR )
    {
        // We could probably do something better here but this works for now
        for ( ;; )
        {
            Sleep(1000);
        }
    }

    // Clean up (probably never called as you need to CTRL+C to exit)
    midiInClose(midi_input);
}
