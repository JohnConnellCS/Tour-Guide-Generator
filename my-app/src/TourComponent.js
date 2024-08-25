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
    <div style={styles.container}>
      <h1 style={styles.title}>Tour Robot Direction Generator</h1>

      <p style={styles.locations}> See ReadMe file for Input Formatting and Location Possibilities </p>

      <textarea
        onChange={handleLocationChange}
        style={styles.textarea}
      />
      <button onClick={handleSubmit} style={styles.button}>Generate Route</button>
      <div style={styles.routeContainer}>
        <h2 style={styles.subtitle}>Robot Directions</h2>
        <pre style={styles.routeText}>{route}</pre>
      </div>
    </div>
  );
};

const styles = {
  container: {
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
    justifyContent: 'center',
    minHeight: '100vh',
    backgroundColor: '#2E4057',  
    color: '#F5F5F5', 
    fontFamily: 'Lato, sans-serif',
  },
  title: {
    fontSize: '2.5rem',
    marginBottom: '1rem',
    color: '#A3C4C9', 
  },
  subtitle: {
    fontSize: '2rem',
    marginBottom: '1rem',
    color: '#A3C4C9',
  },
  locations: {
    fontSize: '1.2rem',
    marginBottom: '1rem',
    color: '#D1E3E1', 
    textAlign: 'center',
  },
  textarea: {
    width: '80%',
    height: '150px',
    marginBottom: '1rem',
    padding: '10px',
    fontSize: '1.1rem',
    borderRadius: '8px',
    border: '1px solid #A3C4C9', 
    backgroundColor: '#4A6572', 
    color: '#F5F5F5', 
  },
  button: {
    padding: '10px 20px',
    fontSize: '1.2rem',
    borderRadius: '8px',
    border: 'none',
    backgroundColor: '#557A95', 
    color: '#F5F5F5',
    cursor: 'pointer',
    marginBottom: '2rem',
  },
  routeContainer: {
    width: '80%',
    textAlign: 'center',
  },
  routeText: {
    whiteSpace: 'pre-wrap',
    wordWrap: 'break-word',
    backgroundColor: '#4A6572', 
    padding: '15px',
    borderRadius: '8px',
    fontSize: '1.1rem',
    border: '1px solid #A3C4C9',
    color: '#F5F5F5',
  }
};

export default TourComponent;