import React, { useEffect, useState } from 'react';
import { Link } from 'react-router-dom';
import { useNavigate } from 'react-router-dom';
import UserService from '../UserService';
import Summary from './Summary';

const Cart = () => {
    const [cartProducts, setCartProducts] = useState([]);
    const navigate = useNavigate();

    useEffect(() => {
      getCartDataFromApi()
        .then((data) => {
          setCartProducts(data);
        })
        .catch((error) => {
          console.error('Error fetching cart data:', error);
        });
    }, []);

    const handleSummary = async () => {
      try {
        navigate('/summary');
      } catch (error) {
        console.error('Error: ', error);
      }
    };

    const getCartDataFromApi = () => {
      let token = UserService.getToken();
      return fetch('http://localhost:8080/api/basket', {
        method: 'GET',
        headers: {
          accept: 'application/json',
          authorization: `Bearer ${token}`
        }
      })
        .then((response) => response.json())
        .catch((error) => {
          console.error('Error fetching cart data:', error);
          throw error;
        });
    };

    const deleteCartProduct = (productId) => {
        let token = UserService.getToken();
        fetch(`http://localhost:8080/api/basket?product=${productId}`, {
          method: 'DELETE',
          headers: {
            accept: 'application/json',
            authorization: `Bearer ${token}`
          }
        })
          .then((response) => {
            if (!response.ok) {
              throw new Error('Failed to delete product from cart');
            }
            return getCartDataFromApi();
          })
          .then((data) => {
            setCartProducts(data);
          })
          .catch((error) => {
            console.error('Error deleting product from cart:', error);
          });
      };

      return (
        <div className='Margin'>
          <table style={{ width: '100%' }}>
            <tbody>
              {cartProducts.map((product, index) => (
                <tr key={index}>
                  <td style={{ display: 'flex', alignItems: 'center' }}>
                    {product.image_base64 && (
                      <img
                        alt={product.nazwa}
                        src={"data:image/png;base64," +product.image_base64}
                        height="128px"
                        style={{ marginRight: '10px' }}
                      />
                    )}
                  </td>
                  <td>
                    <Link to={`/details/${index}`}>{product.nazwa}</Link>
                  </td>
                  <td>{product.cena}</td>
                  <td>
                    <button onClick={() => deleteCartProduct(product.id)}>Remove from Cart</button>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
          <button className='button-link' onClick={handleSummary}>
            Go to summary
          </button>
        </div>
      );
    };

export default Cart;