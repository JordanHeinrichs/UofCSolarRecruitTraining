import React, {FC, InputHTMLAttributes} from "react";

interface SpeedInputProps {
  value: number; // Specify the type as 'number'
  onChange: (newValue: number) => void; // Define the type for the 'onChange' callback
}

const SpeedInput: React.FC<SpeedInputProps> = ({ value, onChange}) => {
  const handleSpeedChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const newValue = parseFloat(e.target.value);
    onChange(newValue);
  }
  return (
    <>
      <div className="flex w-full flex-col items-center gap-2">
        <label>Speed (km/h):</label>
        <input
          id="speed"
          className="mx-[8px] w-1/4 rounded-md border border-solid border-[#ccc] px-[20px] py-[12px] text-black"
          name="speed"
          type="number"
          placeholder="Speed"
          value={value} // Bind the input value to the prop value
          onChange={handleSpeedChange} // Call the handler function on input change
        />
        
      </div>
    </>
  );
};

export default SpeedInput;
