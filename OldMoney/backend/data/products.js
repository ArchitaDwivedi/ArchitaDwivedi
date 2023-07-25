const products = [
	{
		
		name: 'Striped Polo Shirt',
		image: '/images/s1.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Polo',
		category: 'Blouses',
		price: 12000,
		countInStock: 22,
		rating: 4.0,
		numReviews: 4,
		latestProduct: true
	},
	{
		
		name: 'Plain White Shirt',
		image: '/images/s2.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Urban Outfitters',
		category: 'Blouses',
		price: 8500,
		countInStock: 42,
		rating: 3.5,
		numReviews: 2,
		latestProduct: true
	},
	{
		
		name: 'Pink Polo Tshirt',
		image: '/images/s3.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Urban Outfitters',
		category: 'Blouses',
		price: 8500,
		countInStock: 42,
		rating: 3.5,
		numReviews: 2,
		latestProduct: false
	},
	{
		
		name: 'Blue Jean Shirt',
		image: '/images/s2.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Urban Outfitters',
		category: 'Blouses',
		price: 8500,
		countInStock: 42,
		rating: 3.5,
		numReviews: 2,
		latestProduct: false
	},
	{
		
		name: 'Beige Long Skirt',
		image: '/images/p1.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Ralph Lauren',
		category: 'Bottoms',
		price: 6000,
		countInStock: 18,
		rating: 4.5,
		numReviews: 2,
		latestProduct: true
	},
	{
		
		name: 'Grey Formal Pants',
		image: '/images/p2.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Gucci',
		category: 'Bottoms',
		price: 21000,
		countInStock: 8,
		rating: 4.8,
		numReviews: 12,
		latestProduct: true
	},
	{
		
		name: 'White Flowy Half Pants',
		image: '/images/p3.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Ralph Lauren',
		category: 'Bottoms',
		price: 6000,
		countInStock: 18,
		rating: 4.5,
		numReviews: 2,
		latestProduct: false
	},
	{
		
		name: 'Classic Khakhi Pants',
		image: '/images/p4.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Ralph Lauren',
		category: 'Bottoms',
		price: 6000,
		countInStock: 18,
		rating: 4.5,
		numReviews: 2,
		latestProduct: false
	},
	{
		
		name: 'Grey Ralph Dress',
		image: '/images/d1.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Chanel',
		category: 'Dresses',
		price: 43000,
		countInStock: 6,
		rating: 4.9,
		numReviews: 8,
		latestProduct: true
	},
	{
		
		name: 'Green Slit Silk Dress',
		image: '/images/d2.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Tom Ford',
		category: 'Dresses',
		price: 16000,
		countInStock: 21,
		rating: 4.1,
		numReviews: 3,
		latestProduct: true
	},
	{
		
		name: 'Long Beige Dress',
		image: '/images/d3.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Chanel',
		category: 'Dresses',
		price: 43000,
		countInStock: 6,
		rating: 4.9,
		numReviews: 8,
		latestProduct: false
	},
	{
		
		name: 'Simple Black Dress',
		image: '/images/d4.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Chanel',
		category: 'Dresses',
		price: 43000,
		countInStock: 6,
		rating: 4.9,
		numReviews: 8,
		latestProduct: false
	},
	{
		
		name: 'Burgundy Dirt Bag',
		image: '/images/b1.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Calvin Klein',
		category: 'Misc',
		price: 7500,
		countInStock: 25,
		rating: 3.4,
		numReviews: 3,
		latestProduct: true
	},
	{
		
		name: 'Black Tipped Heels',
		image: '/images/b2.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Chanel',
		category: 'Misc',
		price: 9500,
		countInStock: 0,
		rating: 4.2,
		numReviews: 5,
		latestProduct: true
	},
	{
		
		name: 'Classic Sun Money Scarf',
		image: '/images/b3.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Calvin Klein',
		category: 'Misc',
		price: 7500,
		countInStock: 25,
		rating: 3.4,
		numReviews: 3,
		latestProduct: false
	},
	{
		
		name: 'Small Brown Purse',
		image: '/images/b4.jpeg',
		description:
			'Etiam cursus condimentum vulputate. Nulla nisi orci, vulputate at dolor et, malesuada ultrices nisi. Ut varius ex ut purus porttitor, a facilisis orci condimentum. Nullam in elit et sapien ornare pellentesque at ac lorem.',
		brand: 'Calvin Klein',
		category: 'Misc',
		price: 7500,
		countInStock: 25,
		rating: 3.4,
		numReviews: 3,
		latestProduct: false
	},
];

export default products;
