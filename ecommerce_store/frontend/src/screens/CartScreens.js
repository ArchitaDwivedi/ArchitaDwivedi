import {useEffect} from 'react';
import {Link as RouterLink} from 'react-router-dom';
import {useDispatch,useSelector} from 'react-redux';
import {
    Flex,
    Grid,
    Image,
    Box,
    Link,
    Icon,
    Heading,
    Text,
    Button,
    Select,
} from '@chakra-ui/react';
import Message from '../components/Message';
import {IoTrashBinSharp} from 'react-icons/io5';
import {addToCart,removeFromCart} from '../actions/cartActions';

// just like match and history, our React Router also returns
// location. In the location object you'll see url related info
// i.e your path and then also your query string. The query string
// will be under something called 'location.search'.
const CartScreen = ({match, history, location}) => {
    const productId = match.params.id;
    // the + here is used to convert the string to a number
    const qty = location.search ? +location.search.split("=")[1] : 1;


    const dispatch = useDispatch();

    // get cart state
    const cart = useSelector( (state) => state.cart);
    const {cartItems} = cart;

    useEffect( () => {
        // if someone comes via 'Add to Cart' i.e if there is id in the URL
        //, only then we want to dispatch
        if (productId){
            dispatch(addToCart(productId, qty));
        }
        // else if someone tries to directly access this without id, we will do nothing
    }, [dispatch, productId, qty]);





    // On the cart page, we also want to add the remove from cart functionality (button)
    const removeFromCartHandler = (id) => {

        dispatch(removeFromCart(id));

    }





    // Button for when the customer reaches the cart page, checks everything
    // and now wants to checkout (place order).
    const checkoutHandler = () => {
        // we're adding this parameter, incase the user was not logged in.
        // Once they log in, we will redirect them to the shipping page.
        history.push('/login?redirect=shipping');


    };




    return (
        <Grid gridTemplateColumns="3">
      <Box>
        <Heading mb="8">Shopping Cart</Heading>
        <Flex>
          {cartItems.length === 0 ? (
            <Message>
              Your cart is empty.{' '}
              <Link as={RouterLink} to="/">
                Go Back
              </Link>
            </Message>
          ) : (
            <Grid templateColumns="4fr 2fr" gap="10" w="full">
              <Flex direction="column">
                {cartItems.map((item) => (
                  <Grid
                    key={item.product}
                    size="100%"
                    alignItems="center"
                    justifyContent="space-between"
                    borderBottom="1px"
                    borderColor="gray.200"
                    py="4"
                    templateColumns="1fr 4fr 2fr 2fr 1fr"
                    px="6"
                    _hover={{ bgColor: 'gray.50' }}
                  >
                    <Image
                      src={item.image}
                      alt={item.name}
                      borderRadius="lg"
                      height="14"
                      width="14"
                      objectFit="cover"
                    />
                    <Text fontWeight="semibold" fontSize="lg">
                      <Link as={RouterLink} to={`/product/${item.product}`}>
                        {item.name}
                      </Link>
                    </Text>
                    <Text fontWeight="bold" fontSize="lg">
                      ₹{item.price}
                    </Text>
                    <Select
                        // if new qty is chosen, dispatch the entire addtocart action again
                      value={item.qty}
                      onChange={(e) =>
                        dispatch(
                          addToCart(item.product, Number(e.target.value))
                        )
                      }
                      width="20"
                    >
                      {[...Array(item.countInStock).keys()].map((x) => (
                        <option key={x + 1} value={x + 1}>
                          {x + 1}
                        </option>
                      ))}
                    </Select>
                    <Button
                      type="button"
                      colorScheme="red"
                      onClick={() => removeFromCartHandler(item.product)}
                    >
                      <Icon as={IoTrashBinSharp} />
                    </Button>
                  </Grid>
                ))}
              </Flex>




              <Flex
                direction="column"
                border="1px"
                borderWidth="2"
                borderColor="gray.200"
                rounded="md"
                padding="5"
                height="48"
                justifyContent="space-between"
              >
                <Flex direction="column">
                  <Heading as="h2" fontSize="3xl">
                    {/* Here we are trying to accumulate and depending on the quantity we are
                    going to get the final result */}
                    Subtotal (
                    {cartItems.reduce((acc, currItem) => acc + currItem.qty, 0)}
                    ) item/s
                  </Heading>
                  <Text fontWeight="bold" fontSize="2xl" color="blue.600">
                    ₹
                    {cartItems.reduce(
                        //depending of the quantity we decide the final price.
                      (acc, currItem) => acc + currItem.qty * currItem.price,
                      0
                    )}
                  </Text>
                </Flex>

                {/* To checkout*/}
                <Button
                  type="button"
                  disabled={cartItems.length === 0}
                  onClick={checkoutHandler}
                  size="lg"
                  colorScheme="teal"
                  bgColor="gray.800"
                >
                  Proceed To Checkout
                </Button>
              </Flex>
            </Grid>
          )}
        </Flex>
      </Box>
    </Grid>

    );
};

export default CartScreen;