import React, { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';
import logo from '../logo.png';
import Slider from '@mui/material/Slider';
import Box from '@mui/material/Box';
import Tooltip from '@mui/material/Tooltip';
import Login from './Login';
import UserService from '../UserService';
import Logout from './Logout';

const Header = ({onFetchData}) => {
    const [phrase, setInputValue] = useState('');
    const handleSearch = (phrase, value) => {
        console.log(value);
        onFetchData(value);
        console.log(`Searched: ${phrase}`);
    };
    const handleInputChange = (event) => {
        setInputValue(event.target.value);
    };

    const [value, setValue] = useState([0, 10000]);
    const minDistance = 1;

    const handleChange = (event, newValue) => {
      onFetchData(newValue);
      if (!Array.isArray(newValue)) {
        return;
      }

      if (newValue[1] - newValue[0] < minDistance) {
        const clamped = newValue[0] + minDistance > 10000 ? 10000 - minDistance : newValue[0];
        setValue([clamped, clamped + minDistance]);
      } else {
        setValue(newValue);
      }
    };
    const user = UserService.getUsername();

    return (
        <div className="header">
            <img src={logo} className="App-logo" alt="logo" />
            <Link className="button-link" to="/">Home</Link>
            <div class="container" style={{ marginTop: 35 }}>
              <input
                type="text"
                placeholder="Search"
                className="search-input"
                size="60"
                onChange={handleInputChange}
              />
              <Tooltip title="Product price">
              <Box sx={{ width: 540 }}>
                <Slider
                  value={value}
                  onChange={handleChange}
                  disableSwap
                  valueLabelDisplay="auto"
                  min={0}
                  max={10000}
                />
              </Box>
              </Tooltip>
            </div>
            <button className="button-link" onClick={() => handleSearch(phrase, value)}>Submit</button>
            <div className="right-buttons">
                {user ? (
                    <>
                        <Link className='button-link' to="/cart">Cart</Link>
                        <p>Jesteś zalogowany jako {user}   </p>
                        <Logout />
                    </>
                    ) : (
                    <>
                        <Login />
                    </>
                )}
            </div>
        </div>
    );
};

export default Header;