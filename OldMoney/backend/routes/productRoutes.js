import express from 'express';
import asyncHandler from 'express-async-handler';
import Product from '../models/productModel.js';
import { getProducts, getProductById } from '../controllers/productController.js';


const router = express.Router();

router.route('/').get(getProducts)
router.route('/:id').get(getProductById)



router.get('/blouses', (req,res) => {
    res.json(product);
});

router.get('/pants', (req,res) => {
    res.json(product);
});

router.get('/dresses', (req,res) => {
    res.json(product);
});

router.get('/misc', (req,res) => {
    res.json(product);
});

export default router;