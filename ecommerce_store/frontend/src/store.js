// Here we're setting up our global store

//createStore - create a global store object
// combineReducers - we'll be making multiple reducers so we will need this.
// More on this later.
// applyMiddleware - We need middlewares too. More on this later
import {createStore,combineReducers, applyMiddleware} from 'redux';
// In redux, we cannot do asynchronous requests. Redux has a synchronous pattern,
// so if we want to do async req then we need this package.
import thunk from 'redux-thunk';
// every action and global stores will be visible on the browser
// via the extension we downloaded. It lays out a proper diagram for us to see.
// to use it we just import it here.
import {composeWithDevTools} from 'redux-devtools-extension';
import {productListReducer,productDetailsReducer} from './reducers/productReducer';
import {cartReducer} from './reducers/cartReducer';
import {userLoginReducer} from './reducers/userReducer';



// This is where we'll write all our reducers and the states that they
// will impact/change.
const reducer = combineReducers({
    // so productListReducer is going to update the value of p roductList.
    productList: productListReducer,
    productDetails: productDetailsReducer,
    cart: cartReducer,
    userLogin: userLoginReducer,
});



// Get any item that is present in the localStorage
// Since it will be stored in a string format, we need to
// convert it to JSON, so we use JSON.parse()
const cartItemsFromStorage = localStorage.getItem('cartItems') ? 
    JSON.parse(localStorage.getItem('cartItems'))
    : [];



// Once our user logs in we want to store their info in our local storage
const userInfoFromStorage = localStorage.getItem('userInfo') ? 
    JSON.parse(localStorage.getItem('userInfo'))
    : {};



// Our Global Store will initially have nothing
// if we wanted we could initialize this with some data
// If some content is already present in localStorage, set that as initialState
// else just put an empty array
const initialState = {
    cart: {cartItems: cartItemsFromStorage},
    userLogin: {userInfo: userInfoFromStorage}
                    
};




// All the middleware that we will use. You can add as many as
// you want to use.
// Thunk is something that'll help us make async requests.
// We will be passing all these middlewares to our composeWithDevTools(applyMiddleware()), because
// we know that it is responsible to keep track of all the requests, actions, etc. 
// i.e so that it could read everything in our store.
const middleware = [thunk];




// creating the global store
const store = createStore(
    reducer, 
    initialState, 
    composeWithDevTools(applyMiddleware(...middleware))
    );
 
  
export default store;


