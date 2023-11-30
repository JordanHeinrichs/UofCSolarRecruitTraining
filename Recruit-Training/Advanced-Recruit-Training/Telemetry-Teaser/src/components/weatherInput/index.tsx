interface Props {
  weather: number;
  setWeather: React.Dispatch<React.SetStateAction<number>>;
}

const WeatherInput = (props: Props) => {
  return (
    <>
      <img src="/Cloud.png" height="66px" width="66px" alt="Cloud" />
      <input
        id="weather"
        className="w-1/4"
        type="range"
        min="0"
        max="100"
        value={props.weather}
        onChange={(e) => props.setWeather(parseInt(e.target.value))}
      />
      <img src="/Sun.png" height="66px" width="66px" alt="Sun" />
    </>
  );
};

export default WeatherInput;
