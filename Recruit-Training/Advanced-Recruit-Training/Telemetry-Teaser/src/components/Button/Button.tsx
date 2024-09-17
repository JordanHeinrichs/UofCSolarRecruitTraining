const Button = (props:any) => {
    return (
        <div className="m-2">
            <button
                className="bg-blue-500 text-white font-bold py-2 px-4 text-center rounded"
                onClick={props.clickHandle}>
                {props.name}
            </button>
        </div>
    )
}
export default Button;