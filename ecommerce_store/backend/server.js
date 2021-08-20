import express from 'express';
import dotenv from 'dotenv';
import colors from 'colors';
import morgan from 'morgan';
import connectDB from './config/db.js';
import productRoutes from './routes/productRoutes.js';
import userRoutes from './routes/userRoutes.js';
import orderRoutes from './routes/orderRoutes.js';
import { notFound, errorHandler } from './middleware/errorMiddleware.js';

dotenv.config();

// before our app even runs we want to connect to db
connectDB();

// our main app
const app = express();
// parse the body
app.use(express.json()); 


// using morgan middleware
app.use(morgan('dev'));

// Route/Endpoint
app.get('/', (req, res) => {
  res.send('API is running!');
});


// All product related routes will go here
app.use('/api/products', productRoutes);
// // All user related routes will go here
app.use('/api/users', userRoutes);
// // All order related routes will go here
app.use('/api/orders', orderRoutes);


//PayPal's data endpoint. We have made this so that we dont 
// have to store the client id in the frontend. So essentially,
// we'll get the client id from here
app.get('/api/config/paypal', (req, res) => {
  res.send(process.env.PAYPAL_CLIENT_ID);
});

// Middleware (Errors)
app.use(notFound);
app.use(errorHandler);

// get env variable.
const PORT = process.env.PORT || 5000;

// listen on port 5000
app.listen(PORT, console.log(`Server running on port ${PORT}`.yellow.bold));
