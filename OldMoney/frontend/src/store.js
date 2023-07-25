import {createStore, combineReducers, applyMiddleware} from 'redux';
import thunk from 'redux-thunk';
import {productListReducer, productDetailsReducer} from './reducers/productReducer';
import {composeWithDevTools} from 'redux-devtools-extension';
import { useState } from 'react';
import { cartReducer } from './reducers/cartReducer';
import {userLoginReducer, userRegisterReducer, userDetailsReducer, userUpdateProfileReducer} from './reducers/userReducer';
import { orderCreateReducer, orderDetailsReducer, orderPayReducer , orderMyListReducer} from './reducers/orderReducer';

const reducer = combineReducers({
	productList: productListReducer,
	productDetails: productDetailsReducer,
	cart: cartReducer,
	userLogin: userLoginReducer,
	userRegister: userRegisterReducer,
	userDetails: userDetailsReducer,
	userUpdateProfile: userUpdateProfileReducer,
	orderCreate: orderCreateReducer,
	orderDetails: orderDetailsReducer,
	orderPay: orderPayReducer,
	orderMyList: orderMyListReducer,

})

const cartItemsFromStorage = localStorage.getItem('cartItems')
	? JSON.parse(localStorage.getItem('cartItems'))
	: [];

const userDetailsFromStorage = localStorage.getItem('userInfo')
	? JSON.parse(localStorage.getItem('userInfo'))
	: null;

const shippingAddressFromStorage = localStorage.getItem('shippingAddress')
	? JSON.parse(localStorage.getItem('shippingAddress'))
	: {};

const initialState = {
	cart: {cartItems: cartItemsFromStorage, shippingAddress: shippingAddressFromStorage},
	userLogin: {userInfo: userDetailsFromStorage}
	}


const middlewares = [thunk];

// thunk is the async await for redux
const store = createStore(
	reducer,
	initialState,
	composeWithDevTools(applyMiddleware(...middlewares))
);



export default store;
