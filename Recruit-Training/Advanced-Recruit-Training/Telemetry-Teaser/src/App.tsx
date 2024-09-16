import BatteryInput from "~/components/batteryInput";
import Header from "~/components/header";
import SpeedInput from "~/components/speedInput";
import WeatherInput from "~/components/weatherInput";

import {useState, useEffect} from 'react';

const App = () => {
  const calculateRange = () => {
    var range = -(speed * speed * battery / 2500) + (4 * battery) + weather
    console.log("Range: "+ range);
    return;
  }
  
  const [battery, setBattery] = useState(0);
  const [speed, setSpeed] = useState(0);
  const [weather, setWeather] = useState(50);

  return (
    <div className="h-screen w-screen bg-[#212121]">
      <div className="flex h-full flex-col items-center pt-36 text-white">
        <Header />
        <form name="simulator" className="flex w-full flex-col items-center">
          <div className="mb-4 flex w-full flex-col items-center gap-y-4">
            <SpeedInput speed={speed} setSpeed={setSpeed}/>
            <BatteryInput battery={battery} setBattery={setBattery}/>
          </div>
          <div className="flex w-full flex-row justify-center gap-4">
            <WeatherInput weather={weather} setWeather={setWeather}/>
          </div>
        </form>
            <button className="bg-green-500 hover:bg-blue-700 text-white font-bold py-2 px-4 rounded" 
                    onClick={() => calculateRange()}>
                    Calculate!
            </button>
      </div>
    </div>
  );
};

export default App;
