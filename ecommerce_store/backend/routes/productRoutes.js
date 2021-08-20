import express from 'express';
// import the logic bit here
import {
  getProducts,
  getProductById,
  deleteProduct,
  createProduct,
  updateProduct,

} from '../controllers/productController.js';
import {protect,admin} from '../middleware/authMiddleware.js';

const router = express.Router();
// if someone tries to go to /, we could chain multiple requests
// .get().post(),etc
// i.e if someone tries to get or post,etc.
router.route('/').get(getProducts).post(protect, admin, createProduct);
router
  .route('/:id')
  .get(getProductById)
  .delete(protect, admin, deleteProduct)
  .put(protect, admin, updateProduct);


export default router;








// // This is where we will add all product related routes
// // and how to handle them.
// // i.e to fetch data, if we want to update, etc.
// import express from 'express';
// import asyncHandler from 'express-async-handler';
// import Product from '../models/productModel.js';




// // creating a router object that will help us 
// // listen to things coming on server.js
// const router = express.Router();



// // So express.Router() helps sticks these routes onto
// // our server.js



// // if someone tries to get /api/products
// // Now we will make the callback an async function,
// // because our ultimate goal there would be interacting
// // with our database. So we will add async await.
// // Now with async await, it is convention to use try and catch
// // So instead of using a try and catch to handle
// // errors, We will use the 'asyncHandler' instead.
// // This will handle the errors for us.
// // For example: when you mess up the id by breaking its
// // format i.e if you remove a few letters from between 
// // it will give a Cast Error
// // So each time we must write try catch for each of the
// // routes which may end up looking messy, so we could use asyncHandler
// // It wont break the app, but it'll send the error to the browser.




// // Old way 
// // routes.get('/', async (req,res) => {
// //     const products = await Product.find({});
// //     res.json(products);
// // })
// //---
// // New way
// router.get('/', asyncHandler(async (req,res) => {
//     const products = await Product.find({});
//     res.json(products);
// }));





// // if someone tries to get /api/products/id
// // Old way
// // routes.get('/:id', async (req,res) => {
// //     // const product = products.find( (prod) => prod._id === req.params.id)
// //     const product = await Product.findById(req.params.id);

// //     if (product){
// //         res.json(product);
// //     } else{
// //         res.status(404).json({message: "Product not found!"});
// //     }
// // });
// //---
// // New way
// router.get('/:id', asyncHandler(
//     async (req,res) => {
//         // const product = products.find( (prod) => prod._id === req.params.id)
//         const product = await Product.findById(req.params.id);
    
//         if (product){
//             res.json(product);
//         } else{
//             res.status(404).json({message: "Product not found!"});
//         }
//     }
// ));



// export default router;
