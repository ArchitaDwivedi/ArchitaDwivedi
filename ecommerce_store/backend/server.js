//--------------------- VERSION 1 ----------------------//
/* Basic express set up to listen on port 5000
// Remember that currently, our frontend has ES module system support
// and our backend does not. So we cannot use 'import' keyword in the backend.
// Later on we will fix this to make both consistent. But for now we must use
// 'require'

const express = require('express');

// Make sure that you are changing the 'export' keyword in the products.js
// file.
const products = require('./data/products');

// This will give back a special express object which we save in app.
// This is just like the app = HTTP().. we do in node.
// We use express here since it gives us better features.
// So we're using our express package to build our server and not the HTTP package.
const app = express();


// ** ESSENTIALLY, We are determining or deciding what we want to send back,
// if a particular endpoint receives a request!

// At this moment, we have a file called products.js with us here, so we are
// directly getting this from there.

// However, later on we will be populating our database with data and then
// we will use mongoose to get, push, put or delete data from our database.

//creating endpoints
// if someone tries to GET '/' 

// Remember that req and res are just going to be objects. Req being the info
// about the HTTP req that triggered the event and res being the HTTP response you want
// to send back.

// In Node we would have to do stuff like res.write and many other steps to send
// response back. But here in Express, we're just doing a simple res.send()

// Now when you try and go to localhost:5000 on your browser,
// you'll get the message below.
app.get('/', (req,res) => {
    // res.send() to send the data back
    res.send('API is running!')
})


// To get all products' detail
app.get('/api/products', (req,res) => {
    // res.send() sends back HTML.
    // TO send back JSON, just do res.json()
    res.json(products);
})



// a particular product
// We know that req object contains all detail about our HTTP request,
// so technically it will have details about our URL too.
// we will get access to this using our req.params
app.get('/api/products/:id', (req,res) => {
    const product = products.find( (prod) => prod._id === req.params.id)
    res.json(product);
})



// listen(what to port listen on and a callback)
app.listen(5000, () => {
    console.log('Server runnning on port 5000')
});
*/


//-------------------- VERSION 2 ------------------------//
// We have added "type" : "module" in the package.json of the root folder
// so now we can use ES module syntax
/*import express from 'express';
import dotenv from 'dotenv';
import products from './data/products.js';


dotenv.config();
const app = express();

app.get('/', (req,res) => {
    // res.send() to send the data back
    res.send('API is running!')
})


// To get all products' detail
app.get('/api/products', (req,res) => {
    // res.send() sends back HTML.
    // TO send back JSON, just do res.json()
    res.json(products);
})

app.get('/api/products/:id', (req,res) => {
    const product = products.find( (prod) => prod._id === req.params.id)
    res.json(product);
})

// get env variable.
const PORT = process.env.PORT || 5000;

app.listen(PORT, () => {
    console.log('Server runnning on port 5000')
});*/




//-------------------- VERSION 3 ------------------------//
import express from 'express';
import dotenv from 'dotenv';
import colors from 'colors';
import morgan from 'morgan';
import connectDB from './config/db.js';
import productRoutes from './routes/productRoutes.js';
import userRoutes from './routes/userRoutes.js';
import {notFound, errorHandler} from './middleware/errorMiddleware.js';
 


dotenv.config();



// before our app even runs we want to connect to db
connectDB();




// our main app
const app = express();
app.use(express.json());



// using morgan middleware
app.use(morgan());




app.get('/', (req,res) => {
    // res.send() to send the data back
    res.send('API is running!')
})




// All product related routes will go here
app.use('/api/products', productRoutes);

// // All user related routes will go here
app.use('/api/users', userRoutes);

// // All order related routes will go here
// app.use('/api/orders', orderRoutes)


app.use(notFound);
app.use(errorHandler);


// get env variable.
const PORT = process.env.PORT || 5000;




// listen on port 5000
app.listen(PORT, console.log(`Server runnning on ${PORT}`.yellow.bold));