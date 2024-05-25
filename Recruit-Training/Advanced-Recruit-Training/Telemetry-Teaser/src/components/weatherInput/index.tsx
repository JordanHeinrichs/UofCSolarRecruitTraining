const WeatherInput = ({ state, dispatch }) => {
  return (
    <>
      <img src="/Cloud.png" height="66px" width="66px" alt="Cloud" />
      <input
        id="weather"
        className="w-1/4"
        type="range"
        min="0"
        max="100"
        value={state.weather}
        onChange={(e) => {
          const weatherValue =
            e.target.value !== "" ? parseInt(e.target.value) : null;
          dispatch({ type: "setWeather", payload: weatherValue });
        }}
      />
      <img src="/Sun.png" height="66px" width="66px" alt="Sun" />
    </>
  );
};

export default WeatherInput;
