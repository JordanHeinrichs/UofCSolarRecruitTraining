import BatteryInput from "~/components/batteryInput";
import Header from "~/components/header";
import SpeedInput from "~/components/speedInput";
import WeatherInput from "~/components/weatherInput";
import Button from "~/components/Button/Button.tsx";
import {useState} from "react";

const App = () => {
  const [speed,setSpeed] = useState(null);
  const [batteryPercent, changeBatteryPercent] = useState(0);
  const [weather, weatherChange] = useState(0);
  const[speedValid,setSpeedValid]= useState(false);
  const[batteryValid,setBatteryValid]= useState(false);
  const [calc, setCalc] = useState(0)
  const [initialCalc, setInitialCalc] =useState(false);

  const calculateRange = (e) => {
    e.preventDefault();
    setCalc(-(speed * speed * batteryPercent / 2500) + (4 * batteryPercent) + weather);
    setInitialCalc(true);
  }
  const speedChangeHandler = (e) => {
    if(e.target.value > 90 || e.target.value < 0){
      setSpeedValid(false)
    }
    else{
      setSpeedValid(true)
      setSpeed(e.target.value)
      console.log(speed)
    }
}
  const weatherChangeHandler = (e) => {
    weatherChange(e.target.value);
    console.log(weather)
  }
const batterChangeHandler = (e) => {
    if(e.target.value > 100 || e.target.value<0) {
      setBatteryValid(false);
    }
    else{
      setBatteryValid(true);
      changeBatteryPercent(e.target.value);
      console.log("Battery %" + batteryPercent)}

}

  return (
    <div className="h-screen w-screen bg-[#212121]">
      <div className="flex h-full flex-col items-center pt-36 text-white">
        <Header />
        <form name="simulator" className="flex  w-full flex-col items-center bg-[#212121]">
          <div className="mb-4 flex w-full flex-col items-center gap-y-4">
            <SpeedInput onChangeHandler={speedChangeHandler} />
            {!speedValid && <p>The speed should be with the range of 0 to 90</p>}
            <BatteryInput onChangeHandler={batterChangeHandler} />
            {!batteryValid && <p>The battery percentage should be with the range of 0 to 100</p>}
          </div>
          <div className="flex w-full flex-row justify-center gap-4">
            <WeatherInput onChangeHandler={weatherChangeHandler} value={weather}/>
          </div>
          <div className="flex w-full flex-row justify-center gap-4">
            <Button clickHandle={calculateRange} name="Calculate"/>
          </div>
          {initialCalc && <p>The predicted range of the Eylsia is {calc} km.</p>}
        </form>
      </div>
    </div>
  );
};

export default App;
