import axios from 'axios';
// our actions will dispatch the action object to our reducer
// i.e the one with the 'type' and payload. So we need to import the 'types'
import {
  PRODUCT_LIST_REQUEST,
  PRODUCT_LIST_SUCCESS,
  PRODUCT_LIST_FAIL,
  PRODUCT_DETAILS_REQUEST,
  PRODUCT_DETAILS_SUCCESS,
  PRODUCT_DETAILS_FAIL,
} from '../constants/productConstants';






// this will be responsible to get data we want to show on our homescreen
// we need this to async and we had already learnt about rethunk.
// so we will use that.
// Remember, our actions cannot be async, but they can surely return functions that
// are async
// Also, since this isnt the backend, we will directly use try catch instead of asyncHandler.
// Redux, gives you the dispatch function that you can accept and use.
export const listProducts = () => async (dispatch) => {
  try {

// dispatch the action object and will execute reducer function to this type.
    dispatch({ type: PRODUCT_LIST_REQUEST });


        // make a get request to get the data
    const { data } = await axios.get('/api/products');


        // dispatch the success if successful
    dispatch({ type: PRODUCT_LIST_SUCCESS, payload: data });

            // we're getting this error from axios. So we check if it has
        // the response property on it and if the data.message
  } catch (error) {
    dispatch({
      type: PRODUCT_LIST_FAIL,
            // if you have given your own custom message then we prefer to display
            // that else we will display the default error message we get
      payload:
        error.response && error.response.data.message
          ? error.response.data.message
          : error.message,
    });
  }
};










// Action for single product.


// this time we must accept an id which we'll get from our params
export const listProductDetails = (id) => async (dispatch) => {
  try {
        // dispatch the action object and will execute reducer function to this type.
    dispatch({ type: PRODUCT_DETAILS_REQUEST });
        // make a get request to get the data
    const { data } = await axios.get(`/api/products/${id}`);
        // dispatch the success if successful
    dispatch({ type: PRODUCT_DETAILS_SUCCESS, payload: data });

        // we're getting this error from axios. So we check if it has
        // the response property on it and if the data.message
  } 
  catch (error) {
    dispatch({
      type: PRODUCT_DETAILS_FAIL,
            // if you have given your own custom message then we prefer to display
            // that else we will display the default error message we get
      payload:
        error.response && error.response.data.message
          ? error.response.data.message
          : error.message,
    });
  }
};
