import React, {FC, InputHTMLAttributes} from "react";

interface WeatherInputProps {
  value: number; // Specify the type as 'number'
  onChange: (newValue: number) => void; // Define the type for the 'onChange' callback
}

const WeatherInput: React.FC<WeatherInputProps> = ({ value, onChange }) => {
  const handleWeatherChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const newValue = parseFloat(e.target.value);
    onChange(newValue);
  }
  return (
    <>
      <img src="/Cloud.png" height="66px" width="66px" alt="Cloud" />
      <input
        id="weather"
        className="w-1/4"
        type="range"
        min="0"
        max="100"
        value={value} // Bind the input value to the prop value
        onChange={handleWeatherChange} // Call the handler function on input change
      />
      <img src="/Sun.png" height="66px" width="66px" alt="Sun" />
    </>
  );
};

export default WeatherInput;
