import React from 'react';
import { useParams } from 'react-router-dom';

const ProductDetail = ({ products }) => {
  const { id } = useParams();
  const product = products[id];

  if (!product) {
    return <div>Can't find the product: {id}.</div>;
  }

  let pr = 'g';
  let waga = product.waga;
  if (product.waga/1000 > 1) {
    pr = 'kg';
    waga = product.waga/1000;
  }
  
  return (
    <div className='Margin'>
      <h2>{product.nazwa}</h2>
      <p>{product.opis}</p>
      <p>Price: {product.cena} zł</p>
      <p>Weight: {waga + pr}</p>
      <p>Dimensions: {product.wymiary}</p>
      {product.image_base64 && (<img alt={product.nazwa} src={'data:image/png;base64,' + product.image_base64} height="128px" style={{ marginRight: '10px' }}/>
      )}
    </div>
  );
};

export default ProductDetail;


// ulozyc to sensowniej