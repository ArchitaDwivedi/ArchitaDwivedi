import { Flex, Box, Image, Heading, Link, Text } from "@chakra-ui/react";
import {Link as RouterLink} from 'react-router-dom';
import Rating from "./Ratings";

const Product = ({product}) => { 
return(
    <Link
        as={RouterLink} 
        to={`/api/products/${product._id}`}
        _hover={{textDecor: 'none'}}
    >
        <Box
            maxW="md"
            borderRadius="lg"
            borderWidth="1px"
            bgColor="white"
            overflow="hidden"
            transition="all"
            _hover={{boxShadow: "dark-lg", }}
        >
            <Image 
                src={product.image} 
                alt={product.name} 
                minH="360px"
                objectFit="cover"
                // width="360px"

            />
            <Flex py="5" px="4" justifyContent="space-between" h="32"
            >
                <Box align="left">
                <Heading as="h5" fontSize="11px" mb="2" color="#7b8757">{product.brand}</Heading>
                <Heading as="h4" fontSize="lg" mb="3" color="#7a5f4a">{product.name}</Heading>
                <Text fontSize="xl" fontWeight="medium" color="#7e8b97">${product.price}</Text>
                </Box>
                <Rating align="right" value={product.rating} color="#939c76" text={`${product.numReviews} reviews`}/>
            </Flex>
        </Box>
    </Link>
)};
export default Product;
    