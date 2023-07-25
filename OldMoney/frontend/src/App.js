import {Flex} from '@chakra-ui/react';
import { BrowserRouter, Route, Routes } from 'react-router-dom';
import Footer from "./components/Footer";
import Header from "./components/Header";
import CartScreen from './screens/CartScreen';
import HomeScreen from "./screens/HomeScreen";
import LoginScreen from './screens/LoginScreen';
import ProductScreen from './screens/ProductScreen';
import ProfileScreen from './screens/ProfileScreen';
import RegisterScreen from './screens/RegisterScreen';
import OrderScreen from './screens/OrderScreen';
import ShippingScreen from './screens/ShippingScreen';
import PaymentScreen from './screens/PaymentScreen';
import PlaceOrderScreen from './screens/PlaceOrderScreen';
const App = () => {
  return (
    <BrowserRouter>
      <Header/>
      <Flex as="main" direction="column" mt="84px" minH="5xl" py="6" px="6">
        <Routes>
          <Route path='/' element={<HomeScreen />} />
          <Route path='/api/products/:id' element={<ProductScreen />} />
          <Route path='/cart' element={<CartScreen/>} />
          <Route path='/cart/:id' element={<CartScreen/>} />
          <Route path='/login' element={<LoginScreen/>} />
          <Route path='/register' element={<RegisterScreen/>} />
          <Route path='/shipping' element={<ShippingScreen />} />
          <Route path='/profile' element={<ProfileScreen/>} />
          <Route path='/order/:id' element={<OrderScreen/>} />
          <Route path='/payment' element={<PaymentScreen/>} />
          <Route path='/placeorder' element={<PlaceOrderScreen/>} />
        </Routes>
      </Flex>
      <Footer />
      
    </BrowserRouter>
  );
}

export default App;
