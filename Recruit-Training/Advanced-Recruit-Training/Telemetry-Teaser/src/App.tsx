import { useState } from "react";

import BatteryInput from "~/components/batteryInput";
import Header from "~/components/header";
import SpeedInput from "~/components/speedInput";
import WeatherInput from "~/components/weatherInput";

const App = () => {
  const calculateRange = () => {
    if (validateSpeed() && validateBattery()) {
      setRange(-((speed * speed * battery) / 2500) + 4 * battery + weather);
    }
  };

  const validateSpeed = () => {
    return speed >= 0 && speed <= 90 ? true : false;
  };

  const validateBattery = () => {
    return battery >= 0 && battery <= 100 ? true : false;
  };

  const [speed, setSpeed] = useState<number>(0);
  const [battery, setBattery] = useState<number>(0);
  const [weather, setWeather] = useState<number>(0);
  const [range, setRange] = useState<number>(NaN);

  return (
    <div className="h-screen w-screen bg-[#212121]">
      <div className="flex h-full flex-col items-center pt-36 text-white">
        <Header />
        <form name="simulator" className="flex w-full flex-col items-center">
          <div className="mb-4 flex w-full flex-col items-center gap-y-4">
            <SpeedInput speed={speed} setSpeed={setSpeed} />
            {isNaN(speed) && <p className="text-red-600">Speed is required.</p>}
            {!isNaN(speed) && !validateSpeed() && (
              <p className="text-red-600">
                The speed should be within the range of 0 to 90.
              </p>
            )}
            <BatteryInput battery={battery} setBattery={setBattery} />
            {isNaN(battery) && (
              <p className="text-red-600">Battery percentage is required.</p>
            )}
            {!isNaN(battery) && !validateBattery() && (
              <p className="text-red-600">
                The battery percentage should be within the range of 0 to 100.
              </p>
            )}
          </div>
          <div className="flex w-full flex-row justify-center gap-4">
            <WeatherInput weather={weather} setWeather={setWeather} />
          </div>
        </form>
        <button
          className="rounded bg-blue-500 px-4 py-2 text-white hover:bg-blue-700"
          onClick={calculateRange}
        >
          Calculate
        </button>
        {/* <div className="py-6" style={{ display: showRange ? "block" : "none" }}>
          The predicted range of the Eylsia is {range.toFixed(2)} km.
        </div> */}
        {!isNaN(range) && validateSpeed() && validateBattery() && (
          <div className="py-6">
            The predicted range of the Eylsia is {range.toFixed(2)} km.
          </div>
        )}
      </div>
    </div>
  );
};

export default App;
