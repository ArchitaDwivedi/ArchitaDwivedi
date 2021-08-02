// THis is where we change our global store's value
// all product related variables in our global store will be updated
// from the functions here
import {PRODUCT_LIST_REQUEST,
    PRODUCT_LIST_SUCCESS,
    PRODUCT_LIST_FAIL} from '../constants/productConstants'

export const productListReducer = (state = {products: []}, action) => {
    // The reason we're choosing these values in our cases
    // is because we want to keep track of when we request,
    // when it succeeds and when it fails. We can keep track of 
    // whatever we want but for now this should suffice.
    // ultimately all this will get stored in the state object. That is why
    // we made it an object.

    switch(action.type){
        // the reason we've taken this into account is because
        // after we make our axios request for all products,
        // we could have some loading parameter which gets set to true,
        // i.e we wait until the product comes. We could use this later
        // to perhaps show a loading symbol
        case PRODUCT_LIST_REQUEST:
            // whatever we return, will end up replacing the 'products' variable in the
            // global store
            // after request is made, we want our loading to be true
            return {loading: true, products: []};
        case PRODUCT_LIST_SUCCESS:
            // data has been returned so that is the payload.
            // and now loading must be set to false
            return {loading: false, products: action.payload};
        case PRODUCT_LIST_FAIL:
            // in case of error we'll attach the error to payload
            // set loading to false
            return {loading: false, error: action.payload};
        // IN any other case, we just return the state as it is.
        default:
            return state;
    }
};


