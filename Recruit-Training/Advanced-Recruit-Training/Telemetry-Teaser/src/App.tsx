import { useReducer, useState } from "react";

import { type Action, type inputState } from "~/lib/types";

import BatteryInput from "~/components/batteryInput";
import Header from "~/components/header";
import SpeedInput from "~/components/speedInput";
import WeatherInput from "~/components/weatherInput";

const App = () => {
  const [show, setShow] = useState<boolean>(false);

  const reducer = (prev: inputState, action: Action) => {
    setShow(false);
    switch (action.type) {
      case "batteryInput":
        return { ...prev, batteryInput: action.payload };
      case "speedInput":
        return { ...prev, speedInput: action.payload };
      case "weatherInput":
        return { ...prev, weatherInput: action.payload };
      default:
        return prev;
    }
  };

  const [input, dispatch] = useReducer(reducer, {
    batteryInput: 0,
    speedInput: 0,
    weatherInput: 0,
  });

  const range =
    -((input.speedInput * input.speedInput * input.batteryInput) / 2500) +
    4 * input.batteryInput +
    input.weatherInput;

  const invalidBatteryInput =
    input.batteryInput < 0 || input.batteryInput > 100
      ? "The battery percentage should be with the range of 0 to 100"
      : input.batteryInput === 0
      ? "Battery is required"
      : "";
  const invalidSpeedInput =
    input.speedInput < 0 || input.speedInput > 90
      ? "The speed should be with the range of 0 to 90"
      : input.batteryInput === 0
      ? "Speed is required"
      : "";

  const calculateRange = (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    invalidBatteryInput && invalidSpeedInput ? setShow(false) : setShow(true);
  };

  return (
    <div className="h-screen w-screen bg-[#212121]">
      <div className="flex h-full flex-col items-center p-24 text-white">
        <Header />
        <form
          onSubmit={(e) => calculateRange(e)}
          name="simulator"
          className="flex w-full flex-col items-center"
        >
          <div className="mb-4 flex w-full flex-col items-center gap-y-4">
            <SpeedInput dispatch={dispatch} />
            <p>{invalidSpeedInput}</p>
            <BatteryInput dispatch={dispatch} />
            <p>{invalidBatteryInput}</p>
          </div>
          <div className="flex w-full flex-row justify-center gap-4">
            <WeatherInput dispatch={dispatch} />
          </div>
          <button
            type="submit"
            className="flex h-12 w-32 items-center justify-center rounded-md bg-blue-500"
          >
            Calculate
          </button>
        </form>
        {show && (
          <p>{"The predicted range of the Eylsia is " + range + " km."}</p>
        )}
      </div>
    </div>
  );
};

export default App;
