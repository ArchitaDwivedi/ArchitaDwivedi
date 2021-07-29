//----------------------------- VERSION 1 ---------------------------------//

// this is our homescreen where all products will be displayed.
// Each of those products will be displayed in a certain way. The rule of that
// if defined in Product.js, so we must import it in order to display it on our Homescreen
import {Heading, Grid} from '@chakra-ui/react';
import Product from '../components/Product';
// The Product component currently depends on our product.js file, so we must
// import that here too.
import products from '../products';



// Our entire Home Page screen
const HomeScreen = () => {
    // essentially, we map over each of the product object, pass it to our Product.js, it
    // builds that product box and then fills it in the Grid (in this case 4 will be displayed in one line)
    
    // Imporant POINT:- Whenever you render arrays as below, you MUST give 'KEYS',
    // in order to uniquely indentify each product, in our case it would be the product._id
    return (
        <div>
            <Heading mb="8" as="h2" fontSize="3xl">
                Latest Products
            </Heading>

            <Grid templateColumns="repeat(4,1fr)" gap="8">
                
                {products.map( (prod) => (
                    <Product key={prod._id} product={prod}/>
                ))}
            </Grid>
        </div>
    )

}

export default HomeScreen;