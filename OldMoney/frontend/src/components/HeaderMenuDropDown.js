import {MenuItem, Icon} from '@chakra-ui/react';



const HeaderMenuDropDown = ({icon, label }) => { 
return(
        <MenuItem minH='48px' _hover={{color: "#7b8757"}} color="#7a5f4a">
        <Icon as={icon} w="6" h="6" mr="4" ml="1" color="#7b8757"/>
        <span >{label}</span>
        </MenuItem>


    )};
export default HeaderMenuDropDown
    