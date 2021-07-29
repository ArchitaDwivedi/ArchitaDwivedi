//--------------------------- VERSION 1 -----------------------------------//
/* import Footer from './components/Footer';
import Header from './components/Header';

// making an arrow function called 'App' which
// returns some JSX that Babel will convert to vanilla JS for the browser to understand.
const App = () => {
    return (
        // <> is a fragment, so that we can wrap multiple elements together, without
        // having to use <div> for each one.
        <>
        <Header/>
        <div>
            <h1>RST STORE</h1>
        </div>
        <Footer/>
        </>
    );
}

// If we want to import something entirely without using {}, then
// we must use 'export default'
export default App;
*/



//--------------------------- VERSION 2 -----------------------------------//
import Footer from './components/Footer';
import Header from './components/Header';
import {Flex} from '@chakra-ui/react';
import HomeScreen from './screens/HomeScreen';


// making an arrow function called 'App' which
// returns some JSX that Babel will convert to vanilla JS for the browser to understand.
const App = () => {
    return (
        // <> is a fragment, so that we can wrap multiple elements together, without
        // having to use <div> for each one.
        <>
        <Header/>
        <Flex as="main" direction="column" mt="72px" minH="xl" py="6" px="6" bgColor="gray.100">
            <HomeScreen/>
        </Flex>
        <Footer/>
        </>
    );
}

// If we want to import something entirely without using {}, then
// we must use 'export default'
export default App;