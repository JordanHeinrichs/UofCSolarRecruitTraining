const Messages = ({ messages }) => {
  return (
    <div className="mb-3 rounded bg-gray-200 px-4 py-2 text-red-500">
      <span className="text-xl font-bold">Errors:</span>
      {messages.map((message, index) => (
        <li key={index} className="list-none">
          {message}
        </li>
      ))}
    </div>
  );
};

export default Messages;
