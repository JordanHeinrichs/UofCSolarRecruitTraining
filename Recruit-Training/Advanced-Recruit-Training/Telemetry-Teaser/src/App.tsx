import { useState } from "react";

import BatteryInput from "~/components/batteryInput";
import Header from "~/components/header";
import SpeedInput from "~/components/speedInput";
import WeatherInput from "~/components/weatherInput";

const App = () => {
  // Calculates range only if speed and battery are valid
  const calculateRange = () => {
    if (validateSpeed() && validateBattery()) {
      const r = -((speed * speed * battery) / 2500) + 4 * battery + weather;
      setRange(r);
      console.log("Range: " + range);
      return;
    } else {
      return;
    }
  };
  // Returns 1 if Valid Speed
  const validateSpeed = () => {
    if (speed < 0 || speed > 90) {
      return 0;
    } else {
      return 1;
    }
  };
  // Returns 1 if Valid Battery
  const validateBattery = () => {
    if (battery < 0 || battery > 100) {
      return 0;
    } else {
      return 1;
    }
  };

  const [battery, setBattery] = useState(NaN);
  const [speed, setSpeed] = useState(NaN);
  const [weather, setWeather] = useState(50);

  const [range, setRange] = useState(NaN);

  return (
    <div className="h-screen w-screen bg-[#212121]">
      <div className="flex h-full flex-col items-center pt-36 text-white">
        <Header />
        <form name="simulator" className="flex w-full flex-col items-center">
          <div className="mb-4 flex w-full flex-col items-center gap-y-4">
            <SpeedInput speed={speed} setSpeed={setSpeed} />
            {isNaN(speed) && <p className="text-red-500">Speed is Required</p>}
            {!validateSpeed() && (
              <p className="text-red-500">
                The speed should be within the range of 0 to 90.
              </p>
            )}
            <BatteryInput battery={battery} setBattery={setBattery} />
            {isNaN(battery) && (
              <p className="text-red-500">Battery is Required</p>
            )}
            {!validateBattery() && (
              <p className="text-red-500">
                The speed should be within the range of 0 to 90.
              </p>
            )}
          </div>
          <div className="flex w-full flex-row justify-center gap-4">
            <WeatherInput weather={weather} setWeather={setWeather} />
          </div>
        </form>
        <button
          className="rounded bg-green-500 px-4 py-2 font-bold text-white hover:bg-lime-900"
          onClick={() => calculateRange()}
        >
          Calculate!
        </button>
        {!isNaN(range) && (
          <p text-white>The predicted range of the Eylsia is {range} km</p>
        )}
      </div>
    </div>
  );
};

export default App;
