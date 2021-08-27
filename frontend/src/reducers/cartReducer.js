import {
  CART_ADD_ITEM,
  CART_REMOVE_ITEM,
  CART_SAVE_SHIPPING_ADDRESS,
  CART_SAVE_PAYMENT_METHOD,
} from '../constants/cartConstants';

export const cartReducer = (
  state = { cartItems: [], shippingAddress: {} },
  action
) => {
  switch (action.type) {
    case CART_ADD_ITEM:
    // first get the item the user wants to put in the cart
      const item = action.payload;

// A person could repeat an item. So, we check to see if the item is 
            // already present in cart
            // ** The 'product' here is the id of our product. This is defined in the Actions file
      const existItem = state.cartItems.find((i) => i.product === item.product);

      // if yes
      if (existItem) {
// we check to see if the item is 
            // already present in cart. If yes then we replace it with the existing one. 
            // Otherwise we just append the item.

            // ...state: if there is already something in state( from the localStorage ) store that first.
        return {
          ...state,
          cartItems: state.cartItems.map((i) =>
            i.product === existItem.product ? item : i
          ),
        };
      } else {
        // append the new item
        return { ...state, cartItems: [...state.cartItems, item] };
      }
    case CART_REMOVE_ITEM:
      return {
        ...state,
        cartItems: state.cartItems.filter((i) => i.product !== action.payload),
      };
    case CART_SAVE_SHIPPING_ADDRESS:
      return {
        ...state,
        shippingAddress: action.payload,
      };
    case CART_SAVE_PAYMENT_METHOD:
      return {
        ...state,
        paymentMethod: action.payload,
      };
    default:
      return state;
  }
};
