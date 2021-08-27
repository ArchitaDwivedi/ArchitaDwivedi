import path from 'path';
import express from 'express';
import dotenv from 'dotenv';
import colors from 'colors';
import morgan from 'morgan';
import connectDB from './config/db.js';
import productRoutes from './routes/productRoutes.js';
import userRoutes from './routes/userRoutes.js';
import orderRoutes from './routes/orderRoutes.js';
import { notFound, errorHandler } from './middleware/errorMiddleware.js';
import uploadRoutes from './routes/uploadRoutes.js';

dotenv.config();


// before our app even runs we want to connect to db
connectDB();


// our main app
const app = express();


// parse the body
app.use(express.json()); 


// morgan middleware
app.use(morgan('dev'));



app.use('/api/products', productRoutes);

app.use('/api/users', userRoutes);

app.use('/api/orders', orderRoutes);

app.use('/api/upload', uploadRoutes);



// PayPal data endpoint
app.get('/api/config/paypal', (req, res) => {
  res.send(process.env.PAYPAL_CLIENT_ID);
});



// Make 'uploads' folder static
const __dirname = path.resolve();
app.use('/uploads', express.static(path.join(__dirname, '/uploads')));



if (process.env.NODE_ENV === 'production') {
  app.use(express.static(path.join(__dirname, '/frontend/build')));

  app.get('*', (req, res) => {
    res.sendFile(path.resolve(__dirname, 'frontend', 'build', 'index.html'));
  });
} else {
  app.get('/', (req, res) => {
    res.send('API is running!');
  });
}



// Middlewares (Errors)
app.use(notFound);

app.use(errorHandler);



const PORT = process.env.PORT || 5000;



app.listen(PORT, console.log(`Server running on port ${PORT}`.yellow.bold));


