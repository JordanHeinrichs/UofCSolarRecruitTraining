import { useReducer, useState } from "react";

import BatteryInput from "~/components/batteryInput";
import Header from "~/components/header";
import Messages from "~/components/messages";
import SpeedInput from "~/components/speedInput";
import WeatherInput from "~/components/weatherInput";

const App = () => {
  const initialState = {
    speed: null,
    battery: null,
    weather: 50,
    range: null,
  };

  const reducer = (state, action) => {
    switch (action.type) {
      case "setSpeed":
        return { ...state, speed: action.payload, range: null };
      case "setBattery":
        return { ...state, battery: action.payload, range: null };
      case "setWeather":
        return { ...state, weather: action.payload, range: null };
      case "setRange":
        return { ...state, range: action.payload };
      default:
        throw "Unknown type error";
    }
  };

  const [state, dispatch] = useReducer(reducer, initialState);
  const [messages, setMessages] = useState([]);

  const calculateRange = () => {
    if (checkErrors()) return;

    // s = speed, b = battery percentage w = weather
    // if s=1, b=2, w=50 then range=57.9992
    let s = state.speed,
      b = state.battery,
      w = state.weather;
    let range = -((s * s * b) / 2500) + 4 * b + w;
    dispatch({ type: "setRange", payload: range });
  };

  const checkErrors = () => {
    let messages = [];

    if (state.speed == null) messages.push("Speed is required");
    if (state.battery == null) messages.push("Battery is required");
    if (state.speed < 0 || state.speed > 90)
      messages.push("The speed should be within a range of 0 and 90");
    if (state.battery < 0 || state.battery > 100)
      messages.push(
        "The battery percentage should be within a range of 0 and 100",
      );
    setMessages(messages);
    return messages.length !== 0;
  };

  return (
    <div className="h-screen w-screen bg-[#212121]">
      <div className="flex h-full flex-col items-center pt-36 text-white">
        <Header />
        <form name="simulator" className="flex w-full flex-col items-center">
          <div className="mb-4 flex w-full flex-col items-center gap-y-4">
            <SpeedInput dispatch={dispatch} />
            <BatteryInput dispatch={dispatch} />
          </div>
          <div className="flex w-full flex-row justify-center gap-4">
            <WeatherInput state={state} dispatch={dispatch} />
          </div>

          <div className="my-4 flex flex-row rounded bg-blue-500 hover:bg-blue-600">
            <button
              type="button"
              className="flex items-center justify-center p-3 text-white"
              onClick={calculateRange}
            >
              Calculate
            </button>
          </div>

          <div className="text-black">
            {state.range &&
              `The predicted range of the Eylsia is ${state.range} km.`}
          </div>
          {/* {messages &&
              messages.map((message, index) => <li key={index}>{message}</li>)} */}
          {messages.length !== 0 && <Messages messages={messages} />}
        </form>
      </div>
    </div>
  );
};

export default App;
