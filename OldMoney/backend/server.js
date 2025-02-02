import express from 'express';
import dotenv from 'dotenv';
import colors from 'colors';
import connectDB from './config/db.js';
import ProductRoutes from './routes/productRoutes.js';
import {notFound, errorHandler} from './middleware/errorMiddleware.js';
import userRoutes from './routes/userRoutes.js';
import orderRoutes from './routes/orderRoutes.js';

dotenv.config()
await connectDB();
const app = express();
app.use(express.json())

app.get('/', (req,res)=>{
    res.send('API is running!');
});

app.use('/api/products',ProductRoutes);
app.use('/api/users', userRoutes);
app.use('/api/orders', orderRoutes);

app.use(notFound)
app.use(errorHandler)

const PORT = process.env.PORT || 5000;

app.listen(PORT, console.log(`Server running on port ${PORT}`));