//----------------------------- VERSION 1 ---------------------------------//
// We have imported this Link from react-router-dom to prevent our Anchor tag's
// (Link componenet in Chakra UI) default page reload behaviour. 
import {Link as RouterLink} from 'react-router-dom';
import {Box, Link, Image, Flex, Heading, Text} from '@chakra-ui/react';
import Rating from './Rating';
// we will accept a product object and then display its info in a particulat manner on 
// our HomeScreen

// product is actually a part of the 'prop' object. If we has not destructed it like
// {product} then we would have to do 'prop.product'
const Product = ({product}) => {
    return (
        // when someone clicks our product image, we will push that 
        // person to the /product/<whateve_Was_the_product_id>

        // Making Link as RouterLink to prevent page reloading, but still
        // preserving the Chakri UI's properties and style.
        // Instead of href we will use 'to' since that is required with RouterLink.
        // Now if you click on individual products, nothing will reload, but just
        // change normally.
        // The same needs to be done in our header too.
        <Link as={RouterLink} to={`/product/${product._id}`} _hover={{textDecor: 'none'}}>
            <Box
            maxW="sm"
            borderRadius="lg"
            borderWidth="1px"
            bgColor="white"
            overflow="hidden" // things will get cut out if screen is too small
            transition="all" // this is a feature that can actually manage the hover speed
            // i.e vo slow ya fast kar sakte hain (just a css animation property)
            _hover={{shadow: 'md'}}
            >
             <Image src={product.image} 
             alt={product.name} 
             min="360px"
             objectFit="cover"
             />
             <Flex py="5" px="4" direction="column" justifyContent="space-between" h="36">
                <Heading as="h4" fontSize="lg" mb="3">
                    {product.name}
                </Heading>

            <Flex alignItems="flex-end" justifyContent="space-between">
                <Rating value={product.rating} 
                text={`${product.numReviews} reviews`}
                color='yellow.400' 
                />

                <Text fontSize="2xl" fontWeight="medium" color="blue.600">
                    {product.price}
                </Text>
            </Flex>

             </Flex>
            </Box>
        </Link>
    );
}

export default Product;