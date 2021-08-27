// FOR ALL PRODUCTS
// THis is where we change our global store's value
// all product related variables in our global store will be updated
// from the functions here
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
  PRODUCT_CREATE_RESET,
  PRODUCT_UPDATE_REQUEST,
  PRODUCT_UPDATE_SUCCESS,
  PRODUCT_UPDATE_FAIL,
  PRODUCT_UPDATE_RESET,
  PRODUCT_CREATE_REVIEW_REQUEST,
  PRODUCT_CREATE_REVIEW_SUCCESS,
  PRODUCT_CREATE_REVIEW_FAIL,
  PRODUCT_CREATE_REVIEW_RESET,
} from '../constants/productConstants';



export const productListReducer = (state = { products: [] }, action) => {
   // The reason we're choosing these values in our cases
    // is because we want to keep track of when we request,
    // when it succeeds and when it fails. We can keep track of 
    // whatever we want but for now this should suffice.
    // ultimately all this will get stored in the state object. That is why
    // we made it an object.
  switch (action.type) {
        // the reason we've taken this into account is because
        // after we make our axios request for all products,
        // we could have some loading parameter which gets set to true,
        // i.e we wait until the product comes. We could use this later
        // to perhaps show a loading symbol
    case PRODUCT_LIST_REQUEST:
            // whatever we return, will end up replacing the 'products' variable in the
            // global store
            // after request is made, we want our loading to be true
      return { loading: true, products: [] };
    case PRODUCT_LIST_SUCCESS:
            // data has been returned so that is the payload.
            // and now loading must be set to false
      return { loading: false, products: action.payload };
    case PRODUCT_LIST_FAIL:
            // in case of error we'll attach the error to payload
            // set loading to false
      return { loading: false, error: action.payload };
    default:
          // IN any other case, we just return the state as it is.
      return state;
  }
};




// FOR SINGLE PRODUCT
// Product will contain product details and also an array of reviews
export const productDetailsReducer = (
  state = { product: { reviews: [] } },
  action
) => {
  switch (action.type) {
    case PRODUCT_DETAILS_REQUEST:
// this will contain details of 
                // whatever product you want to see, or something
                // you saw previously
      return { ...state, loading: true };
    case PRODUCT_DETAILS_SUCCESS:
    // fill with new details
      return { loading: false, product: action.payload };
    case PRODUCT_DETAILS_FAIL:
      return { loading: false, error: action.payload };
    default:
      return state;
  }
};



export const productDeleteReducer = (state = {}, action) => {
  switch (action.type) {
    case PRODUCT_DELETE_REQUEST:
      return { ...state, loading: true };
    case PRODUCT_DELETE_SUCCESS:
      return { loading: false, success: true };
    case PRODUCT_DELETE_FAIL:
      return { loading: false, error: action.payload };
    default:
      return state;
  }
};



export const productCreateReducer = (state = {}, action) => {
  switch (action.type) {
    case PRODUCT_CREATE_REQUEST:
      return { loading: true };
    case PRODUCT_CREATE_SUCCESS:
      return { loading: false, success: true, product: action.payload };
    case PRODUCT_CREATE_FAIL:
      return { loading: false, error: action.payload };
    case PRODUCT_CREATE_RESET:
      return {};
    default:
      return state;
  }
};



export const productUpdateReducer = (state = { product: {} }, action) => {
  switch (action.type) {
    case PRODUCT_UPDATE_REQUEST:
      return { loading: true };
    case PRODUCT_UPDATE_SUCCESS:
      return { loading: false, success: true, product: action.payload };
    case PRODUCT_UPDATE_FAIL:
      return { loading: false, error: action.payload };
    case PRODUCT_UPDATE_RESET:
      return { product: {} };
    default:
      return state;
  }
};



export const productCreateReviewReducer = (state = {}, action) => {
  switch (action.type) {
    case PRODUCT_CREATE_REVIEW_REQUEST:
      return { loading: true };
    case PRODUCT_CREATE_REVIEW_SUCCESS:
      return { loading: false, success: true };
    case PRODUCT_CREATE_REVIEW_FAIL:
      return { loading: false, error: action.payload };
    case PRODUCT_CREATE_REVIEW_RESET:
      return {};
    default:
      return state;
  }
};
