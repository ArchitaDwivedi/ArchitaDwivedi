import {Flex, Text, Link, Box, Icon} from '@chakra-ui/react';

const Footer = () => { 
return(
    <Flex as="footer"
    justifyContent="center"
    py="5"
    
    bgColor="#f7f0e9"
    >
        <Text         fontFamily="Copperplate"
        fontWeight="hairline" color="#7f6551" >
            Copyright 2023, Old Money. All Rights Reserved.</Text>
    </Flex>
)
};
export default Footer;
    