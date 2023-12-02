interface props {
  weather: number;
  setWeather: React.Dispatch<React.SetStateAction<number>>;
}

const WeatherInput = (props: props) => {
  return (
    <>
      <img src="/Cloud.png" height="66px" width="66px" alt="Cloud" />
      <input
        id="weather"
        className="w-1/4"
        type="range"
        min="0"
        max="100"
        onChange={(e) => props.setWeather(e.target.valueAsNumber)}
      />
      <img src="/Sun.png" height="66px" width="66px" alt="Sun" />
    </>
  );
};

export default WeatherInput;
