import {Flex, Heading, Link, Box, Icon, Text} from '@chakra-ui/react';
import {Link as RouterLink} from 'react-router-dom';
import {HiShoppingBag} from 'react-icons/hi';

const HeaderMenuItems = ({icon, url, label}) => { 
return(
    <>
    <Icon as={icon} w="6" h="6" mr="1" color="#7b8757"/>
    <Link as={RouterLink} to={url} fontSize="md" color="#7a5f4a" letterSpacing="wide"
    _hover={{color: "#7b8757"}} display="block" mr="10">
        {label}
    </Link>
    </>
    )};

export default HeaderMenuItems
    