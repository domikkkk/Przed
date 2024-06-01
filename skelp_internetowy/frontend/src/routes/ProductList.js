import React from 'react';
import { Link } from 'react-router-dom';
import cart from './../cart.png';
import UserService from '../UserService';


const ProductList = ({ products }) => {
    const handleAddToCart = (product) => {
        console.log(`Product added to cart: ${product.nazwa}`);
        let token = UserService.getToken();
        fetch(`http://localhost:8080/api/basket?product=${product.id}`, {
          method: 'PUT',
          headers: {
            accept: 'application/json',
            authorization: `Bearer ${token}`
          }
        })
      };
      return (
        <div className='Margin'>
          <table style={{ width: '100%' }}>
            <tbody>
              {products.map((product, index) => (
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
                    <button onClick={() => handleAddToCart(product)} className='cart'>
                    <img alt="Add to cart" src={cart} height="64px" />
                    </button>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      );
    };

export default ProductList;