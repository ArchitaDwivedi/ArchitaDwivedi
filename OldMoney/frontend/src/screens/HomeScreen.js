import {useState, useEffect} from 'react';
import { useDispatch, useSelector } from 'react-redux';
import axios from 'axios';
import { Heading, Grid } from "@chakra-ui/react";
import Product from "../components/Product";
import { listProducts } from '../actions/productAction';
import Loader from '../components/Loader';
import Message from '../components/Message';


const HomeScreen = () => { 
    
    const dispatch = useDispatch();

    const productList = useSelector((state) => state.productList)

    const {loading, products, error } = productList;

    useEffect( () => {
        dispatch(listProducts())
    }, [dispatch])
return(
    <>
    <Heading 
        mb="8"
        as="h2"
        fontSize="3xl"  
        letterSpacing="widest"
        fontFamily="Copperplate"
        fontWeight="hairline"
        color="#7c8a96"
        align="center"
        mt={{base: "7", md: "2"}}
    >
        Latest Products
    </Heading>
    <Grid align="center" templateColumns={{base: "repeat(1, 1fr)", md: "repeat(2, 1fr)", lg: "repeat(3, 1fr)"}} gap={{base: "4", md: "2", lg: "3"}}>
    { loading ? (<Loader/>) : error ? (<Message type={error}>{error}</Message>) :
        products && (products.filter((p) => (p.latestProduct)).map((prod)=> <Product key={prod._id} product={prod}/> ))
        
        
    }
    </Grid>
    </>
)};
export default HomeScreen;
   
