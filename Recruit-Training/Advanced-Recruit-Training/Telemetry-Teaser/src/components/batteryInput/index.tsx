interface Props {
  battery: number;
  setBattery: React.Dispatch<React.SetStateAction<number>>;
}

const BatteryInput = (props: Props) => {
  return (
    <div className="flex w-full flex-col items-center gap-2">
      <label>Battery Percentage (%):</label>
      <input
        id="battery"
        className="mx-[8px] w-1/4 rounded-md border border-solid border-[#ccc] px-[20px] py-[12px] text-black"
        name="battery"
        type="number"
        placeholder="Battery"
        value={props.battery}
        onChange={(e) => props.setBattery(parseInt(e.target.value))}
      />
    </div>
  );
};

export default BatteryInput;
