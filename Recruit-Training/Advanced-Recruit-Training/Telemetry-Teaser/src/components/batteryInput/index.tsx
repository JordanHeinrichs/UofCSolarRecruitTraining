import React, {FC, InputHTMLAttributes} from "react";

interface BatteryInputProps {
  value: number; // Specify the type as 'number'
  onChange: (newValue: number) => void; // Define the type for the 'onChange' callback
}

const BatteryInput: React.FC<BatteryInputProps> = ({ value, onChange }) => {
  const handleBatteryChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const newValue = parseFloat(e.target.value);
    onChange(newValue);
  }
  return (
    <div className="flex w-full flex-col items-center gap-2">
      <label>Battery Percentage (%):</label>
      <input
        id="battery"
        className="mx-[8px] w-1/4 rounded-md border border-solid border-[#ccc] px-[20px] py-[12px] text-black"
        name="battery"
        type="number"
        placeholder="Battery"
        value={value} // Bind the input value to the prop value
        onChange={handleBatteryChange} // Call the handler function on input change
      
      />
    </div>
  );
};

export default BatteryInput;
