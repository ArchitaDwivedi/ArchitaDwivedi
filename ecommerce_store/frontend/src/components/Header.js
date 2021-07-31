// Link:- anchor tag
// Box:- like div, kuch bhi bana sakte hain.
import {useState} from 'react';
import {Flex,Heading, Link, Box, Icon} from '@chakra-ui/react';
import {HiShoppingBag, HiUser, HiOutlineMenuAlt3} from 'react-icons/hi';
import {Link as RouterLink} from 'react-router-dom';

// A helper component which will be used internally by our Box
// children is whateber will be put between the <MenuItems> tag.

// Essentially this is something that each of the options in our header
// will be.

// We have made the Link a RouterLink, in order to prevent reloading
const MenuItems = ({children,url}) => {
    return(
        <Link
        as={RouterLink}
        to={url}
        mt={{base: 4 , md: 0}}
        fontSize="sm"
        color="whiteAlpha.800"
        letterSpacing="wide"
        textTransform="uppercase"
        _hover={{color: 'whiteAlpha.800'}}
        mr="5"
        display="block"
    >
        {children}
    </Link>
    );


}





const Header = () => {
    const [show, setShow] = useState(false);

    return(
        <Flex 
        as="header" 
        align="center" 
        justifyContent="space-between" 
        wrap="wrap" 
        py="6"
        px="6" 
        bgColor="gray.800" 
        shadow="md" 
        // so it extends all way to the right of the screen
        w="100%"
        top="0" 
        pos="fixed" 
        zIndex="2"
        >
            <Flex align="center" mr="5">
                <Heading 
                as="h1" 
                color="whiteAlpha.800" 
                fontWeight="medium" 
                size="md" 
                letterSpacing="wider"
                // if screen size is md, give 1 rem
                // but if it is base i.e b/w md and lg (normal), set it to 0
                mr={{md: '1rem', base: 0}}
                >
                    <Link 
                        as={RouterLink}
                        to="/" 
                        // hover effect
                        _hover={{color:'whiteAlpha.700', textDecor: 'none'}}
                        >
                        Ecommerce Store
                    </Link>

                </Heading>
            </Flex>



            <Box onClick={() => setShow(!show)}
                display={{base: 'block', md: 'none', sm:'block'}}>
                <Icon as={HiOutlineMenuAlt3} color="white" w="6" h="6"/>
                <title>Menu</title>
            </Box>



            
            <Box
                // is show state variable is true i.e if it is small,
                // dont show the menu bar items, else show them
                align="center" width={{sm: 'full', md:'auto'}}
                display={{sm: show ? 'block' : 'none', md:'flex' }}
                //display={{sm: }}
                >
                <MenuItems url="/cart"> 
                    <Flex alignItems="center">
                        <Icon as={HiShoppingBag} w="4" h="4" mr="1"/>
                        Cart
                    </Flex>
                </MenuItems>

                <MenuItems url="/">
                    <Flex alignItems="center">
                        <Icon as={HiUser} w="4" h="4" mr="1"/>
                        Login
                    </Flex>
                </MenuItems>
            </Box>
        </Flex>
    );

}

export default Header;