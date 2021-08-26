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
  PRODUCT_DELETE_REQUEST,
  PRODUCT_DELETE_SUCCESS,
  PRODUCT_DELETE_FAIL,
  PRODUCT_CREATE_REQUEST,
  PRODUCT_CREATE_SUCCESS,
  PRODUCT_CREATE_FAIL,
  PRODUCT_UPDATE_REQUEST,
  PRODUCT_UPDATE_SUCCESS,
  PRODUCT_UPDATE_FAIL,
  PRODUCT_UPDATE_RESET,
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
  } catch (error) {
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




export const deleteProduct = (id) => async (dispatch, getState) => {
  try {
    dispatch({ type: PRODUCT_DELETE_REQUEST });

    const {
      userLogin: { userInfo },
    } = getState();

    const config = {
      headers: {
        Authorization: `Bearer ${userInfo.token}`,
      },
    };

    await axios.delete(`/api/products/${id}`, config);

    dispatch({ type: PRODUCT_DELETE_SUCCESS });
  } catch (error) {
    dispatch({
      type: PRODUCT_DELETE_FAIL,
      payload:
        error.response && error.response.data.message
          ? error.response.data.message
          : error.message,
    });
  }
};





export const createProduct = () => async (dispatch, getState) => {
  try {
    dispatch({ type: PRODUCT_CREATE_REQUEST });

    const {
      userLogin: { userInfo },
    } = getState();

    const config = {
      headers: {
        Authorization: `Bearer ${userInfo.token}`,
      },
    };

    const { data } = await axios.post(`/api/products`, {}, config);

    dispatch({ type: PRODUCT_CREATE_SUCCESS, payload: data });
  } catch (error) {
    dispatch({
      type: PRODUCT_CREATE_FAIL,
      payload:
        error.response && error.response.data.message
          ? error.response.data.message
          : error.message,
    });
  }
};





export const updateProduct = (productData) => async (dispatch, getState) => {
  try {
    dispatch({ type: PRODUCT_UPDATE_REQUEST });

    const {
      userLogin: { userInfo },
    } = getState();

    const config = {
      headers: {
        'Content-Type': 'application/json',
        Authorization: `Bearer ${userInfo.token}`,
      },
    };

    const { data } = await axios.put(
      `/api/products/${productData._id}`,
      productData,
      config
    );

    dispatch({ type: PRODUCT_UPDATE_SUCCESS, payload: data });
  } catch (error) {
    dispatch({
      type: PRODUCT_UPDATE_FAIL,
      payload:
        error.response && error.response.data.message
          ? error.response.data.message
          : error.message,
    });
  }
};
