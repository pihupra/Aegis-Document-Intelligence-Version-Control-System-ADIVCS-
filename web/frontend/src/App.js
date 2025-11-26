import React, { useEffect, useState } from "react";

function App() {
  const [docs, setDocs] = useState([]);
  const [query, setQuery] = useState("");

  useEffect(() => {
    fetch("/documents")
      .then(res => res.json())
      .then(setDocs);
  }, []);

  const searchDocs = () => {
    fetch(`/document/search?q=${query}`)
      .then(res => res.json())
      .then(setDocs);
  };

  return (
    <div style={{ padding: 20 }}>
      <h1>Aegis Document System</h1>
      <input value={query} onChange={e => setQuery(e.target.value)} placeholder="Search..." />
      <button onClick={searchDocs}>Search</button>
      <ul>
        {docs.map(d => (
          <li key={d.id}>{d.id} | {d.title} | {d.author}</li>
        ))}
      </ul>
    </div>
  );
}

export default App;
