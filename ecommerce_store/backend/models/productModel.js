//----------------------- VERSION 1 --------------------//
import mongoose from 'mongoose';

// Building a schema i.e everything we 
// want in this Model -> username, password, etc

// we will make a review Schema as well, we wont make it in a completely 
// diff file.
// We need name, rating, comment,etc
const reviewSchema = mongoose.Schema({
    name: {
        type: String,
        required: true
    },
    rating: {
        type: Number,
        required: true,
     },   
    comment: {
        type: String,
        required: true        
    },
});





// A product can have 
// user -> each product will be added to page by an Admin so we need their details
// ...
const productSchema = mongoose.Schema({
    user: {
        // MongoDB's object id will get saved here
        // That object id will be of one of the users hence we've
        // given 'ref: User'
        type: mongoose.Schema.Types.ObjectId,
        required: true,
        ref: 'User',
    },
     name: {
         type: String,
         required: true
     },
     image: {
         type: String,
         required: true

     },
     brand: {
         type: String,
         required: true
     },
     category: {
        type: String,
         required: true
     },
     description: {
        type: String,
        required: true
     },
     rating: {
        type: Number,
        required: true,
        default: 0,
     },
     numReviews: {
        type: Number,
        required: true,
        default: 0,
     },
     price: {
        type: Number,
        required: true,
        default: 0,
     },
     countInStock: {
        type: Number,
        required: true,
        default: 0,
     },

     // we will use the schema from above
     // We need 'reviews' to be a collection
     // of all reviews so it'll be an array
     reviews: [reviewSchema],

},
// Schema can take in more args
// by enabling this, we'll essentially
// log the time of when the product was
// created,etc
{timestamps: true}

);

// building a model using our Schema
// Now that we've built a model, we can use Mongoose's inbuilt
// methods to talk to our MongoDB.
const Product = mongoose.model('Product', productSchema);


export default Product;