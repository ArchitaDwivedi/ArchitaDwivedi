//--------------------------- VERSION 3 -----------------------------------//
import {BrowserRouter as Router, Route} from 'react-router-dom';
import {Flex} from '@chakra-ui/react';
import Footer from './components/Footer';
import Header from './components/Header';
import HomeScreen from './screens/HomeScreen';
import ProductScreen from './screens/ProductScreen';
import CartScreen from './screens/CartScreens';
import LoginScreen from './screens/LoginScreen';
import RegisterScreen from './screens/RegisterScreen';
import ProfileScreen from './screens/ProfileScreen';
// making an arrow function called 'App' which
// returns some JSX that Babel will convert to vanilla JS for the browser to understand.
const App = () => {
    return (
        // We have replaced the fragment with the Router
        // Now instead of directly writing the path, we are going
        // to use Route. We will tell this Route component about which component it must 
        // render when giving a certain path. (check line 20)
        // On line 27, the :id becomes a variable because of the ':' and so now
        // it can change depending on the id we get.
        // Also, the / path will match all urls and for each of the URL's the homescreen
        // will get rendered since Router is doing pattern matching from your address bar.
        // So to make sure that the Homescreen only gets rendered when there is just a / , we 
        // must use the 'exact' keyword (line 26)
        <Router>
            <Header/>
            <Flex as="main" direction="column" mt="72px" minH="xl" py="6" px="6" bgColor="gray.100">
                <Route path="/profile" component={ProfileScreen}/>
                <Route path="/register" component={RegisterScreen}/>
                <Route path="/login" component={LoginScreen}/>
                <Route path="/" exact component={HomeScreen} />
                <Route path="/product/:id" component={ProductScreen} />
                {/* The reason we have put a ? is because, we want the id part
                to be optional. This means, if someone just tries to go to /cart, they
                should still be redirected to the cart page and if they happen to come
                with any id. They should still be able to do so.*/}
                <Route path="/cart/:id?" component={CartScreen} />
            </Flex>
            <Footer/>
        </Router>
    );
}

// If we want to import something entirely without using {}, then
// we must use 'export default'
export default App;