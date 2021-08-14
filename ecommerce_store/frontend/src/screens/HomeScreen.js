//----------------------- VERSION 3 --------------------------//
// Once we get our data back from the backend, we will
// save it in the our component's state.
// Once we get our data back, we also would want to do something
// with it, So in order to perform some action with it, we will
// use 'useEffect'.
import { useEffect } from 'react';
import { useDispatch, useSelector } from 'react-redux';
// we got rid of axios cause now we're not doing any requests directly.
import { Heading, Grid } from '@chakra-ui/react';
import Product from '../components/Product';
import { listProducts } from '../actions/productActions';
import Loader from '../components/Loader';
import Message from '../components/Message';

const HomeScreen = () => {
  // this will return a dispatch() function.
  const dispatch = useDispatch();
// useSelector is used to read values from the global Store.
    // from it we get the productList and get certain values from inside it
  const productList = useSelector((state) => state.productList);
  const { loading, products, error } = productList;

  useEffect(() => {
        // as soon as the component loads, we want to dispatch our 'listProducts' 
        // Action which will then go and appropriately do its job.
    dispatch(listProducts());
    // depending on when something get's dispatched we want to reload.
  }, [dispatch]);

  return (
    <div>
      <Heading mb="8" as="h2" fontSize="3xl">
        Latest Products
      </Heading>
      {loading ? (
        <Loader />
      ) : error ? (
        <Message type="error">{error}</Message>
      ) : (
        <Grid templateColumns="repeat(4, 1fr)" gap="8">
          {products.map((prod) => (
            <Product key={prod._id} product={prod} />
          ))}
        </Grid>
      )}
    </div>
  );
};

export default HomeScreen;







//----------------------------- VERSION 1 ---------------------------------//
/*
// this is our homescreen where all products will be displayed.
// Each of those products will be displayed in a certain way. The rule of that
// if defined in Product.js, so we must import it in order to display it on our Homescreen
import {Heading, Grid} from '@chakra-ui/react';
import Product from '../components/Product';
// The Product component currently depends on our product.js file, so we must
// import that here too.
import products from '../products';



// Our entire Home Page screen
const HomeScreen = () => {
    // essentially, we map over each of the product object, pass it to our Product.js, it
    // builds that product box and then fills it in the Grid (in this case 4 will be displayed in one line)
    
    // Imporant POINT:- Whenever you render arrays as below, you MUST give 'KEYS',
    // in order to uniquely indentify each product, in our case it would be the product._id
    return (
        <div>
            <Heading mb="8" as="h2" fontSize="3xl">
                Latest Products
            </Heading>

            <Grid templateColumns="repeat(4,1fr)" gap="8">
                
                {products.map( (prod) => (
                    <Product key={prod._id} product={prod}/>
                ))}
            </Grid>
        </div>
    )

}

export default HomeScreen;*/





// //----------------------- VERSION 2 --------------------------//
// // Once we get our data back from the backend, we will
// // save it in the our component's state.
// // Once we get our data back, we also would want to do something
// // with it, So in order to perform some action with it, we will
// // use 'useEffect'.
// import {useState, useEffect} from 'react';
// // Now instead of fetching our data from the frontend itself,
// // we will be fetching it from the backend. So in order to send
// // requests to the backend from the frontend, we will use axios
// import axios from 'axios';
// import {Heading, Grid} from '@chakra-ui/react';
// import Product from '../components/Product';


// const HomeScreen = () => {
//     // initialize the state variable (will be an array of objects)
//     const [products, setProducts] = useState([]);


//     // The async keyword means that the function will always
//     // return a promise and the await keyword makes it wait for
//     // the promise to get settled (resolves or rejected).

//     // res is an object with gives us a bunch of things from which
//     // we really only care about the data, so we directly destructure it
//     useEffect( () => {
//         const fetchProducts = async () => {
//             const {data} = await axios.get('api/products');
//             setProducts(data);
//         };

//         // trigger the function
//         fetchProducts();
//     } , [])
//     return (
//         <div>
//             <Heading mb="8" as="h2" fontSize="3xl">
//                 Latest Products
//             </Heading>

//             <Grid templateColumns="repeat(4,1fr)" gap="8">
                
//                 {products.map( (prod) => (
//                     <Product key={prod._id} product={prod}/>
//                 ))}
//             </Grid>
//         </div>
//     );

// };



// export default HomeScreen;






