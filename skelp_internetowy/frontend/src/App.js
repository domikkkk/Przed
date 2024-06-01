import React, { useState, useEffect } from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import ProductDetail from './routes/ProductDetail';
import ProductList from './routes/ProductList'
import Header from './routes/Header';
import Cart from './routes/Cart';
import './App.css';
import Summary from './routes/Summary';

const App = () => {
  const [data, setData] = useState(null);
  useEffect(() => {
      const getproducts = async () => {
        try {
          const response = await fetch(`http://localhost:8080/api/products`);
          if (!response.ok) {
            throw new Error(`HTTP error! Status: ${response.status}`);
          }

          const jsonData = await response.json();
          console.log('Pobrane dane:', jsonData);
          setData(jsonData);
        } catch (error) {
          console.error('Błąd pobierania danych:', error.message);
        }
      }
      getproducts();
    }, []);


  const fetchData = async (newValues) => {
    try {
      if (!newValues) {
        newValues = [0, 10000];
      }
      const response = await fetch(`http://localhost:8080/api/products?minPrice=${newValues[0]}&maxPrice=${newValues[1]}`);
      if (!response.ok) {
        throw new Error(`HTTP error! Status: ${response.status}`);
      }

      const jsonData = await response.json();
      console.log('Pobrane dane:', jsonData);
      setData(jsonData);
    } catch (error) {
      console.error('Błąd pobierania danych:', error.message);
    }
  };

  console.log('Render komponentu. Aktualne dane:', data);

  return (
  <div className="App">
    <Router>
      <Header onFetchData={fetchData}/>
        { data ? (
          <Routes>
            <Route path="/details/:id" element={<ProductDetail products={data} />} />
            <Route path="/" element={<ProductList products={data} />} />
            <Route path="/cart" element={<Cart />} />
            <Route path="/summary" element={<Summary/>} />
          </Routes>
        ) : (
          <p>Ładu Ładu.. </p>
        )}
      
    </Router>
  </div>
  )
};

export default App;
