Python Code: 
 
import serial 
import subprocess 
import threading 
 
PORT = "COM3"   # CHANGE THIS to your STM32 COM port 
BAUD = 115200 
 
def speak(text): 
    def _s(): 
        cmd = ( 
            "Add-Type -AssemblyName System.Speech; " 
            "$s = New-Object 
System.Speech.Synthesis.SpeechSynthesizer; " 
            "$s.Volume = 100; " 
            "$s.Rate = 0; " 
            f"$s.Speak('{text}')" 
        ) 
        subprocess.run(["powershell", "-Command", cmd], 
shell=True) 
    threading.Thread(target=_s, daemon=True).start() 
 
print("Connecting to STM32...") 
ser = serial.Serial(PORT, BAUD, timeout=1) 
print(f"Connected on {PORT} — waiting for EMG trigger...") 
 
while True: 
    try: 
        line = ser.readline().decode('utf-8', errors='ignore').strip() 
        if line: 
            print("STM32:", line) 
            if line.startswith("SPEAK:"): 
                speak(line[6:]) 
    except KeyboardInterrupt: 
        print("Stopped.") 
        break 
 
ser.close() 