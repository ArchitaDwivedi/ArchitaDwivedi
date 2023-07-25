import {
	Box,
	Button,
	Flex,
	Grid,
	Heading,
	Icon,
	Image,
	Link,
	Select,
	Text,
} from '@chakra-ui/react';
import { useEffect } from 'react';
import { IoCloseOutline } from 'react-icons/io5';
import { useDispatch, useSelector } from 'react-redux';
import {
	Link as RouterLink,
	useNavigate,
	useParams,
	useSearchParams,
} from 'react-router-dom';

import { addToCart, removeFromCart } from '../actions/cartActions';
import Message from '../components/Message';

const CartScreen = () => {
	const dispatch = useDispatch();
	const navigate = useNavigate();

	const { id } = useParams();

	const [searchParams] = useSearchParams();
	let qty = searchParams.get('qty');

	const cart = useSelector((state) => state.cart);
	const { cartItems } = cart;

	useEffect(() => {
		if (id) {
			dispatch(addToCart(id, qty));
		}
	}, [dispatch, id, qty]);

	const removeFromCartHandler = (id) => {
		dispatch(removeFromCart(id));
	};

	const checkoutHandler = () => {
		navigate(`/login?redirect=/shipping`);
	};

	return (
		<Grid>
			<Box>
				<Heading mb='8' size="lg" color="#88a2a8">Shopping Cart</Heading>
				<Flex>
					{cartItems.length === 0 ? (
						<Message>
							Your cart is empty.{' '}
							<Link as={RouterLink} to='/'>
								Go Back
							</Link>
						</Message>
					) : (
						<Grid templateColumns='4fr 2fr' gap='10' w='full'>
							<Flex direction='column'>
								{cartItems.map((item) => (
									<Grid
										key={item.product}
										size='100%'
										alignItems='center'
										justifyContent='space-between'
										borderBottom='1px'
										borderColor='gray.200'
										py='4'
										px='2'
										rounded='lg'
										_hover={{ bgColor: 'gray.50' }}
										templateColumns='1fr 4fr 2fr 2fr 2fr'>
										{/* Product Image */}
										<Image
											src={item.image}
											alt={item.name}
											borderRadius='lg'
											height='14'
											width='14'
											objectFit='cover'
										/>

										{/* Product Name */}
										<Text fontWeight='semibold' fontSize='lg' color="#7a5f4a">
											<Link as={RouterLink} to={`/product/${item.product}`}>
												{item.name}
											</Link>
										</Text>

										{/* Product Price */}
										<Text fontWeight='semibold' fontSize='lg' color="#7b8757">
											₹{item.price}
										</Text>

										{/* Quantity Select Box */}
										<Select
											value={item.qty}
											onChange={(e) =>
												// the + is for string to number
												dispatch(addToCart(item.product, +e.target.value))
											}
											width='20'>
											{[...Array(item.countInStock).keys()].map((i) => (
												<option key={i + 1}>{i + 1}</option>
											))}
										</Select>

										{/* Delete Button */}
										<Button
											_hover={{bg: "#e65c42"}}
											type='button'
											bg="#f9b8ac"
											w="40%"
											onClick={() => removeFromCartHandler(item.product)}>
											
											<Icon as={IoCloseOutline} w="6" h="6"/>
										</Button>
									</Grid>
								))}
							</Flex>

							<Flex
								direction='column'
								bgColor='#faf2ea'
								rounded='md'
								padding='5'
								height='48'
								justifyContent='space-between'>
								<Flex direction='column'>
									<Heading as='h2' fontSize='2xl' mb='2' color="#7a5f4a">
										Subtotal (
										{cartItems.reduce((acc, currVal) => acc + +currVal.qty, 0)}{' '}
										items )
									</Heading>
									<Text
										fontWeight='bold'
										fontSize='2xl'
										color='#7b8757'
										mb='4'>
										₹
										{cartItems.reduce(
											(acc, currVal) => acc + currVal.price * +currVal.qty,
											0
										)}
									</Text>
									<Button
										type='button'
										disabled={cartItems.length === 0}
										size='lg'
										bgColor='#7b8757'
										_hover={{bgColor: "#a9b87b"}}
										onClick={checkoutHandler}>
										Proceed to checkout
									</Button>
								</Flex>
							</Flex>
						</Grid>
					)}
				</Flex>
			</Box>
		</Grid>
	);
};

export default CartScreen;
