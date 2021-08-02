import {Spinner, Flex} from '@chakra-ui/react';


const Loader = () => {
    return (
        <Flex minHeight="50vh" alignItems="center" justifyContent="center">
            <Spinner thicknes="4px" color="blue.800" label="Loading..."/>
        </Flex>
    );
};

export default Loader;