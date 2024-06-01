import React from 'react';
import UserService from '../UserService';
import { useNavigate } from 'react-router-dom';

const Logout = () => {
  const navigate = useNavigate();
  const handleRegister = async () => {
    try {
        navigate('/');
        await UserService.doLogout();
      } catch (error) {
        console.error('Error: ', error);
      }
  };

  return (
    <button className="button-link" onClick={handleRegister}>Log out</button>
  );
};

export default Logout;