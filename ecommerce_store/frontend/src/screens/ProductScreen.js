//----------------------------- VERSION 1 ----------------------------//

// This is a individual product screen i.e a product and its details.
/*
import React from 'react';
import { Link as RouterLink } from 'react-router-dom';
import {
  Flex,
  Grid,
  Image,
  Heading,
  Text,
  Button,
  Container,
  Divider,
  Tag,
} from '@chakra-ui/react';
import Rating from '../components/Rating';
import products from '../products';



// We know that we had wrapped everything inside our
// Router component in App.js and we had called it a Provider.
// Now this is where we see what it actually does.

// If you notice we have destructed our 'match' object here.
// In order to see what is loaded in our Address bar, we can use
// this match object which is loaded by that ROUTER component in
// each and every component's props object.

// The reason it is avaible on each and every component is because,
// if you notice in App.js, the Router component is wrapping all 
// the other components. So it loads the match in the props object of each one.


// Inside the match object, we get all details related to our address bar and path.
const ProductScreen = ({ match }) => {

    // We are getting the 'params' key from match object.
    // You will notice it also has the ':id' variable that we had given in App.js.
    // So we can now use it here.

    // We will parse through the array of objects in our products.js data file
    // and loop over each product and try to find the details of the product 
    // that matches the id of the product we want.
    // once we get it we extract it.

    const product = products.find((prod) => prod._id === match.params.id);


    // return JSX
    return(
        <>
      <Flex mb="5">
        <Button as={RouterLink} to="/" colorScheme="gray">
          Go Back
        </Button>
      </Flex>
      <Grid templateColumns="5fr 4fr 3fr" gap="10">
        <Image src={product.image} alt={product.name} borderRadius="md" />
        <Flex direction="column">
          <Heading as="h6" fontSize="base" color="gray.500">
            {product.brand}
          </Heading>
          <Heading as="h2" fontSize="4xl" mb="5">
            {product.name}
          </Heading>
          <Rating
            value={product.rating}
            text={`${product.numReviews} reviews`}
            alignment="single"
          />
          <Heading
            as="h5"
            fontSize="4xl"
            fontWeight="medium"
            color="teal.600"
            mt="5"
            mb="5"
          >
            ₹{product.price}
          </Heading>
          <Text color="gray.500">{product.description}</Text>
        </Flex>
        <Flex direction="column">
          <Flex justifyContent="space-between" py="2">
            <Text>Price:</Text>
            <Text fontWeight="bold">₹{product.price}</Text>
          </Flex>
          <Divider />
          <Flex justifyContent="space-between" py="2">
            <Text>Status:</Text>
            <Text fontWeight="bold">
              {product.countInStock > 0 ? 'In Stock' : 'Unavailable'}
            </Text>
          </Flex>
          <Divider />
          <Button
            bgColor="gray.800"
            textTransform="uppercase"
            letterSpacing="wide"
            colorScheme="teal"
            my="2"
            disabled={product.countInStock === 0}
          >
            Add To Cart
          </Button>
        </Flex>
      </Grid>
    </>

    );
}

export default ProductScreen;
*/



// ------------------------------ VERSION 2 ---------------------------------- //
// We're fixing the thing and changing it to axios here as well/
/*
import {useState, useEffect} from 'react';
import {useDispatch,useSelector} from 'react-redux';
import axios from 'axios';
import { Link as RouterLink } from 'react-router-dom';
import {
  Flex,
  Grid,
  Image,
  Heading,
  Text,
  Button,
  Container,
  Divider,
  Tag,
} from '@chakra-ui/react';
import Rating from '../components/Rating';
// import products from '../products';




const ProductScreen = ({ match }) => {
  // initialize it to empty, to avoid errors in general.

  //** Remember to give useState a default value, i.e product = {}.
  // If you dont do this, then we know that JS will try and render the JSX below,
  // since its synchronous. So, if we dont give it some initial value, it will give us 
  // an undefined error
  const [product, setProduct] = useState({}); 
  // const [products,setProducts] = useState([]);

  // const product = products.find((prod) => prod._id === match.params.id);

  // Now we are trying to send req to the backend from here.
  useEffect(() => {
    const fetchProduct = async () => {
      // Send an axios request to the following route. eg:- /api/products/3

      // wait for it to send the data of the 3rd product back and store it
      // use it to display component below
      const { data } = await axios.get(`/api/products/${match.params.id}`);
      setProduct(data);
    };

    fetchProduct();
  }, [match]);



  return(
    <>
  <Flex mb="5">
    <Button as={RouterLink} to="/" colorScheme="gray">
      Go Back
    </Button>
  </Flex>
  <Grid templateColumns="5fr 4fr 3fr" gap="10">
    <Image src={product.image} alt={product.name} borderRadius="md" />
    <Flex direction="column">
      <Heading as="h6" fontSize="base" color="gray.500">
        {product.brand}
      </Heading>
      <Heading as="h2" fontSize="4xl" mb="5">
        {product.name}
      </Heading>
      <Rating
        value={product.rating}
        text={`${product.numReviews} reviews`}
        alignment="single"
      />
      <Heading
        as="h5"
        fontSize="4xl"
        fontWeight="medium"
        color="teal.600"
        mt="5"
        mb="5"
      >
        ₹{product.price}
      </Heading>
      <Text color="gray.500">{product.description}</Text>
    </Flex>
    <Flex direction="column">
      <Flex justifyContent="space-between" py="2">
        <Text>Price:</Text>
        <Text fontWeight="bold">₹{product.price}</Text>
      </Flex>
      <Divider />
      <Flex justifyContent="space-between" py="2">
        <Text>Status:</Text>
        <Text fontWeight="bold">
          {product.countInStock > 0 ? 'In Stock' : 'Unavailable'}
        </Text>
      </Flex>
      <Divider />
      <Button
        bgColor="gray.800"
        textTransform="uppercase"
        letterSpacing="wide"
        colorScheme="teal"
        my="2"
        disabled={product.countInStock === 0}
      >
        Add To Cart
      </Button>
    </Flex>
  </Grid>
  </>

);
}

export default ProductScreen;*/









// ------------------------------ VERSION 3 ---------------------------------- //
import {useState, useEffect} from 'react';
import {useDispatch,useSelector} from 'react-redux';
import { Link as RouterLink } from 'react-router-dom';
import {
  Flex,
  Grid,
  Image,
  Heading,
  Text,
  Button,
  Container,
  Select,
  Divider,
  Tag,
} from '@chakra-ui/react';
import Rating from '../components/Rating';
import {listProductDetails} from '../actions/productActions';
import Loader from '../components/Loader';
import Message from '../components/Message';
import { productDetailsReducer } from '../reducers/productReducer';
import { set } from 'mongoose';


// Just like match, React Router also gives 'history'
// this will help us navigate.
const ProductScreen = ({ match, history }) => {
  const [qty, setQty] = useState(1);

  const dispatch = useDispatch();

  const productDetails = useSelector( (state) => state.productDetails);
  const {loading, product, error} = productDetails;



  useEffect(() => {
    // pass the match.params.id to listProductDetails
    // and trigger it.
    dispatch(listProductDetails(match.params.id));
    // each time something in URL changes or dispatch changes
    // we refresh again
  }, [match, dispatch]);


  // This will be triggered when someone clicks
  // add to cart.
  const addToCartHandler = () => {
    // If someone changes the quantity, we pull it from the
    // qty variable and with the help of this and the id, we 
    // generate a route  i.e we will be redirected to this link
    history.push(`/cart/${match.params.id}?qty=${qty}`)
  }



  //* [1,2,3,4,5,...] This builds an option box
  // to select quantity*/}
  return(
    <>
  <Flex mb="5">
    <Button as={RouterLink} to="/" colorScheme="gray">
      Go Back
    </Button>
  </Flex>
  

  {loading ? (<Loader />) : error ? 
    (<Message type="error">{error}</Message>) : 
    (
<Grid templateColumns="5fr 4fr 3fr" gap="10">
    <Image src={product.image} alt={product.name} borderRadius="md" />
    <Flex direction="column">
      <Heading as="h6" fontSize="base" color="gray.500">
        {product.brand}
      </Heading>
      <Heading as="h2" fontSize="4xl" mb="5">
        {product.name}
      </Heading>
      <Rating
        value={product.rating}
        text={`${product.numReviews} reviews`}
        alignment="single"
      />
      <Heading
        as="h5"
        fontSize="4xl"
        fontWeight="medium"
        color="teal.600"
        mt="5"
        mb="5"
      >
        ₹{product.price}
      </Heading>
      <Text color="gray.500">{product.description}</Text>
    </Flex>
    <Flex direction="column">
      <Flex justifyContent="space-between" py="2">
        <Text>Price:</Text>
        <Text fontWeight="bold">₹{product.price}</Text>
      </Flex>
      <Divider />
      <Flex justifyContent="space-between" py="2">
        <Text>Status:</Text>
        <Text fontWeight="bold">
          {product.countInStock > 0 ? 'In Stock' : 'Unavailable'}
        </Text>
      </Flex>


      <Divider />
         {product.countInStock > 0 && (
           <Flex justifyContent="space-between" py="2">
             <Text>Qty: </Text>
             <Select value={qty} onChange={e => setQty(e.target.value)} width="30%">
              {[...Array(product.countInStock).keys()].map(i => (
                <option key={i + 1} value={i+1}>{i+1}</option>
              ))}
             </Select>
           </Flex>
         )}
      <Divider />



      <Button
        onClick={addToCartHandler}
        bgColor="gray.800"
        textTransform="uppercase"
        letterSpacing="wide"
        colorScheme="teal"
        my="2"
        disabled={product.countInStock === 0}
      >
        Add To Cart
      </Button>
    </Flex>
  </Grid>
    )}
  </>

);
}

export default ProductScreen;