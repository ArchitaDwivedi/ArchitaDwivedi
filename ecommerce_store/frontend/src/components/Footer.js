import {Flex,Text} from '@chakra-ui/react';


const Footer = () => {
    return(
        // as :- what this does is that it will make the <Flex> tag actually behave
        // as whatever is in the "as". So in this case, it acts like the <footer> tag.
        <Flex as="footer" justifyContent="center" py="5">
            <Text>CopyRight 2021 Ecommerce Store, Archita Dwivedi. All Rights Reserved.</Text>
        </Flex>
    );
    
}


export default Footer;