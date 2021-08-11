import axios from 'axios';
// our actions will dispatch the action object to our reducer
// i.e the one with the 'type' and payload. So we need to import the 'types'
import {
  CART_ADD_ITEM,
  CART_REMOVE_ITEM,
  CART_SAVE_SHIPPING_ADDRESS,
  CART_SAVE_PAYMENT_METHOD,
} from '../constants/cartConstants';




// Just like dispatch, Redux also gives us getState.
// We know that whenever we run an action, we do so with the help of dispatch().
// getState is going to help us get access to our entire Global Store.
// We cannot use useSelector or useState here (hooks) as this is not a react component.


// To add an item to our cart
export const addToCart = (id, qty) => async (dispatch, getState) => {

      // We first get the details of the product
  const { data } = await axios.get(`/api/products/${id}`);


    // we want to dispatch the type
    // For the payload, we only send essential things, that we may need in our
    // cartReducer.js
  dispatch({
    type: CART_ADD_ITEM,
    payload: {
      product: data._id,
      name: data.name,
      image: data.image,
      price: data.price,
      countInStock: data.countInStock,
      qty,
    },
  });




 // Once it is stored in global store, 
    // We need the browser's local storage(Browser API)(inspect->Application->Storage) to make sure the cart items actually get stored and 
    // do not vanish after a simple reload. This'll store key value pairs. 
    // This will persist until the user goes and manually clears the caches, browsing history, cookies, etc.
    // localStorage has 2 features-> setItem / getItem
    // setItem(state, string)

    // getState() will get the entire store
    // we get the state
    // from it we get our actual cartItems. Stringify it and store it to the local storage
  localStorage.setItem('cartItems', JSON.stringify(getState().cart.cartItems));
};



// this one will not be async cause we're not making any axios call for this, cause we dont really need
// to get or update anything from our database. Because we're using local storage for our cart storing
export const removeFromCart = (id) => (dispatch, getState) => {
  dispatch({
    type: CART_REMOVE_ITEM,
        // the id of the item which we want to remove
    payload: id,
  });


    // update it again after removing
  localStorage.setItem('cartItems', JSON.stringify(getState().cart.cartItems));
};

export const saveShippingAddress = (data) => (dispatch) => {
  dispatch({ type: CART_SAVE_SHIPPING_ADDRESS, payload: data });


  localStorage.setItem('shippingAddress', JSON.stringify(data));
};

export const savePaymentMethod = (data) => (dispatch) => {
  dispatch({ type: CART_SAVE_PAYMENT_METHOD, payload: data });


  localStorage.setItem('paymentMethod', JSON.stringify(data));
};
