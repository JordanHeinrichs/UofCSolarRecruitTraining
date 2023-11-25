import React, { useState, FormEvent } from "react";
import BatteryInput from "~/components/batteryInput";
import Header from "~/components/header";
import SpeedInput from "~/components/speedInput";
import WeatherInput from "~/components/weatherInput";

const App = () => {
  const [speed, setSpeed] = useState(NaN);
  const [battery, setBattery] = useState(NaN);
  const [weather, setWeather] = useState(0);
  const [range, setRange] = useState(NaN);
  const [speedError, setSpeedError] = useState("");
  const [batteryError, setBatteryError] = useState("");
  const calculateRange = (event: FormEvent) => {
    event.preventDefault();
    // speedError = "Speed and battery must be set.";
    // Use the given equation to calculate the range
    if (!Number.isNaN(speed) && !Number.isNaN(battery) && battery <= 100 && battery >=0 && speed <= 90 && speed >=0) {
      const calculatedRange = -((speed * speed * battery) / 2500) + 4 * battery + weather;
      setRange(calculatedRange); // Update the range in the state

    }else{
      setRange(NaN)
    }
    setBatteryError("")
    setSpeedError("")

    if (speed > 90 || speed < 0){
      setSpeedError("The speed should be with the range of 0 to 90")
    }
    else if (Number.isNaN(speed)){
      setSpeedError("Speed is required")
    } 
    if (battery > 100 || battery <0){
      setBatteryError("The battery percentage should be with the range of 0 to 100")
    }
    else if (Number.isNaN(battery)){
      setBatteryError("Battery percentage is required")
    }
  
  };

  return (
    <div className="h-screen w-screen bg-[#212121]">
      <div className="flex h-full flex-col items-center pt-36 text-white">
        <Header />
        <form name="simulator" className="flex w-full flex-col items-center">
          <div className="mb-4 flex w-full flex-col items-center gap-y-4">
            <SpeedInput value={speed} onChange={setSpeed}/>
            {Number.isNaN(range) && speedError!="" &&(
              <div className="text-red-600">{speedError}</div>
            )}
            <BatteryInput value={battery} onChange={setBattery}/>
            {Number.isNaN(range) && batteryError!="" &&(
              <div className="text-red-600">{batteryError}</div>
            )}
          </div>
          <div className="flex w-full flex-row justify-center gap-4">
            <WeatherInput value={weather} onChange={setWeather}/>
          </div>
          <button
            onClick={calculateRange} // Call the calculateRange function when the button is clicked
            className="bg-blue-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded-lg inline-block"
          >
            Calculate
          </button>
          {!Number.isNaN(range) && (
            <p>
              The predicted range of the Eylsia is {range} km.
            </p>
          )}
        </form>
      </div>
    </div>
  );
};

export default App;
