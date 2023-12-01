interface props {
  speed : number;
  setSpeed : React.Dispatch<React.SetStateAction<number>>;
}

const SpeedInput = (props : props) => {
  return (
    <>
      <div className="flex w-full flex-col items-center gap-2">
        <label>Speed (km/h):</label>
        <input
          id="speed"
          className="mx-[8px] w-1/4 rounded-md border border-solid border-[#ccc] px-[20px] py-[12px] text-black"
          name="speed"
          type="number"
          max="90"
          min="0"
          placeholder="Speed"
          value={props.speed}
          onChange={(e)=>(props.setSpeed(parseInt(e.target.value)))}
        />
      </div>
    </>
  );
};

export default SpeedInput;
