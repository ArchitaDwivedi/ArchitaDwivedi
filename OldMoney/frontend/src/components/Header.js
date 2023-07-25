import {Flex, Heading, Link, Box, Icon, Text, Menu, Button, MenuButton, MenuItem, MenuList} from '@chakra-ui/react';
import {Link as RouterLink, useNavigate} from 'react-router-dom';
import {HiShoppingBag, HiUser, HiOutlineChevronDown, HiChevronDown, HiChevronDoubleDown} from 'react-icons/hi';
import { PiShirtFoldedThin, PiDressThin, PiPantsThin, PiHandbagSimpleLight } from "react-icons/pi";
import HeaderMenuDropDown from './HeaderMenuDropDown';
import HeaderMenuItems from './HeaderMenuItems';
import { useDispatch, useSelector } from 'react-redux';
import {useState} from 'react';
import { logout } from '../actions/userActions';
const Header = () => { 
    const dispatch = useDispatch();
    const navigate = useNavigate();
    const [show, setShow] = useState(false);
    const userLogin = useSelector( (state) => state.userLogin);
    const {userInfo} = userLogin;

    const logoutHandler = () => {
        dispatch(logout());
        navigate('/login');
    }

return(
    <Flex as="header"
        align="center"
        justifyContent="space-between"
        py="6"
        px="6"
        bgColor="#D5C8BE"
        shadow="md"
        w="100%"
        top="0"
        pos="fixed"
        zIndex="2"
    >
        <Flex
            align="center"
            mr="5"
        >
            <Heading as="h1" 
                color="#7a5f4a"
                size="lg"
                letterSpacing="widest"
                fontFamily="body"
                fontWeight="light"
                _hover={{color: "#656c4f"}}
                >
                    <Link as={RouterLink} to="/" _hover={{color: "#8aa1a8"}}>OLD MONEY</Link>
            </Heading>
        </Flex>

        <Box align="center"
            >
                <Flex alignItems="center">
                <Menu>
                    <HiChevronDoubleDown w="7" h="7" color="#7b8757"/>
                    <MenuButton
                    fontSize="md"
                    letterSpacing="wide"
                        ml='1'
                        display="block"
                        mr="10"
                        color="#7a5f4a"
                        _hover={{ color: "#7b8757" }}
                    >
                        Categories 
                    </MenuButton>

                    <MenuList>
                    <HeaderMenuDropDown icon={PiShirtFoldedThin} label="Shirts & Blouses"/>
                    <HeaderMenuDropDown icon={PiDressThin} label="Dresses"/>
                    <HeaderMenuDropDown icon={PiPantsThin} label="Bottoms & Skirts"/>
                    <HeaderMenuDropDown icon={PiHandbagSimpleLight} label="Bags, Shoes & Misc"/>
                    </MenuList>
                </Menu>
                <HeaderMenuItems url="/cart" icon={HiShoppingBag} label="Cart"/>
                {userInfo ? 
                (<Menu>
                    <MenuButton
                        as={Button}
                        rightIcon={HiChevronDown}
                    >
                        {userInfo.name}
                    </MenuButton>
                    <MenuList>
                        <MenuItem as={RouterLink} to='/profile'>
                            Profile
                        </MenuItem>
                        <MenuItem onClick={logoutHandler}>
                            Logout
                        </MenuItem>
                    </MenuList>
                </Menu>) 
                
                : 
                
                (<> 
                <HeaderMenuItems url="/login" icon={HiUser} label="Login"/></>)}
                </Flex>

            </Box>
    </Flex>


    )


};
export default Header;
    


    