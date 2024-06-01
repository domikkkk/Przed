import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import App from './App';
import UserService from "./UserService";

const root = ReactDOM.createRoot(document.getElementById('root'));

UserService.initKeycloak();
root.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>
);
