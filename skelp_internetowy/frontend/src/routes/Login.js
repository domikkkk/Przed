import React from 'react';
import UserService from '../UserService';

const Login = () => {

  const handleLogin = async () => {
    try {
      await UserService.doLogin();
    } catch (error) {
      console.error('Error: ', error);
    }
  };

  return (
    <button className="button-link" onClick={handleLogin}>Log in</button>
  );
};

export default Login;