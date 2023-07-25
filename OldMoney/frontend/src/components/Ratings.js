import { Box, Flex, Icon, Text } from '@chakra-ui/react';
import { IoStar, IoStarHalf, IoStarOutline } from 'react-icons/io5';

const Rating = ({ value, text, color = '"#89a1a8"' }) => {
	return (
		<Flex direction="column">
			<Box mr='2' >
				<Icon w = "3"
					color={color}
					as={value >= 1 ? IoStar : value >= 0.5 ? IoStarHalf : IoStarOutline}
				/>
				<Icon w = "3"
					color={color}
					as={value >= 2 ? IoStar : value >= 1.5 ? IoStarHalf : IoStarOutline}
				/>
				<Icon w = "3"
					color={color}
					as={value >= 3 ? IoStar : value >= 2.5 ? IoStarHalf : IoStarOutline}
				/>
				<Icon w = "3"
					color={color}
					as={value >= 4 ? IoStar : value >= 3.5 ? IoStarHalf : IoStarOutline}
				/>
				<Icon w = "3"
					color={color}
					as={value >= 5 ? IoStar : value >= 4.5 ? IoStarHalf : IoStarOutline}
				/>
			</Box>
			<Text fontSize="xs">{text}</Text>
		</Flex>
	);
};

export default Rating;
