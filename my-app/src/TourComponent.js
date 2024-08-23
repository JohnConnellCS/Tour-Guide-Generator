import React, { useState } from 'react';
import axios from 'axios';

const TourComponent = () => {
  const [locations, setLocations] = useState([]);
  const [route, setRoute] = useState('');

  const handleSubmit = async () => {
    try {
      const response = await axios.post('/generate_route', { locations });
      setRoute(response.data.route);
    } catch (error) {
      console.error('Error generating route:', error);
    }
  };

  const handleLocationChange = (e) => {
    const text = e.target.value;
    const lines = text.split('\n');
    const newLocations = lines.map(line => {
      const [name, description] = line.split('|');
      return { name, description };
    });
    setLocations(newLocations);
  };

  return (
    <div>
      <h1>Generate Tour Route</h1>
      <textarea
        placeholder="Enter locations in the format: name|description"
        onChange={handleLocationChange}
      />
      <button onClick={handleSubmit}>Generate Route</button>
      <div>
        <h2>Tour Route</h2>
        <pre>{route}</pre>
      </div>
    </div>
  );
};

export default TourComponent;
