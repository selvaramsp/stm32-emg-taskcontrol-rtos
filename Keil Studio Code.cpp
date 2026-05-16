Keil Studio(Online) Code: 
extern "C" int _printf_float; 
int _printf_float; 
#include "mbed.h" 
AnalogIn   emg(PA_0); 
DigitalOut led1(PB_0); 
DigitalOut led2(PB_1); 
BuAeredSerial pc(PA_2, PA_3, 115200); 
#define EMG_THRESHOLD    0.30f 
#define BLINK_MS         
300 
typedef enum { IDLE, UPDATED } State; 
void say(const char* msg) { 
pc.write(msg, strlen(msg)); 
pc.write("\r\n", 2); 
} 
int main() { 
led1 = 1; 
led2 = 0; 
ThisThread::sleep_for(1000ms); 
say("=============================="); 
say("  EMG UPDATE SYSTEM ONLINE"); 
say("  CLOSE FIST TO TRIGGER"); 
say("=============================="); 
    say("SPEAK:System ready. Close your fist to trigger firmware 
update."); 
 
    State state      = IDLE; 
    bool  above      = false; 
    auto  t_sample   = Kernel::Clock::now(); 
    auto  t_blink    = Kernel::Clock::now(); 
    bool  led2_state = false; 
    char  buf[64]; 
 
    while (true) { 
        auto now = Kernel::Clock::now(); 
 
        if (state == IDLE) { 
 
            if ((now - t_sample) >= 500ms) { 
                t_sample = now; 
 
                float emg_val = emg.read(); 
                int   emg_int = (int)(emg_val * 1000); 
                snprintf(buf, sizeof(buf), "EMG:%d.%03d", emg_int/1000, 
emg_int%1000); 
                say(buf); 
 
                /* single detection — no hold needed */ 
                if (emg_val >= EMG_THRESHOLD && !above) { 
                    above = true; 
 
                    /* ══ INSTANT TRIGGER ══ */ 
                    say(""); 
                    say("##################################"); 
                    say("##  EMG UPDATE TRIGGERED!      ##"); 
                    say("##  GETTING UPDATED            ##"); 
                    say("##  RECEIVED EMG SENSOR SIGNAL ##"); 
                    say("##################################"); 
                    say("SPEAK:GETTING UPDATED. RECEIVED EMG 
SENSOR SIGNAL. UPDATING FIRMWARE NOW."); 
 
                    led1 = 0;                          // LED1 OFF immediately 
                    ThisThread::sleep_for(2000ms);     // simulate flash write 
 
                    say("##################################"); 
                    say("##  FIRMWARE UPDATE COMPLETE!  ##"); 
                    say("##  NEW CODE NOW RUNNING       ##"); 
                    say("##################################"); 
                    say("SPEAK:Firmware update complete. New code is 
now running."); 
 
                    state = UPDATED; 
                } 
 
                if (emg_val < EMG_THRESHOLD) { 
                    above = false;   // reset for next gesture 
                } 
            } 
        } 
 
        else if (state == UPDATED) { 
            if ((now - t_blink) >= 300ms) { 
                t_blink    = now; 
                led2_state = !led2_state; 
                led2       = led2_state; 
            } 
        } 
    } 
} 